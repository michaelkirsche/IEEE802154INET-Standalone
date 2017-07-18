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
        // initialize the debug output bool from NED parameter value
        trafficDebug = (hasPar("trafficDebug") ? (par("trafficDebug").boolValue()) : (false));

        numReceived = 0;
        WATCH(numReceived);
    }
}

void IEEE802154TrafficSink::handleMessage(cMessage *msg)
{
    processPacket(check_and_cast<cPacket *>(msg));

    if (ev.isGUI())
    {
        char buf[32];
        sprintf(buf, "rcvd: %d pks", numReceived);
        getDisplayString().setTagArg("t", 0, buf);
    }
}

void IEEE802154TrafficSink::processPacket(cPacket *msg)
{
    emit(rcvdPkSignal, msg);

    if (dynamic_cast<mcpsDataInd*>(msg))
    {
        mcpsDataInd* ind = check_and_cast<mcpsDataInd*>(msg);
        cPacket* payload = ind->decapsulate();
        trafficEV << "Got MCPS-Data.indication for Message #" << (int) (ind->getDSN()) << " from " << (ind->getSrcAddr().str()) << endl;
        trafficEV << "Received payload: " << payload << endl;
    } // (dynamic_cast<mcpsDataInd*>(msg))
    else
    {
        trafficEV << "Received packet: " << msg << endl;
        trafficEV << "Payload length: " << msg->getByteLength() << " bytes" << endl;
    }

    delete (msg);
    numReceived++;
}
