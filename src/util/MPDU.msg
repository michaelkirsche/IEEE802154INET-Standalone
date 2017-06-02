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

cplusplus {{
    #include "MACAddressExt.h"
    #include "IEEE802154Fields.h"
    #include "IEEE802154Enum.h"
}};

class noncobject MACAddressExt;
class noncobject SuperframeSpec;
class noncobject GTSDescriptor;
class noncobject PendingAddrFields;
class noncobject DevCapability;
class noncobject Ash;
class noncobject PAN_ELE;

enum Ieee802154MacCmdType;
enum AddrMode;
enum MlmeAssociationStatus;
enum DisAssociateReason;
enum MACenum;
enum RxEnableStatus;
enum ScanType;
enum ScanStatus;

// see the generated C++ header for more info
packet mpdu  
{  
    unsigned short fcs;         // 16-Bit Frame Check Sequence
    Ash ash;                    // Auxiliary Security Header
    // ... MAC frame payload is encapsulated ...
    MACAddressExt src;          // 0, 16 or 64-Bit Source Address
    unsigned short srcPANid;    // 0 or 16-Bits for Source PAN Identifier
    MACAddressExt dest;         // 0, 16 or 64-Bit Destination Address
    unsigned short destPANid;   // 0 or 16-Bits for Destination PAN Identifier
    unsigned char sqnr=0;       // 8-Bit Sequence number
    unsigned short fcf=0;       // 16-Bit Frame Control Field
    bool isGTS = false;		    // Added extra for GTS logic
    bool isIndirect=false;      // Added extra for indirect transmissions
}

packet beaconFrame extends mpdu
{
    SuperframeSpec sfSpec;                  // Superframe specifications
    GTSDescriptor gtsList[7];	
    PendingAddrFields paFields;             // includes numLong numShort and List
}

packet beaconNotify
{    
    // SDU is encapsulated
    unsigned char BSN;                      // 0x00–0xff, beacon sequence number
    PAN_ELE PANDescriptor;                  // the PANDescriptor for the received beacon
    PendingAddrFields PendAddrSpec;         // includes numLong numShort and List
    unsigned char sduLength;                // 0 – aMaxBeaconPayloadLength (52) (which is aMaxPHYPacketSize (127) – aMaxBeaconOverhead (75))
}

packet CmdFrame extends mpdu
{
    int cmdType @enum(Ieee802154MacCmdType);// refer to IEEE802154Enum.h       
}

packet RealignCmd extends CmdFrame 
{
    unsigned short PANId;
    unsigned short CoordShortAddr;
    unsigned int LogicalChannel;            // logical channel on which to start using new superframe configuration
    unsigned short ShortAddr;
    unsigned char ChannelPage;              // 0 - 31, channel page on which to start using new superframe configuration
}

packet GTSCmd extends CmdFrame
{
    GTSDescriptor GTSCharacteristics;
}

packet DisAssoCmd extends CmdFrame
{
    unsigned char DisassociateReason @enum(DisAssociateReason); // refer to IEEE802154Enum.h
}

packet AssoCmdreq extends CmdFrame
{
    DevCapability CapabilityInformation;
}

packet AssoCmdresp extends CmdFrame
{
    unsigned short shortAddress;
    unsigned short status @enum(MlmeAssociationStatus); // refer to IEEE802154Enum.h
}

packet AckFrame
{
    unsigned short fcs;     // 16-Bit Frame Check Sequence
    unsigned char sqnr;     // 8-Bit Sequence Number
    unsigned short fcf;     // 16-Bit Framce Control Field
}

packet DisAssociation
{
    unsigned char DeviceAddrMode @enum(AddrMode);   // refer to IEEE802154Enum.h
    unsigned short DevicePANId;
    MACAddressExt DeviceAddress;
    unsigned char DisassociateReason @enum(DisAssociateReason); // refer to IEEE802154Enum.h
    bool TxIndirect;
    unsigned short status @enum(MACenum);
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

packet Association
{
    MACAddressExt addr; // used different in request and response for coordinator // device addr
    DevCapability CapabilityInformation;
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

packet AssociationRequest extends Association
{
    unsigned int LogicalChannel;            // logical channel on which to start using new superframe configuration
    unsigned char ChannelPage;              // 0 - 31, channel page on which to start using new superframe configuration
    unsigned char CoordAddrMode @enum(AddrMode);
    unsigned short CoordPANId;              // 0x0000–0xfffe, PAN identifier of the coordinator to which we want to associate
    MACAddressExt CoordAddress;        
}

packet AssociationResponse extends Association
{
    // Short Address ist also stored in the long address
    unsigned short status @enum(MlmeAssociationStatus);     // refer to IEEE802154Enum.h    
}

packet AssociationConfirm extends Association
{
    // Short Address ist also stored in the long address
    unsigned short status @enum(MlmeAssociationStatus);     // refer to IEEE802154Enum.h        
}

packet GTSMessage
{
    GTSDescriptor GTSCharacteristics;
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

packet GTSIndication extends GTSMessage
{
    unsigned short deviceAddr;
}

packet GTSConfirm
{
    GTSDescriptor gts;
    unsigned short status @enum(MACenum);       // refer to IEEE802154Enum.h
}

message MLMEReset
{
    // also used for Confirm true is success
    bool setDefaultPIB;
}

message RxEnableRequest
{
    bool DeferPermit;                       // true if requested operation can be deferred until next superframe
    
    // TODO needs to be defined in symbols to make it adapt to different PHYs
    simtime_t RxOnTime;                     // number of symbols measured from the start of the superframe before the receiver is to be enabled or disabled, 
                                            // a 24-Bit value, to be ignored for non-beacon-enabled PANs 
    unsigned int RxOnDuration;              // number of symbols for which the receiver is to be enabled
}

message RxEnableConfirm
{
    int status @enum(RxEnableStatus);
}

message ScanRequest
{
    unsigned char ScanType @enum(ScanType); // refer to IEEE802154Enum.h
    unsigned int ScanChannels;              // 27-Bit indicating the channels to be scanned
    unsigned int ScanDuration;              // The time spent scanning each channel is 
    unsigned char ChannelPage;              // 0 - 31, channel page on which to perform scan
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

message ScanConfirm
{
    unsigned char status @enum(ScanStatus); // refer to IEEE802154Enum.h
    unsigned char ScanType @enum(ScanType); // 0x00-0x03, refer to IEEE802154Enum.h
    unsigned char ChannelPage;              // 0 - 31, channel page on which to perform scan
    unsigned int UnscannedChannels;         // 27-Bit indicating which channels weren't scanned in the given request, not valid for ED scans
    unsigned short ResultListSize;          // range is implementation specific 
    unsigned char EnergyDetectList[];       // 0x00-0xff for each
    PAN_ELE  PANDescriptorList[];           // Elements of PANDescriptor - compare Table 55 of Spec. 802.15.4-2006
}

packet OrphanIndication
{
    MACAddressExt OrphanAddress;            // Extended 64-bit IEEE address
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006           
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

packet OrphanResponse extends OrphanIndication
{
    unsigned short ShortAddress;            // 16-bit short address allocated to the orphaned device if associated with coordinator
    bool AssociatedMember;                  // TRUE if orphaned device is associated with coordinator, FALSE otherwise
}

message StartRequest
{
    unsigned short PANId;                   // 0x0000-0xffff, PAN identifier 
    unsigned int LogicalChannel;            // logical channel on which to start using new superframe configuration
    unsigned char ChannelPage;              // 0 - 31, channel page on which to start using new superframe configuration
    unsigned int StartTime;                 // 0x000000–0xffffff, 24-bit value indicating time at which beacon transmission commences
    unsigned char BeaconOrder;              // 0 - 15, how often the beacon is transmitted
    unsigned char SuperframeOrder;          // 0 - BO or 15, length of the active period of the superframe
    bool PANCoordinator;                    // if true device becomes PAN coordinator of new PAN, if false device begins using new configuration
    bool BatteryLifeExtension;              // if true disable receiver for macBattLifeExtPeriods backoff periods after IFS following a beacon
    bool CoordRealignment;                  // if true coordinator realigment command is to be transmitted priod to changing superframe structure
    unsigned char CoordRealignSecurityLevel;// 0x00–0x07, security level used for realignment command
    unsigned char CoordRealignKeyIdMode;    // 0x00–0x03, mode to identify the key to be used
    unsigned long CoordRealignKeySource;    // depending on KeyidMode max set of uint8_t[8]
    unsigned char CoordRealignKeyIndex;     // 0x01–0xff, index of the key to be used
    unsigned char BeaconSecurityLevel;      // 0x00–0x07, security level used for beacon frames
    unsigned char BeaconKeyIdMode;          // 0x00–0x03, mode to identify the key to be used
    unsigned long BeaconKeySource;          // depending on KeyidMode max set of uint8_t[8]
    unsigned char BeaconKeyIndex;           // 0x01–0xff, index of the key to be used
}

message StartConfirm
{ 
    unsigned short status @enum(MACenum);   // refer to IEEE802154Enum.h
}

message SyncRequest
{  
    unsigned int LogicalChannel;            // logical channel on which to start using new superframe configuration
    unsigned char ChannelPage;              // 0 - 31, channel page on which to start using new superframe configuration
    bool TrackBeacon;                       // true if synchronizing with every beacon, false if synchronize only with next beacon
}

message SyncIndication
{
    unsigned short LossReason @enum(MACenum);   // refer to IEEE802154Enum.h
    unsigned short PANId;                   // 0x0000–0xffff, PAN identifier
    unsigned int LogicalChannel;            // logical channel on which to start using new superframe configuration
    unsigned char ChannelPage;              // 0 - 31, channel page on which to start using new superframe configuration
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006           
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

message PollRequest
{
    unsigned char CoordAddrMode @enum(AddrMode);    // addressing mode of the coordinator, 16-bit short or 64-bit extended address
    unsigned short CoordPANId;              // 0x0000–0xfffe, PAN identifier of the coordinator which is polled
    MACAddressExt CoordAddress;             // address, type as specified by CoordAddrMode
    unsigned char SecurityLevel;            // 0x00–0x07, compare Table 95 in Spec. 802.15.4-2006           
    unsigned char KeyIdMode;                // 0x00–0x03, mode to identify the key to be used
    unsigned long KeySource;                // depending on KeyidMode max set of uint8_t[8]
    unsigned char KeyIndex;                 // 0x01–0xff, index of the key to be used
}

message PollConfirm
{
    unsigned short status @enum(MACenum);   // refer to IEEE802154Enum.h
}
