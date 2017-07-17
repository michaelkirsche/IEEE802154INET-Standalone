//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2014 Michael Kirsche   (clean-up, adaptation for newer 802.15.4 revisions, ported for INET 2.x)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
#pragma once

#ifndef LLC_H_
#define LLC_H_

#include "omnetpp.h"
#include "mcpsData_m.h"
#include "MPDU_m.h"
#include "IEEE802154Fields.h"

#include "IPvXAddress.h"
#include "IPv6ControlInfo.h"

#define llcEV (ev.isDisabled()||!llcDebug) ? EV : EV << "[802154_LLC]: " // switchable debug output

class llc : public cSimpleModule
{

    public:
        llc();
        virtual ~llc();

    protected:
        /** @brief Debug output switch for the LLC module */
        bool llcDebug = false;

        virtual void initialize(int stage);
        virtual int numInitStages() const { return 3; }

        virtual void handleMessage(cMessage *msg);
        MACAddressExt tokenDest(cMessage* msg);    // returns 64-Bit MAC address generated from the given msg
        void genAssoReq();
        void genPollReq();
        void genScanReq();
        void genOrphanResp(OrphanIndication* oi);
        static bool firstDevice; // first device that receives a "Scan confirm" without results shall announce that it is PAN-Coordinator

    private:
        unsigned short logicalChannel;

        /** @brief Conversion enabled for non-802.15.4-compatible application layers*/
        bool convertingMode;

        /** @brief The 3 bits (b0, b1, b2) indicate the transmission options for this MSDU.
         *
         * For b0: 1 = acknowledged transmission, 0 = unacknowledged transmission.
         * For b1: 1 = GTS transmission, 0 = CAP transmission for a beacon-enabled PAN.
         * For b2: 1 = indirect transmission, 0 = direct transmission.
         * For a non-beacon-enabled PANs, bit b1 should always be set to 0.
         */
        unsigned char TXoption;

        unsigned char msgHandle;    // simple 8-bit counter to set msduHandle (and subsequently MAC DSN) for created packets

        simtime_t pollFreq;

        bool associateStarted;      // association process started
        bool associateSuccess;      // We associate on first beacon notify until successful

        unsigned char coordAddrMode;
        unsigned short coordPANId;
        MACAddressExt coordAddress; // shared by both 16 bit short address or 64 bit extended address

        // --- Initial Scan Variables
        int scanChannels;   // 27 bit, choose each bit for the channel to be scanned
        double scanDuration;
        int scanPage;
        int scanType;

        StartRequest* startMsg; // MLME-START.request message

        cMessage* selfMsg;      // Message for start up on rng

        cMessage* pollTimer;    // Poll Timer
};

#endif /* LLC_H_ */
