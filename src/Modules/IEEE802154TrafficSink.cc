//
// Copyright (C) 2004 Andras Varga      (IPvXTrafSink in INET 2.x)
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

#include <IEEE802154TrafficSink.h>

Define_Module(IEEE802154TrafficSink);

simsignal_t IEEE802154TrafficSink::rcvdPkSignal = registerSignal("rcvdPk");

void IEEE802154TrafficSink::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == 0)
    {
        // initialize the debug ouput bool from NED parameter value
        trafficDebug = (hasPar("trafficDebug") ? (par("trafficDebug").boolValue()) : (false));

        numReceived = 0;
        WATCH(numReceived);
    }
    // TODO another initialization stage necessary? If not, remove other code
//    else if (stage == 3)
//    {
//        int protocol = par("protocol");
//        IPSocket ipSocket(gate("ipOut"));
//        ipSocket.registerProtocol(protocol);
//        ipSocket.setOutputGate(gate("ipv6Out"));
//        ipSocket.registerProtocol(protocol);
//    }
}

void IEEE802154TrafficSink::handleMessage(cMessage *msg)
{
    // TODO check and cast into MAC frame format
    processPacket(check_and_cast<cPacket *>(msg));

    if (ev.isGUI())
    {
        char buf[32];
        sprintf(buf, "rcvd: %d pks", numReceived);
        getDisplayString().setTagArg("t", 0, buf);
    }
}

// TODO change msg type from cPacket to correct MAC frame type
void IEEE802154TrafficSink::processPacket(cPacket *msg)
{
    emit(rcvdPkSignal, msg);
    printPacket(msg);
    delete (msg);
    numReceived++;
}

// TODO change msg type from cPacket to correct MAC frame type
void IEEE802154TrafficSink::printPacket(cPacket *msg)
{
    // TODO add correct "printing of packet information for IEEE 802.15.4 MAC packets

//    IPvXAddress src, dest;
//    int protocol = -1;
//
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

    // TODO add more info printers
    trafficEV << "Received packet: " << msg << endl;
    trafficEV << "Payload length: " << msg->getByteLength() << " bytes" << endl;
//
//    if (protocol != -1)
//    {
//        trafficEV << "src: " << src << "  dest: " << dest << "  protocol=" << protocol << "\n";
//    }
}

