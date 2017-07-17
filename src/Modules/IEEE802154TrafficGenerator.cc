//
// Copyright (C) 2004 Andras Varga      (IPvXTrafGen in INET 2.x)
// Copyright (C) 2017 Michael Kirsche
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <IEEE802154TrafficGenerator.h>

Define_Module(IEEE802154TrafficGenerator);

simsignal_t IEEE802154TrafficGenerator::rcvdPkSignal = registerSignal("rcvdPk");
simsignal_t IEEE802154TrafficGenerator::sentPkSignal = registerSignal("sentPk");

IEEE802154TrafficGenerator::IEEE802154TrafficGenerator()
{
    sendTimer = NULL;

    packetLengthPar = NULL;
    sendIntervalPar = NULL;
}

IEEE802154TrafficGenerator::~IEEE802154TrafficGenerator()
{
    cancelAndDelete(sendTimer);
}

void IEEE802154TrafficGenerator::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == 0)
    {
        // initialize the debug output bool from NED parameter value
        trafficDebug = (hasPar("trafficDebug") ? (par("trafficDebug").boolValue()) : (false));

        numPackets = par("numPackets");
        startTime = par("startTime");
        stopTime = par("stopTime");

        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
        {
            error("Invalid startTime/stopTime parameters");
        }

        packetLengthPar = &par("packetLength");
        sendIntervalPar = &par("sendInterval");

        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
    }
    else if (stage == 2)
    {
        sendTimer = new cMessage("sendTimer");
        scheduleNextPacket(-1);
    }
}

void IEEE802154TrafficGenerator::handleMessage(cMessage *msg)
{
    if ((msg == sendTimer) && (msg->isSelfMessage()))
    {
        if (msg->getKind() == START)
        {
            destMACAddresses.clear();
            const char *destAddrsPar = par("destAddresses");
            cStringTokenizer tokenizer(destAddrsPar);
            const char *token;
            while ((token = tokenizer.nextToken()) != NULL)
            {
                MACAddressExt result;
                tryResolve(token, result);
                if (result.isUnspecified())
                {
                    trafficEV << "Cannot resolve destination MAC address: " << token << endl;
                }
                else
                {
                    destMACAddresses.push_back(result);
                }
            }
        }

        if (!destMACAddresses.empty())
        {
            sendPacket();
            scheduleNextPacket(simTime());
        }
    }
    else
    {
        processPacket(check_and_cast<cPacket *>(msg));
    }

    if (ev.isGUI())
    {
        char buf[40];
        sprintf(buf, "rcvd: %d pks\nsent: %d pks", numReceived, numSent);
        getDisplayString().setTagArg("t", 0, buf);
    }
}

void IEEE802154TrafficGenerator::scheduleNextPacket(simtime_t previousTime)
{
    simtime_t nextTime;
    if (previousTime == -1)
    {
        nextTime = simTime() <= startTime ? startTime : simTime();
        sendTimer->setKind(START);
    }
    else
    {
        nextTime = previousTime + sendIntervalPar->doubleValue();
        sendTimer->setKind(NEXT);
    }
    if (stopTime < SIMTIME_ZERO || nextTime < stopTime)
    {
        scheduleAt(nextTime, sendTimer);
    }
}

MACAddressExt IEEE802154TrafficGenerator::chooseDestMACAddr()
{
    unsigned int k = intrand(destMACAddresses.size());
    return destMACAddresses[k];
}

void IEEE802154TrafficGenerator::sendPacket()
{
    char msgName[32];
    sprintf(msgName, "appData-%d", numSent);

    cPacket *payload = new cPacket(msgName);
    payload->setByteLength(packetLengthPar->longValue());

    MACAddressExt destMACAddr = chooseDestMACAddr();


//    controlInfo->setDestAddr(destAddr.get4());

    trafficEV << "Sending packet: ";
    printPacket(payload);
    emit(sentPkSignal, payload);
    send(payload, "trafficOut");
    numSent++;
}

void IEEE802154TrafficGenerator::printPacket(cPacket *msg)
{
    MACAddressExt src, dest;

//    if (dynamic_cast<IPv4ControlInfo *>(msg->getControlInfo()) != NULL)
//    {
//        IPv4ControlInfo *ctrl = (IPv4ControlInfo *)msg->getControlInfo();
//        src = ctrl->getSrcAddr();
//        dest = ctrl->getDestAddr();
//        protocol = ctrl->getProtocol();
//    }
//    else if (dynamic_cast<IPv6ControlInfo *>(msg->getControlInfo()) != NULL)
//    {
//        IPv6ControlInfo *ctrl = (IPv6ControlInfo *)msg->getControlInfo();
//        src = ctrl->getSrcAddr();
//        dest = ctrl->getDestAddr();
//        protocol = ctrl->getProtocol();
//    }

    trafficEV << msg << endl;
    trafficEV << "src: " << src << "  dest: " << dest << endl;
    trafficEV << "Payload length: " << msg->getByteLength() << " bytes" << endl;
}

void IEEE802154TrafficGenerator::processPacket(cPacket *msg)
{
    emit(rcvdPkSignal, msg);
    trafficEV << "Received packet: ";
    printPacket(msg);
    delete msg;
    numReceived++;
}

bool IEEE802154TrafficGenerator::tryResolve(const char *s, MACAddressExt& result)
{
    // empty address
    result = MACAddressExt();
    if (!s || !*s)
    {
        // no MAC address specified
        return true;
    }

    // handle address literal
    if (result.tryParse(s))
    {
        return true;
    }

    // must be " modulename [ { '%' interfacename | '>' destnode } ] [ '(' protocol ')' ] [ '/' ] " syntax
    // interfacename: existing_interface_of_module | 'routerId'
    // protocol: 'ipv4' | 'ipv6'
    // '/': returns mask instead address
    std::string modname, ifname, protocol, destnodename;
    const char *p = s;
    const char *endp = strchr(p, '\0');
    const char *nextsep = strpbrk(p, "%>(/");
    if (!nextsep)
    {
        nextsep = endp;
    }
    modname.assign(p, nextsep - p);

    char c = *nextsep;

    if (c == '%')
    {
        { p = nextsep + 1; nextsep = strpbrk(p, "(/"); if (!nextsep) nextsep = endp; }
        ifname.assign(p, nextsep - p);
        c = *nextsep;
    }
    else if (c == '>')
    {
        { p = nextsep + 1; nextsep = strpbrk(p, "(/"); if (!nextsep) nextsep = endp; }
        destnodename.assign(p, nextsep - p);
        c = *nextsep;
    }

    if (c == '(')
    {
        { p = nextsep + 1; nextsep = strpbrk(p, ")"); if (!nextsep) nextsep = endp; }
        protocol.assign(p, nextsep - p);
        c = *nextsep;
        if (c == ')')
        {
            { p = nextsep + 1; nextsep = p; }
            c = *nextsep;
        }
    }

    if (c)
    {
        throw cRuntimeError("MACAddressResolver: syntax error parsing address spec `%s'", s);
    }

    // find module
    cModule *mod = simulation.getModuleByPath(modname.c_str());
    if (!mod)
    {
        throw cRuntimeError("MACAddressResolver: module `%s' not found", modname.c_str());
    }


//    // check protocol
//    if (!protocol.empty())
//    {
//        if (protocol == "ipv4")
//            addrType = ADDR_IPv4;
//        else if (protocol == "ipv6")
//            addrType = ADDR_IPv6;
//        else
//            throw cRuntimeError("MACAddressResolver: error parsing address spec `%s': address type must be `(ipv4)' or `(ipv6)'", s);
//    }
//    if (netmask)
//        addrType |= ADDR_MASK;
//
//    // find interface for dest node
//    // get address from the given module/interface
//    if (!destnodename.empty())
//    {
//        cModule *destnode = simulation.getModuleByPath(destnodename.c_str());
//        if (!destnode)
//            throw cRuntimeError("MACAddressResolver: destination module `%s' not found", destnodename.c_str());
//        result = addressOf(mod, destnode, addrType);
//    }
//    else if (ifname.empty())
//        result = addressOf(mod, addrType);
//    else if (ifname == "routerId")
//        result = IPvXAddress(routerIdOf(mod)); // addrType is meaningless here, routerId is protocol independent
//    else
//        result = addressOf(mod, ifname.c_str(), addrType);
//    return !result.isUnspecified();
}
