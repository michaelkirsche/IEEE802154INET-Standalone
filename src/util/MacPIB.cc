//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (clean-up and fixes, ported for INET 2.x)
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

#include "MacPIB.h"

MacPIB::MacPIB()
{
    macAssociatedPANCoord = false;
    macAssociationPermit = false;
    macAutoRequest = true;
    macBattLifeExt = false;
    macBattLifeExtPeriods = 6; // no real default value given just putting it in range
    macBeaconPayloadLength = 0;
    macBeaconTxTime = 0;
    macBeaconOrder = 0;
    macBSN = 0;
    macDSN = 0;
    macCoordShortAddress = 0xffff;
    macGTSPermit = true;
    macMaxBE = 5;
    macMaxCSMABackoffs = 4;
    macMaxFrameRetries = 3;
    macMinBE = 3;
    macMinLIFSPeriod = 40;
    macMinSIFSPeriod = 12;
    macPANId = 0xFFFF;
    macPromiscuousMode = false;
    macResponseWaitTime = 32;
    macRxOnWhenIdle = false;
    macSecurityEnabled = false;
    macShortAddress = 0xFFFF;
    macSuperframeOrder = 15;
    macSyncSymbolOffset = 0x100; // value for 2.4 GHz
    macTimestampSupported = true;
    macTransactionPersistenceTime = 500;
    macAckWaitDuration = 0;
}

int MacPIB::getMacAckWaitDuration()
{
    return macAckWaitDuration;
}

void MacPIB::setMacAckWaitDuration(unsigned int val)
{
    macAckWaitDuration = val;
}

bool MacPIB::getMacAssociatedPANCoord()
{
    return macAssociatedPANCoord;
}

void MacPIB::setMacAssociatedPANCoord(bool status)
{
    macAssociatedPANCoord = status;
}

bool MacPIB::getMacAssociationPermit()
{
    return macAssociationPermit;
}

void MacPIB::setMacAssociationPermit(bool status)
{
    macAssociationPermit = status;
}

bool MacPIB::getMacAutoRequest()
{
    return macAutoRequest;
}

void MacPIB::setMacAutoRequest(bool status)
{
    macAutoRequest = status;
}

bool MacPIB::getMacBattLifeExt()
{
    return macBattLifeExt;
}

void MacPIB::setMacBattLifeExt(bool status)
{
    macBattLifeExt = status;
}

unsigned short MacPIB::getMacBattLifeExtPeriods()
{
    return macBattLifeExtPeriods;
}

void MacPIB::setMacBattLifeExtPeriods(unsigned short val)
{
    if (5 < val && val < 42)
    {
        macBattLifeExtPeriods = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned BattLifePeriod is not in Range");
    }
}

std::vector<unsigned char> MacPIB::getMacBeaconPayload()
{
    return macBeaconPayload;
}

void MacPIB::setMacBeaconPayload(std::vector<unsigned char> payload)
{
    macBeaconPayload = payload;
}

unsigned short MacPIB::getMacBeaconPayloadLength()
{
    return macBeaconPayloadLength;
}

void MacPIB::setMacBeaconPayloadLength(unsigned short val)
{
    if (val < 7)
    {
        macBeaconPayloadLength = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned BeaconPayloadLength is not in Range");
    }
}

unsigned short MacPIB::getMacBeaconOrder()
{
    return macBeaconOrder;
}

void MacPIB::setMacBeaconOrder(unsigned short val)
{
    if (val < 16)
    {
        macBeaconOrder = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned BeaconOrder is not in Range");
    }
}

simtime_t MacPIB::getMacBeaconTxTime()
{
    return macBeaconTxTime;
}

void MacPIB::setMacBeaconTxTime(simtime_t val)
{
    if (val < 0x10000)
    {
        macBeaconTxTime = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned BeaconTxTime is not in Range");
    }
}
unsigned short MacPIB::getMacBSN()
{
    return macBSN;
}

void MacPIB::setMacBSN(unsigned short val)
{
    if (val < 0x100)
    {
        macBSN = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned BeaconSqnr is not in Range");
    }
}

MACAddressExt MacPIB::getMacCoordExtendedAddress()
{
    return macCoordExtendedAddress;
}

void MacPIB::setMacCoordExtendedAddress(MACAddressExt addr)
{
    macCoordExtendedAddress = addr;
}

unsigned short MacPIB::getMacCoordShortAddress()
{
    return macCoordShortAddress;
}

void MacPIB::setMacCoordShortAddress(unsigned short addr)
{
    macCoordShortAddress = addr;
}

unsigned short MacPIB::getMacDSN()
{
    return macBSN;
}

void MacPIB::setMacDSN(unsigned short val)
{
    if (val < 0x100)
    {
        macDSN = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned DataSqnr is not in Range");
    }
}

bool MacPIB::getMacGTSPermit()
{
    return macGTSPermit;
}

void MacPIB::setMacGTSPermit(bool status)
{
    macGTSPermit = status;
}

unsigned short MacPIB::getMacMaxBE()
{
    return macMaxBE;
}

void MacPIB::setMacMaxBE(unsigned short val)
{
    if (2 < val && val < 9)
    {
        macMaxBE = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned MAXBE is not in Range");
    }
}

unsigned short MacPIB::getMacMaxCSMABackoffs()
{
    return macMaxCSMABackoffs;
}

void MacPIB::setMacMaxCSMABackoffs(unsigned short val)
{
    if (val < 6)
    {
        macMaxCSMABackoffs = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned MaxCSMABackoffs is not in Range");
    }
}

simtime_t MacPIB::getMacMaxFrameTotalWaitTime()
{
    return macMaxFrameTotalWaitTime;
}

void MacPIB::setMacMaxFrameTotalWaitTime(simtime_t val)
{
    macMaxFrameTotalWaitTime = val;
}

unsigned short MacPIB::getMacMaxFrameRetries()
{
    return macMaxFrameRetries;
}

void MacPIB::setMacMaxFrameRetries(unsigned short val)
{
    if (val < 8)
    {
        macMaxFrameRetries = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned MacMaxFrameRetries is not in Range");
    }
}

unsigned short MacPIB::getMacMinBE()
{
    return macMinBE;
}

void MacPIB::setMacMinBE(unsigned short val)
{
    if (val < macMaxBE)
    {
        macMinBE = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned MinBE is larger than MaxBE");
    }
}

unsigned short MacPIB::getMacMinLIFSPeriod()
{
    return macMinLIFSPeriod;
}

void MacPIB::setMacMinLIFSPeriod(unsigned short val)
{
    macMinLIFSPeriod = val;
}

unsigned short MacPIB::getMacMinSIFSPeriod()
{
    return macMinSIFSPeriod;
}

void MacPIB::setMacMinSIFSPeriod(unsigned short val)
{
    macMinSIFSPeriod = val;
}

unsigned short MacPIB::getMacPANId()
{
    return macPANId;
}

void MacPIB::setMacPANId(unsigned short val)
{
    macPANId = val;
}

bool MacPIB::getMacPromiscuousMode()
{
    return macPromiscuousMode;
}

void MacPIB::setMacPromiscuousMode(bool status)
{
    macPromiscuousMode = status;
}

simtime_t MacPIB::MacResponseWaitTime()
{
    return macResponseWaitTime;
}

void MacPIB::setMacResponseWaitTime(simtime_t val)
{
    if (val < 65 && val > 1)
    {
        macResponseWaitTime = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned ResponseWaitTime is not in Range");
    }
}

bool MacPIB::getMacRxOnWhenIdle()
{
    return macRxOnWhenIdle;
}

void MacPIB::setMacRxOnWhenIdle(bool status)
{
    macRxOnWhenIdle = status;
}

bool MacPIB::getMacSecurityEnabled()
{
    return macSecurityEnabled;
}

void MacPIB::setMacSecurityEnabled(bool status)
{
    macSecurityEnabled = status;
}

unsigned short MacPIB::getMacShortAddress()
{
    return macShortAddress;
}

void MacPIB::setMacShortAddress(unsigned short addr)
{
    macShortAddress = addr;
}

unsigned short MacPIB::getMacSuperframeOrder()
{
    return macSuperframeOrder;
}

void MacPIB::setMacSuperframeOrder(unsigned short val)
{
    if (val < 16)
    {
        macSuperframeOrder = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned MacSuperframeOrder is not in Range");
    }
}

unsigned short MacPIB::getMacSyncSymbolOffset()
{
    return macSyncSymbolOffset;
}

void MacPIB::setMacSyncSymbolOffset(unsigned short val)
{
    macSyncSymbolOffset = val;
}

bool MacPIB::getMacTimestampSupported()
{
    return macTimestampSupported;
}

void MacPIB::setMacTimestampSupported(bool status)
{
    macTimestampSupported = status;
}

simtime_t MacPIB::getMacTransactionPersistenceTime()
{
    return macTransactionPersistenceTime;
}

void MacPIB::setMacTransactionPersistenceTime(simtime_t val)
{
    if (val < 0x10000)
    {
        macTransactionPersistenceTime = val;
    }
    else
    {
        throw cRuntimeError("[802154MAC-PIB]: Assigned macTransactionPersistenceTime is not in Range");
    }
}
