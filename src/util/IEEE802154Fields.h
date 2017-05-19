//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (adaptation for newer 802.15.4 revisions, ported for INET 2.x)
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

#ifndef IEEE802154FIELDS_H_
#define IEEE802154FIELDS_H_

#include "IEEE802154Enum.h"
#include "MACAddressExt.h"

struct MAC_ACL
{
        MACAddressExt ACLExtendedAddress;
        unsigned short ACLShortAddress;
        unsigned short ACLPANId;
        unsigned char ACLSecurityMaterialLength;
        unsigned char* ACLSecurityMaterial;
        unsigned char ACLSecuritySuite;
};

struct SecurityControl
{
        unsigned char Seculevel;
        unsigned char KeyIdMode;
};

struct KeyIdField
{
        unsigned long KeySource;
        unsigned char KeyIndex;
};

struct Ash
{
        SecurityControl secu;
        unsigned int FrameCount;
        KeyIdField KeyIdentifier;
};

// Elements of PAN descriptor (Table 41)
struct PAN_ELE
{
        unsigned char CoordAddrMode;
        unsigned short CoordPANId;

        MACAddressExt CoordAddress;      // shared by both 16 bit short address or 64 bit extended address

        unsigned char LogicalChannel;
        //UINT_16           SuperframeSpec;     // ignored, store in txSfSpec or rxSfSpec instead
        bool GTSPermit;
        unsigned char LinkQuality;
        //simtime_t     TimeStamp;              // ignored, use bcnRxTime instead
        bool SecurityUse;
        unsigned char ACLEntry;
        bool SecurityFailure;
        //add one field for cluster tree
        //UINT_16   clusTreeDepth;
};

// Superframe specification (SS) (16 bits)
struct SuperframeSpec
{
        unsigned char BO;       // beacon order (0 - 15)
        unsigned int BI;        // beacon interval --> BI = aBaseSuperframeDuration * 2^BO (in symbols)
        unsigned char SO;       // superframe order (0 - 15)
        unsigned int SD;        // superframe duration --> SD = aBaseSuperframeDuration * 2^SO (in symbols)
        unsigned char finalCap; // final superframe slot utilized by the CAP
        bool battLifeExt;       // battery life extension
        bool panCoor;           // PAN coordinator
        bool assoPmt;           // association permit
};

// Device capability information field
struct DevCapability
{
        bool alterPANCoor;
        bool FFD;
        MACAddressExt addr;
        const char* powSrc;
        bool recvOnWhenIdle;
        bool secuCapable;
        bool alloShortAddr;
        const char* hostName;       // only for convenience
};

struct GTSDescriptor
{
        unsigned short devShortAddr;// device short address
        unsigned char startSlot;    // starting slot
        unsigned char length;       // length in slots
        bool isRecvGTS;             // transmit or receive in GTS, not defined here is spec, but we put it here just for convenience
        bool isTxPending;           // there is a data pending for transmitting
        bool Type;                  // true if it's a request
};

struct PendingAddrFields
{
        unsigned char numShortAddr;     // number of short addresses pending
        unsigned char numExtendedAddr;  // number of extended addresses pending
        MACAddressExt addrList[7];      // pending address list (shared by short/extended addresses)
};

#endif
