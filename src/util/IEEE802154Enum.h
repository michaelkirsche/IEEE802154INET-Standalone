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

#ifndef IEEE_802154_ENUM_H
#define IEEE_802154_ENUM_H

enum PIBMsgTypes {
    SETTRXSTATE = 0,
    GET,
    SET,
    CCA,
    ED,
    CONF
};

enum phyState {
    phy_BUSY = CONF+1,
    phy_BUSY_RX,
    phy_BUSY_TX,
    phy_FORCE_TRX_OFF,
    phy_IDLE,
    phy_INVALID_PARAMETER,
    phy_RX_ON,
    phy_SUCCESS,
    phy_TRX_OFF,
    phy_TX_ON,
    phy_UNSUPPORT_ATTRIBUTE,
    phy_CHANGE_TRANSMITTER_POWER,
    phy_CHANGE_CHANNEL,
    phy_CHANGE_BITRATE
};

inline const char* phyStateToString(phyState x)
{
    switch (x)
    {
        case phy_BUSY:                      return "phy_BUSY";
        case phy_BUSY_RX:                   return "phy_BUSY_RX";
        case phy_BUSY_TX:                   return "phy_BUSY_TX";
        case phy_FORCE_TRX_OFF:             return "phy_FORCE_TRX_OFF";
        case phy_IDLE:                      return "phy_IDLE";
        case phy_INVALID_PARAMETER:         return "phy_INVALID_PARAMETER";
        case phy_RX_ON:                     return "phy_RX_ON";
        case phy_SUCCESS:                   return "phy_SUCCESS";
        case phy_TRX_OFF:                   return "phy_TRX_OFF";
        case phy_TX_ON:                     return "phy_TX_ON";
        case phy_UNSUPPORT_ATTRIBUTE:       return "phy_UNSUPPORT_ATTRIBUTE";
        case phy_CHANGE_TRANSMITTER_POWER:  return "phy_CHANGE_TRANSMITTER_POWER";
        case phy_CHANGE_CHANNEL:            return "phy_CHANGE_CHANNEL";
        case phy_CHANGE_BITRATE:            return "phy_CHANGE_BITRATE";
        default:                            return "[Unknown phyState]";
    }
}

enum PhyPIB_Attributes {
    currentChannel   = 0,
    channelSupported = 1,
    transmitPower    = 2,
    CCA_Mode         = 3,
    currentPage      = 4,
    maxFrameDuration = 5,
    SHRDuration      = 6,
    symbolsPerSecond = 7
};

inline const char* PhyPIB_AttributesToString(PhyPIB_Attributes u)
{
    switch (u)
    {
        case currentChannel:    return "currentChannel";
        case channelSupported:  return "channelSupported";
        case transmitPower:     return "transmitPower";
        case CCA_Mode:          return "CCA_Mode";
        case currentPage:       return "currentPage";
        case maxFrameDuration:  return "maxFrameDuration";
        case SHRDuration:       return "SHRDuration";
        case symbolsPerSecond:  return "symbolsPerSecond";
        default:                return "[Unknown PhyPIB_Attribute]";
    }
}

enum PhyPIB_Status {
    PhyPIB_SUCCESS                  = 10,
    PhyPIB_UNSUPPORTED_ATTRIBUTE    = 11,
    PhyPIB_INVALID_PARAMETER        = 12,
    PhyPIB_READ_ONLY                = 13
};

inline const char* PhyPIB_StatusToString(PhyPIB_Status z)
{
    switch (z)
    {
        case PhyPIB_SUCCESS:                return "PhyPIB_SUCCESS";
        case PhyPIB_UNSUPPORTED_ATTRIBUTE:  return "PhyPIB_UNSUPPORTED_ATTRIBUTE";
        case PhyPIB_INVALID_PARAMETER:      return "PhyPIB_INVALID_PARAMETER";
        case PhyPIB_READ_ONLY:              return "PhyPIB_READ_ONLY";
        default:                            return "[Unknown PhyPIB_Status]";
    }
}

enum mlmeRequestTypes {
    MLMEASSOCIATE       = 5,
    MLMEDISASSOCIATE    = 6,
    MLMEGET             = 7,
    MLMEGTS             = 8,
    MLMERESET           = 9,
    MLMERXENABLE        = 10,
    MLMESCAN            = 11,
    MLMECOMMSTATUS      = 12,
    MLMESET             = 13,
    MLMESTART           = 14,
    MLMESYNC            = 15,
    MLMEPOLL            = 16,
    MLMEASSOCIATERESP   = 17,
    MLMEORPHANRESP      = 18
};

inline const char* mlmeRequestTypesToString(mlmeRequestTypes w)
{
    switch (w)
    {
        case MLMEASSOCIATE:     return "MLME-ASSOCIATE";
        case MLMEDISASSOCIATE:  return "MLME-DISASSOCIATE";
        case MLMEGET:           return "MLME-GET";
        case MLMEGTS:           return "MLME-GTS";
        case MLMERESET:         return "MLME-RESET";
        case MLMERXENABLE:      return "MLME-RXENABLE";
        case MLMESCAN:          return "MLME-SCAN";
        case MLMECOMMSTATUS:    return "MLME-COMMSTATUS";
        case MLMESET:           return "MLME-SET";
        case MLMESTART:         return "MLME-START";
        case MLMESYNC:          return "MLME-SYNC";
        case MLMEPOLL:          return "MLME-POLL";
        case MLMEASSOCIATERESP: return "MLME-ASSOCIATE-RESPONCE";
        case MLMEORPHANRESP:    return "MLME-ORPHAN-RESPONSE";
        default:                return "[Unknown MLME Request Type]";
    }
}

enum MCPSStatus {
    SUCCESS = 1,
    TRANSACTION_OVERFLOW,
    TRANSACTION_EXPIRED,
    CHANNEL_ACCESS_FAILURE,
    INVALID_ADDRESS,
    INVALID_GTS,
    NO_ACK,
    COUNTER_ERROR,
    FRAME_TOO_LONG,
    UNAVAILABLE_KEY,
    UNSUPPORTED_SECURITY,
    INVALID_PARAMETER
};

inline const char* MCPSStatusToString(MCPSStatus v)
{
    switch (v)
    {
        case SUCCESS:                   return "SUCCESS";
        case TRANSACTION_OVERFLOW:      return "TRANSACTION_OVERFLOW";
        case TRANSACTION_EXPIRED:       return "TRANSACTION_EXPIRED";
        case CHANNEL_ACCESS_FAILURE:    return "CHANNEL_ACCESS_FAILURE";
        case INVALID_ADDRESS:           return "INVALID_ADDRESS";
        case INVALID_GTS:               return "INVALID_GTS";
        case NO_ACK:                    return "NO_ACK";
        case COUNTER_ERROR:             return "COUNTER_ERROR";
        case FRAME_TOO_LONG:            return "FRAME_TOO_LONG";
        case UNAVAILABLE_KEY:           return "UNAVAILABLE_KEY";
        case UNSUPPORTED_SECURITY:      return "UNSUPPORTED_SECURITY";
        case INVALID_PARAMETER:         return "INVALID_PARAMETER";
        default:                        return "[Unknown MCPSStatus]";
    }
}

enum frameType {
    Beacon  = 000,
    Data    = 001,
    Ack     = 002,
    Command = 003
};

// MAC enumerations description (Table 78 - IEEE 802.15.4-2006 Revision)
enum MACenum {
    mac_SUCCESS = 0x00,

    //--- following from Table 83 - IEEE 802.15.4-2006 Revision ---
    // Association status
    mac_PAN_at_capacity,
    mac_PAN_access_denied,
    //--------------------------------

    mac_BEACON_LOSS = 0xe0,
    mac_CHANNEL_ACCESS_FAILURE = 0xe1,
    mac_COUNTER_ERROR = 0xdb,
    mac_DENIED = 0xe2,
    mac_DISABLE_TRX_FAILURE = 0xe3,
    mac_FRAME_TOO_LONG = 0xe5,
    mac_IMPROPER_KEY_TYPE = 0xdc,
    mac_IMPROPER_SECURITY_LEVEL = 0xdd,
    mac_INVALID_ADDRESS = 0xf5,
    mac_INVALID_GTS = 0xe6,
    mac_INVALID_HANDLE = 0xe7,
    mac_INVALID_INDEX = 0xf9,
    mac_INVALID_PARAMETER = 0xe8,
    mac_LIMIT_REACHED = 0xfa,
    mac_NO_ACK = 0xe9,
    mac_NO_BEACON = 0xea,
    mac_NO_DATA = 0xeb,
    mac_NO_SHORT_ADDRESS = 0xec,
    mac_ON_TIME_TOO_LONG = 0xf6,
    mac_OUT_OF_CAP = 0xed,
    mac_PAN_ID_CONFLICT = 0xee,
    mac_PAST_TIME = 0xf7,
    mac_READ_ONLY = 0xfb,
    mac_REALIGNMENT = 0xef,
    mac_SCAN_IN_PROGRESS = 0xfc,
    mac_SECURITY_ERROR = 0xe4,
    mac_SUPERFRAME_OVERLAP = 0xfd,
    mac_TRACKING_OFF = 0xf8,
    mac_TRANSACTION_EXPIRED = 0xf0,
    mac_TRANSACTION_OVERFLOW = 0xf1,
    mac_TX_ACTIVE = 0xf2,
    mac_UNAVAILABLE_KEY = 0xf3,
    mac_UNSUPPORTED_ATTRIBUTE = 0xf4,
    mac_UNSUPPORTED_LEGACY = 0xde,
    mac_UNSUPPORTED_SECURITY = 0xdf,
    mac_UNDEFINED           // added this for handling any case not specified in the standard
};

// MAC command frames (Table 82 - IEEE 802.15.4-2006 Revision)
enum Ieee802154MacCmdType {
    //Ieee802154_UNDEFINED_CMD              = 0x00,
    Ieee802154_ASSOCIATION_REQUEST          = 0x01,
    Ieee802154_ASSOCIATION_RESPONSE         = 0x02,
    Ieee802154_DISASSOCIATION_NOTIFICATION  = 0x03,
    Ieee802154_DATA_REQUEST                 = 0x04,
    Ieee802154_PANID_CONFLICT_NOTIFICATION  = 0x05,
    Ieee802154_ORPHAN_NOTIFICATION          = 0x06,
    Ieee802154_BEACON_REQUEST               = 0x07,
    Ieee802154_COORDINATOR_REALIGNMENT      = 0x08,
    Ieee802154_GTS_REQUEST                  = 0x09,
    Ieee802154_POLL_REQUEST                 = 10
};

enum Ieee802154TxOption {
    UNDEFINED       = 0,    // for initialization purpose only, must be set to valid value (1-3) during simulation
    DIRECT_TRANS    = 1,
    INDIRECT_TRANS  = 2,
    GTS_TRANS       = 3
};

// MAC timer type
enum Ieee802154MacTimerType {
    START_PAN_COOR_TIMER,       // dynamic timer
    MAC_BACKOFF_TIMER,
    MAC_DEFER_CCA_TIMER,
    MAC_BCN_RX_TIMER,
    MAC_BCN_TX_TIMER,
    //MAC_TX_OVER_TIMER,
    MAC_ACK_TIMEOUT_TIMER,
    MAC_TX_ACK_BOUND_TIMER,
    MAC_TX_CMD_DATA_BOUND_TIMER,
    MAC_IFS_TIMER,
    MAC_TX_SD_TIMER,
    MAC_RX_SD_TIMER,
    MAC_FINAL_CAP_TIMER,
    MAC_GTS_TIMER,
    MAC_SCAN_TIMER
};

// MAC task pending type
enum Ieee802154MacTaskType {
    TP_MCPS_DATA_REQUEST = 1,
    TP_MLME_ASSOCIATE_REQUEST,
    TP_MLME_ASSOCIATE_RESPONSE,
    TP_MLME_DISASSOCIATE_REQUEST,
    TP_MLME_ORPHAN_RESPONSE,
    TP_MLME_GTS_REQUEST,
    TP_MLME_SYNC_REQUEST,
    TP_MLME_POLL_REQUEST,
    TP_CCA_CSMACA,
    TP_RX_ON_CSMACA
};

enum PDStatus {
    PD_DATA_SUCCESS = 0,
    PD_DATA_RX_ON   = 1,
    PD_DATA_TRX_OFF = 2,
    PD_DATA_BUSY_TX = 3
};

enum purgeStatus {
    purge_SUCCESS,
    purge_INVALID_HANDLE
};

enum EDval {
    ED_SUCCESS  = 0,
    ED_TRX_OFF  = 1,
    ED_TX_ON    = 2
};

enum AddrMode {             // addressing mode of the coordinator to which a poll.request is intended
    noAddr      = 0x00,
    addrShort   = 0x02,     // 16-bit short address
    addrLong    = 0x03      // 64-bit extended address
};

enum BitMasksandShifts {
    ftShift     = 13,
    secuShift   = 12,
    fpShift     = 11,
    arequShift  = 10,
    pidShift    = 9,
    damShift    = 4,
    fvShift     = 2,
    samShift    = 0,
    ftMask      = 57344,
    secuMask    = 4096,
    fpMask      = 2048,
    arequMask   = 1024,
    pidMask     = 512,
    damMask     = 48,
    fvMask      = 12,
    samMask     = 3
};

enum MlmeAssociationStatus {
    Success,
    PAN_at_capacity,
    PAN_access_denied
};

enum DisAssociateReason {
    coordinator_wishes_to_leave,
    device_wishes_to_leave
};

enum RxEnableStatus {
    rx_SUCCESS,
    rx_PAST_TIME,
    rx_ON_TIME_TOO_LONG,
    rx_INVALID_PARAMETER
};

enum ScanType { // Indicates the type of scan performed:
    scan_ED         = 0x00, // ED scan (optional for RFD).
    scan_ACTIVE     = 0x01, // active scan (optional for RFD).
    scan_PASSIVE    = 0x02, // passive scan.
    scan_ORPHAN     = 0x03  // orphan scan
};

enum ScanStatus {
    scan_SUCCESS,
    scan_LIMIT_REACHED,
    scan_NO_BEACON,
    scan_SCAN_IN_PROGRESS,
    scan_COUNTER_ERROR,
    scan_FRAME_TOO_LONG,
    scan_UNAVAILABLE_KEY,
    scan_UNSUPPORTED_SECURITY,
    scan_INVALID_PARAMETER
};

inline const char* ScanStatusToString(ScanStatus y)
{
    switch (y)
    {
        case scan_SUCCESS:              return "scan_SUCCESS";
        case scan_LIMIT_REACHED:        return "scan_LIMIT_REACHED";
        case scan_NO_BEACON:            return "scan_NO_BEACON";
        case scan_SCAN_IN_PROGRESS:     return "scan_SCAN_IN_PROGRESS";
        case scan_COUNTER_ERROR:        return "scan_COUNTER_ERROR";
        case scan_FRAME_TOO_LONG:       return "scan_FRAME_TOO_LONG";
        case scan_UNAVAILABLE_KEY:      return "scan_UNAVAILABLE_KEY";
        case scan_UNSUPPORTED_SECURITY: return "scan_UNSUPPORTED_SECURITY";
        case scan_INVALID_PARAMETER:    return "scan_INVALID_PARAMETER";
        default:                        return "[Unknown ScanStatus]";
    }
}

enum IFSType {  // indicates the type of Inter Frame Spacing
        SIFS    = 0,    // Short inter frame spacing -> waiting time after reception of short frames
        LIFS    = 1,    // Long inter frame spacing -> waiting time after reception of long frames > aMaxSIFSFrameSize
};

#endif /* IEEE_802154_ENUM_H */
