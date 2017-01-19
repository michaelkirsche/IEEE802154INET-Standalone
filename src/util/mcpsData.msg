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

// Container for all MCPS Data Messages

cplusplus {{
    #include "IEEE802154Enum.h"
    #include "MACAddressExt.h" 
}};

enum MCPSStatus;
class noncobject MACAddressExt;
enum AddrMode;
enum purgeStatus;

// This is the format that the SSCS layer should send to our MAC Entity
packet mcpsDataReq {                   // Range of each field
    unsigned char SrcAddrMode@enum(AddrMode); // 0x00–0x03
	unsigned char DstAddrMode@enum(AddrMode); // 0x00–0x03
	unsigned short DstPANId;           // 0x0000–0xffff
	MACAddressExt DstAddr;			
	unsigned char msduLength;          // <= aMaxMACPayloadSize
	//msdu, Payload just encapsulated
	unsigned char msduHandle;          // 0x00–0xff 
	unsigned char TxOptions;           // actuallay a 3-Bit field 000 - 111
	unsigned char SecurityLevel;	   // 0x00–0x07
	unsigned char KeyIdMode;           // 0x00–0x03
	unsigned long KeySource;           // depending on KeyidMode max set of uint8_t[8]			
	unsigned char KeyIndex;            // 0x01–0xff
}

packet mcpsDataInd extends mcpsDataReq {

	unsigned short SrcPANId;           // 0x0000–0xffff
	MACAddressExt SrcAddr;			
	unsigned char mpduLinkQuality;     // 0x00–0xff
	unsigned char DSN;                 // 0x00–0xff	
	simtime_t Timestamp;               // 0x000000–0xffffff -> optional is set via ->setTimestamp()
}

packet mcpsDataConf {
    // added for MSCPS confirm 
	unsigned char msduHandle;          // 0x00–0xff  -->  actually just an unsigned char 8-Bit value but mapping to OMNeT msg ID requires long 
	unsigned char status @enum(MCPSStatus);    // see IEEE802154Enum.h
	simtime_t Timestamp;			       // 0x000000–0xffffff -> optional is set via ->setTimestamp()
}

packet MaUnitdata {
	MACAddressExt SrcAddr;
	MACAddressExt DstAddr;
	// RoutingInformation NULL
	// data 			encapsulated
	// priority,
	// ServiceClass // NULL 
}

packet mcpsPurgeReq {
	unsigned char msduHandle;          // 0x00–0xff  -->  actually just an unsigned char 8-Bit value but mapping to OMNeT msg ID requires long
}

packet mcpsPurgeConf extends mcpsPurgeReq {
	unsigned char status @enum(purgeStatus);   // see IEEE802154Enum.h
}
