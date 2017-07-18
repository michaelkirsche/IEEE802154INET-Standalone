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

    msgHandle = intrand(255);   // 8-bit msg handle (sequence number)

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
        ASSERT((packetLengthPar->longValue() <= 102) && (packetLengthPar->longValue() > 0)); // max 802.15.4 frame size is 127 octets, min header size is 23, FCS is 2

        sendIntervalPar = &par("sendInterval");
        ASSERT(sendIntervalPar > 0);    // send interval should be larger than 0

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
    if ((msg == sendTimer) && (msg->isSelfMessage()))   // send timer
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
    else    // packets arrived from lower layer
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
    char msgName[20];
    sprintf(msgName, "MAC-Payload-%d", numSent);

    cPacket *payload = new cPacket(msgName);
    payload->setByteLength(packetLengthPar->longValue());

    mcpsDataReq* dataReq = new mcpsDataReq("MCPS-DATA.request");
    dataReq->encapsulate(payload);

    ASSERT(msgHandle <= 255);   // sequence number in MPDU is 8-bit / unsigned char
    dataReq->setMsduHandle(msgHandle);
    (msgHandle < 255) ? msgHandle++ : msgHandle = 0;    // check if 8-bit sequence number needs to roll over

    dataReq->setMsduLength(payload->getByteLength());
    ASSERT(getModuleByPath("^.Network.stdLLC") != NULL);    // getModuleByPath shall return the MAC module
    //fullPath = 'net.IEEE802154Nodes[0].Network.stdLLC.TXoption' (string)
    dataReq->setTxOptions(getModuleByPath("^.Network.stdLLC")->par("TXoption").longValue());

    MACAddressExt destMACAddr = chooseDestMACAddr();
    dataReq->setDstAddr(destMACAddr);

    trafficEV << "Packet generated: " << payload << endl;
    trafficEV << "Destination Address is: " << (dataReq->getDstAddr().str()) << " | MSDU Handle: " << (int) (dataReq->getMsduHandle()) << endl;
    trafficEV << "MSDU Length: " << (int) (dataReq->getMsduLength()) << " bytes" << endl;

    emit(sentPkSignal, payload);
    send(dataReq, "trafficOut");
    numSent++;
}

void IEEE802154TrafficGenerator::processPacket(cPacket *msg)
{
    emit(rcvdPkSignal, msg);

    if (dynamic_cast<mcpsDataInd*>(msg))
    {
        mcpsDataInd* ind = check_and_cast<mcpsDataInd*>(msg);
        cPacket* payload = ind->decapsulate();
        trafficEV << "Got MCPS-Data.indication for Message #" << (int) (ind->getDSN()) << " from " << (ind->getSrcAddr().str()) << endl;
        trafficEV << "Received payload: " << payload << endl;
    } // (dynamic_cast<mcpsDataInd*>(msg))
    else if (dynamic_cast<mcpsDataConf*>(msg))
    {
        mcpsDataConf* conf = check_and_cast<mcpsDataConf*>(msg);

        trafficEV << "Got MCPS-Data.confirm for Message #" << (int) (conf->getMsduHandle()) << " with status: " << MCPSStatusToString(MCPSStatus(conf->getStatus())) << endl;

        if (ev.isGUI())
        {
            char buf[22];
            if (conf->getStatus() == SUCCESS)
            {
                this->setDisplayString("i=block/join,#80FF00,45;i2=status/green");
                sprintf(buf, "status/green");
            }
            else if (conf->getStatus() == NO_ACK)
            {
                this->setDisplayString("i=block/join,##FF0000,45;i2=status/red");
                sprintf(buf, "status/red");
            }
            getModuleByPath("^")->getDisplayString().setTagArg("i2", 0, buf);
        }
    }
    else {
        trafficEV << "received a packet: " << msg << endl;
    }

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

    // TODO no further parsing or checking at the moment
    return false;

//    // must be " modulename [ { '%' interfacename | '>' destnode } ] [ '(' protocol ')' ] [ '/' ] " syntax
//    // interfacename: existing_interface_of_module | 'routerId'
//    // protocol: 'ipv4' | 'ipv6'
//    // '/': returns mask instead address
//    std::string modname, ifname, protocol, destnodename;
//    const char *p = s;
//    const char *endp = strchr(p, '\0');
//    const char *nextsep = strpbrk(p, "%>(/");
//    if (!nextsep)
//    {
//        nextsep = endp;
//    }
//    modname.assign(p, nextsep - p);
//
//    char c = *nextsep;
//
//    if (c == '%')
//    {
//        { p = nextsep + 1; nextsep = strpbrk(p, "(/"); if (!nextsep) nextsep = endp; }
//        ifname.assign(p, nextsep - p);
//        c = *nextsep;
//    }
//    else if (c == '>')
//    {
//        { p = nextsep + 1; nextsep = strpbrk(p, "(/"); if (!nextsep) nextsep = endp; }
//        destnodename.assign(p, nextsep - p);
//        c = *nextsep;
//    }
//
//    if (c == '(')
//    {
//        { p = nextsep + 1; nextsep = strpbrk(p, ")"); if (!nextsep) nextsep = endp; }
//        protocol.assign(p, nextsep - p);
//        c = *nextsep;
//        if (c == ')')
//        {
//            { p = nextsep + 1; nextsep = p; }
//            c = *nextsep;
//        }
//    }
//
//    if (c)
//    {
//        throw cRuntimeError("MACAddressResolver: syntax error parsing address spec `%s'", s);
//    }
}
