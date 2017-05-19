//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (clean-up, updated 802.15.4 revision, ported for INET 2.x)
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

// Class representing MAC PIB as listed in Standard description Table 86

#include <stdlib.h>
#include "MACAddressExt.h"

#ifndef MACPIB_H_
#define MACPIB_H_

class MacPIB
{
    public:
        MacPIB();
        virtual ~MacPIB(){};    // Std. Dtor

        /** @brief Getters and Setters for the whole MPIB */
        int getMacAckWaitDuration();
        void setMacAckWaitDuration(unsigned int val);
        bool getMacAssociatedPANCoord();
        void setMacAssociatedPANCoord(bool status);
        bool getMacAssociationPermit();
        void setMacAssociationPermit(bool status);
        bool getMacAutoRequest();
        void setMacAutoRequest(bool status);
        bool getMacBattLifeExt();
        void setMacBattLifeExt(bool status);
        unsigned short getMacBattLifeExtPeriods();
        void setMacBattLifeExtPeriods(unsigned short val);
        std::vector<unsigned char> getMacBeaconPayload();
        void setMacBeaconPayload(std::vector<unsigned char> payload);
        unsigned short getMacBeaconPayloadLength();
        void setMacBeaconPayloadLength(unsigned short val);
        unsigned short getMacBeaconOrder();
        void setMacBeaconOrder(unsigned short val);
        simtime_t getMacBeaconTxTime();
        void setMacBeaconTxTime(simtime_t val);
        unsigned short getMacBSN();
        void setMacBSN(unsigned short val);
        MACAddressExt getMacCoordExtendedAddress();
        void setMacCoordExtendedAddress(MACAddressExt addr);
        unsigned short getMacCoordShortAddress();
        void setMacCoordShortAddress(unsigned short addr);
        unsigned short getMacDSN();
        void setMacDSN(unsigned short val);
        bool getMacGTSPermit();
        void setMacGTSPermit(bool status);
        unsigned short getMacMaxBE();
        void setMacMaxBE(unsigned short val);
        unsigned short getMacMaxCSMABackoffs();
        void setMacMaxCSMABackoffs(unsigned short val);
        simtime_t getMacMaxFrameTotalWaitTime();
        void setMacMaxFrameTotalWaitTime(simtime_t val);
        unsigned short getMacMaxFrameRetries();
        void setMacMaxFrameRetries(unsigned short val);
        unsigned short getMacMinBE();
        void setMacMinBE(unsigned short val);
        unsigned short getMacMinLIFSPeriod();
        void setMacMinLIFSPeriod(unsigned short val);
        unsigned short getMacMinSIFSPeriod();
        void setMacMinSIFSPeriod(unsigned short val);
        unsigned short getMacPANId();
        void setMacPANId(unsigned short val);
        bool getMacPromiscuousMode();
        void setMacPromiscuousMode(bool status);
        simtime_t MacResponseWaitTime();
        void setMacResponseWaitTime(simtime_t val);
        bool getMacRxOnWhenIdle();
        void setMacRxOnWhenIdle(bool status);
        bool getMacSecurityEnabled();
        void setMacSecurityEnabled(bool status);
        unsigned short getMacShortAddress();
        void setMacShortAddress(unsigned short addr);
        unsigned short getMacSuperframeOrder();
        void setMacSuperframeOrder(unsigned short val);
        unsigned short getMacSyncSymbolOffset();
        void setMacSyncSymbolOffset(unsigned short val);
        bool getMacTimestampSupported();
        void setMacTimestampSupported(bool status);
        simtime_t getMacTransactionPersistenceTime();
        void setMacTransactionPersistenceTime(simtime_t val);

    private:
        unsigned int macAckWaitDuration;
        bool macAssociatedPANCoord;
        bool macAssociationPermit;
        bool macAutoRequest;
        bool macBattLifeExt;
        unsigned short int macBattLifeExtPeriods; // Range 6 - 41
        /*
         * This value is dependent on the supported PHY and is the sum of three terms:
         *
         Term 1: The value , where x is the maximum value of macMinBE in BLE
         mode (equal to two). This term is thus equal to 3 backoff periods.

         Term 2: The duration of the initial contention window
         length. This term is thus equal to 2 backoff periods.

         Term 3: The Preamble field length and the SFD field length of the supported PHY,
         summed together and rounded up (if necessary) to an integer number of backoff periods.
         */

        std::vector<unsigned char> macBeaconPayload; // MAXPhyPAcketsize - MaxBeaconOverhead = 52 maximum Octets
        unsigned short macBeaconPayloadLength; // length in Octets -> Range 0 - 6

        /*
         * Specification of how often the coordinator transmits its beacon.
         * If BO = 15, the coordinator will not transmit a periodic beacon.
         */
        unsigned short macBeaconOrder;

        simtime_t macBeaconTxTime;
        unsigned short macBSN;
        MACAddressExt macCoordExtendedAddress;  // An extended 64-bit IEEE address
        unsigned short macCoordShortAddress;    // the 16-Bit short address
        unsigned short macDSN;
        bool macGTSPermit;
        unsigned short macMaxBE; // Range 3 -8
        unsigned short macMaxCSMABackoffs; // Range 0-5
        /*
         * The maximum number of CAP symbols in a beacon-enabled PAN, or symbols in a
         * nonbeacon-enabled PAN, to wait either for a frame intended as a response to a
         * data request frame or for a broadcast frame following a beacon with the Frame
         * Pending subfield set to one
         */
        simtime_t macMaxFrameTotalWaitTime; // TODO Equation 14 in Standard should be set by upper layer
        unsigned short macMaxFrameRetries;
        unsigned short macMinBE; // Range 0 - macMaxBE
        unsigned short macMinLIFSPeriod; // min number of Symbols forming a LIFS period
        unsigned short macMinSIFSPeriod; // min number of Symbols forming a SIFS period
        unsigned long macPANId;
        bool macPromiscuousMode; // indication of whether the MAC sublayer is in a promiscuous (receive all) mode
        simtime_t macResponseWaitTime; // Range 2 - 64
        bool macRxOnWhenIdle;
        bool macSecurityEnabled;
        unsigned short macShortAddress;
        unsigned short macSuperframeOrder; // Range 0 - 15
        unsigned short macSyncSymbolOffset;
        bool macTimestampSupported;
        /*
         * @brief The maximum time that a transaction is stored by a coordinator and indicated in its beacon
         */
        simtime_t macTransactionPersistenceTime;
};

#endif /* MACPIB_H_ */
