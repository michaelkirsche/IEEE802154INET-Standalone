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
#pragma once

#ifndef IEEE802154TRAFFICGENERATOR_H_
#define IEEE802154TRAFFICGENERATOR_H_

#include <omnetpp.h>
#include <stdio.h>
#include <stdlib.h>

#include "MPDU_m.h"
#include "mcpsData_m.h"
#include "MACAddressExt.h"

#define trafficEV (ev.isDisabled()||!trafficDebug) ? EV : EV << "[802154_TRAFFIC]: " // switchable debug output

class IEEE802154TrafficGenerator : public cSimpleModule
{
    protected:
        /** @brief Debug output switch for the traffic generator module */
        bool trafficDebug = false;

        enum Kinds {START=100, NEXT};

        cMessage *sendTimer;

        int numPackets; // -1 to deactivate packet generator

        unsigned int numReceived;
        unsigned int numSent;
        static simsignal_t sentPkSignal;
        static simsignal_t rcvdPkSignal;

        simtime_t startTime;
        simtime_t stopTime;

        std::vector<MACAddressExt> destMACAddresses;

        cPar *sendIntervalPar;

        cPar *packetLengthPar;

    private:
        unsigned char msgHandle;    // simple 8-bit counter to set msduHandle (and subsequently MAC DSN) for created packets

    public:
        IEEE802154TrafficGenerator(); // Ctor
        virtual ~IEEE802154TrafficGenerator(); // Dtor;

    protected:
        int numInitStages() const { return 3; }
        virtual void initialize(int stage);

        virtual void handleMessage(cMessage *msg);

        virtual void scheduleNextPacket(simtime_t previous);

        virtual MACAddressExt chooseDestMACAddr();
        virtual void sendPacket();

        virtual void processPacket(cPacket *msg);

        virtual bool tryResolve(const char *s, MACAddressExt& result);
};

#endif /* IEEE802154TRAFFICGENERATOR_H_ */
