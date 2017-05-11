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

//  TODO:  Preamble length and Start of Frame Delimiter have to be adapted to different PHYs / frequencies 

cplusplus {{
    #include "IEEE802154Fields.h"
    #include "IEEE802154Enum.h"
}}

enum phyState;
enum PDStatus;
enum PhyPIB_Status;
enum PhyPIB_Attributes;

packet pdDataInd
{
    unsigned char psduLength;       // ≤ aMaxPHYPacketSize
    unsigned char ppduLinkQuality;  // 0x00–0xff
    // PSDU Payload is just encapsulated
}

packet ppdu 
{
    unsigned char Preamble[4];      // Synchronization Header (SHR) 
    unsigned char SFD;              // Start of Frame Delimiter (8-bit except ASK)
    unsigned char PHR;              // PHY Header containing 7 Bits Frame Length & 1 Bit Reserved
}

packet edConf
{
	unsigned char status @enum(phyState);  // refer to IEEE802154Enum.h
	unsigned char EnergyLevel;             // 0x00–0xff
}

message GetRequest
{
    unsigned short PIBattr @enum(PhyPIB_Attributes);   // refer to IEEE802154Enum.h
    unsigned short PIBind;
}

message GetConfirm extends GetRequest
{ 
    unsigned short status @enum(PhyPIB_Status); // refer to IEEE802154Enum.h
    double value;
}

message SetRequest
{
    unsigned short PIBattr @enum(PhyPIB_Attributes);    // refer to IEEE802154Enum.h
    unsigned short PIBind;
    double value;
}

message SetConfirm
{
    unsigned short PIBattr @enum(PhyPIB_Attributes);    // refer to IEEE802154Enum.h
    unsigned short status @enum(PhyPIB_Status); // refer to IEEE802154Enum.h
}
