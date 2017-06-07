//
// Copyright (C) 2017 Michael Kirsche
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

// TODO: Check and update for IEEE 802.15.4-2006 revision compliance

#ifndef IEEE802154CONSTS_H_
#define IEEE802154CONSTS_H_

//---PHY sublayer constants (802.15.4-2006 Revision Table 22)---
const unsigned char  aMaxPHYPacketSize = 127;   // max PSDU size, in octets, that the PHY shall be able to receive
const unsigned char  aTurnaroundTime = 12;      // RX-to-TX or TX-to-RX max turn-around time (in symbol period)
const unsigned char  phyHeaderLength = 6;       // Bytes (currently according to 802.15.4-2003 Revision - Figure 16)

//---MAC sublayer constants (802.15.4-2006 Revision Table 85)---
const unsigned char  aBaseSlotDuration = 60; // # of symbols comprising a superframe slot of order 0
const unsigned char  aNumSuperframeSlots = 16; // # of slots contained in a superframe
const unsigned short aBaseSuperframeDuration = aBaseSlotDuration * aNumSuperframeSlots; // # of symbols comprising a superframe of order 0
// aExtendedAddress  *device specific*   // The 64 bit (IEEE) address assigned to the device.
const unsigned char  aGTSDescPersistenceTime = 4; // # of superframes that a GTS descriptor exists in the beacon frame of a PAN coordinator
const unsigned char  aMaxBeaconOverhead = 75; // max # of octets added by the MAC sublayer to the payload of its beacon frame
const unsigned char  aMaxBeaconPayloadLength = aMaxPHYPacketSize - aMaxBeaconOverhead; // max size, in octets, of a beacon payload
const unsigned char  aMaxLostBeacons = 4; // max # of consecutive beacons the MAC sublayer can miss w/o declaring a loss of synchronization
const unsigned char  aMaxFrameOverhead = 25; // max # of octets added by the MAC sublayer to its payload w/o security.
const unsigned short aMaxFrameResponseTime = 1220; // max # of symbols (or CAP symbols) to wait for a response frame
const unsigned char  aMaxMACFrameSize = aMaxPHYPacketSize - aMaxFrameOverhead; // max # of octets that can be transmitted in the MAC frame payload field
const unsigned char  aMaxSIFSFrameSize = 18; // max size of a frame, in octets, that can be followed by a SIFS period
const unsigned short aMinCAPLength = 440; // min # of symbols comprising the CAP
const unsigned short aResponseWaitTime = 32 * aBaseSuperframeDuration; // max # of symbols a device shall wait for a response command following a request command
const unsigned char  aUnitBackoffPeriod = 20; // # of symbols comprising the basic time period used by the CSMA-CA algorithm
// ------------------------------------------ //
const unsigned char  aMaxBE = 5; // max value of the backoff exponent in the CSMA-CA algorithm
const unsigned char  aMinLIFSPeriod = 40; // min # of symbols comprising a LIFS period
const unsigned char  aMinSIFSPeriod = 12; // min # of symbols comprising a SIFS period
// ------------------------------------------ //

//---Additional MAC constants (from the 802.15.4-2006 Revision)---
const unsigned char  maxGTSAllocations = 7; // max # of allocated Guranteed Time Slots (GTS) (see Sec. 7.5.7 GTS allocation and management)

//---Frequency bands and data rates (currently according 802.15.4-2003 Specs Table 1)---
// TODO: Add Specs from 2009 and newer revisions (frequencies / data & symbol rates)
const double BR_868M = 20;      // 20 kb/s   -- ch 0
const double BR_915M = 40;      // 40 kb/s   -- ch 1,2,3,...,10
const double BR_2_4G = 250;     // 250 kb/s  -- ch 11,12,13,...,26
const double SR_868M = 20;      // 20 ks/s
const double SR_915M = 40;      // 40 ks/s
const double SR_2_4G = 62.5;    // 62.5 ks/s

#endif /* IEEE802154CONSTS_H_ */
