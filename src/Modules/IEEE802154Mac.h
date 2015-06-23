//
// Copyright (C) 2008 Feng Chen         (original IEEE 802.15.4 MAC model)
// Copyright (C) 2013 Matti Schnurbusch (adaptation and extension of Feng Chen's model)
// Copyright (C) 2015 Michael Kirsche   (clean-up, ported for INET 2.x)
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

#ifndef MAC_H_
#define MAC_H_

#include <omnetpp.h>
#include <stdio.h>
#include <stdlib.h>

#include "PhyPIB.h"
#include "MacPIB.h"

#include "PPDU_m.h"
#include "MPDU_m.h"

#include "macFrameControlField.h"
#include "MACAddressExt.h"
#include "IEEE802154Enum.h"
#include "RadioState.h"
#include "IEEE802154Fields.h"
#include "NotificationBoard.h"
#include "mcpsData_m.h"

#define macEV (ev.isDisabled()||!macDebug) ? EV : EV << "[802154_MAC]: "    // switchable debug output

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
const unsigned char  aMaxFrameRetries = 3; // max # of retries allowed after a transmission failures
const unsigned char  aMaxMACFrameSize = 127 - aMaxFrameOverhead; // max # of octets that can be transmitted in the MAC frame payload field
const unsigned char  aMaxSIFSFrameSize = 18; // max size of a frame, in octets, that can be followed by a SIFS period
const unsigned short aMinCAPLength = 440; // min # of symbols comprising the CAP
const unsigned short aResponseWaitTime = 32 * aBaseSuperframeDuration; // max # of symbols a device shall wait for a response command following a request command
const unsigned char  aUnitBackoffPeriod = 20; // # of symbols comprising the basic time period used by the CSMA-CA algorithm
// ------------------------------------------ //
const unsigned char  aMaxBE = 5; // max value of the backoff exponent in the CSMA-CA algorithm
const unsigned char  aMinLIFSPeriod = 40; // min # of symbols comprising a LIFS period
const unsigned char  aMinSIFSPeriod = 12; // min # of symbols comprising a SIFS period
// ------------------------------------------ //

//---Frequency bands and data rates (currently according 802.15.4-2003 Specs Table 1)---
// TODO: Add Specs from 2009 and newer revisions (frequencies / data & symbol rates)
const double BR_868M = 20;      // 20 kb/s   -- ch 0
const double BR_915M = 40;      // 40 kb/s   -- ch 1,2,3,...,10
const double BR_2_4G = 250;     // 250 kb/s  -- ch 11,12,13,...,26
const double SR_868M = 20;      // 20 ks/s
const double SR_915M = 40;      // 40 ks/s
const double SR_2_4G = 62.5;    // 62.5 ks/s

// MAC Commands with fixed size (currently according to 802.15.4-2003 Specs)
#define SIZE_OF_802154_ASSOCIATION_RESPONSE             29  // Fig 50: MHR (23) + Payload (4) + FCS (2)
#define SIZE_OF_802154_DISASSOCIATION_NOTIFICATION      21  // Fig 51: MHR (17) + Payload (2) + FCS (2)
#define SIZE_OF_802154_PANID_CONFLICT_NOTIFICATION      26  // Fig 53: MHR (23) + Payload (1) + FCS (2)
#define SIZE_OF_802154_ORPHAN_NOTIFICATION              20  // Fig 54: MHR (17) + Payload (1) + FCS (2)
#define SIZE_OF_802154_BEACON_REQUEST                   10  // Fig 55: MHR (7)  + Payload (1) + FCS (2)
#define SIZE_OF_802154_GTS_REQUEST                      11  // Fig 57: MHR (7)  + Payload (2) + FCS (2)
#define SIZE_OF_802154_ACK                              5   // Fig 46: MHR (3)  + FCS (2)

struct taskPending
{
        taskPending()
        {
            init();
        }

        inline void init()
        {
            mcps_data_request = false;
            mcps_data_request_STEP = 0;
            CCA_csmaca = false;
            CCA_csmaca_STEP = 0;
            RX_ON_csmaca = false;
            RX_ON_csmaca_STEP = 0;
        }

        bool &taskStatus(Ieee802154MacTaskType task)
        {
            switch (task)
            {
                case TP_MCPS_DATA_REQUEST:
                    return mcps_data_request;
                case TP_CCA_CSMACA:
                    return CCA_csmaca;
                case TP_RX_ON_CSMACA:
                    return RX_ON_csmaca;
                default:
                    ASSERT(0);
                    return RX_ON_csmaca;
            }
        }

        unsigned char &taskStep(Ieee802154MacTaskType task)
        {
            switch (task)
            {
                case TP_MCPS_DATA_REQUEST:
                    return mcps_data_request_STEP;
                case TP_CCA_CSMACA:
                    return CCA_csmaca_STEP;
                case TP_RX_ON_CSMACA:
                    return RX_ON_csmaca_STEP;
                default:
                    ASSERT(0);
                    return RX_ON_csmaca_STEP;
            }
        }

        char *taskFrFunc(Ieee802154MacTaskType task)
        {
            switch (task)
            {
                case TP_MCPS_DATA_REQUEST:
                    return mcps_data_request_frFunc;
                default:
                    ASSERT(0);
                    return mcps_data_request_frFunc;
            }
            return mcps_data_request_frFunc;
        }

        //----------------
        bool mcps_data_request;
        unsigned char mcps_data_request_STEP;
        char mcps_data_request_frFunc[81];
        Ieee802154TxOption mcps_data_request_TxOption;
        mpdu* mcps_data_request_pendPkt;

        bool CCA_csmaca;
        unsigned char CCA_csmaca_STEP;
        //----------------
        bool RX_ON_csmaca;
        unsigned char RX_ON_csmaca_STEP;

        //----------------
};

class IEEE802154Mac : public cSimpleModule, public INotifiable
{

    public:
        IEEE802154Mac();
        ~IEEE802154Mac();

        /** @brief Counter to go through device list for setting up destination address since we have no real application */
        int counter;

    protected:
        /** @brief Debug output switch for the IEEE 802.15.4 MAC module */
        bool macDebug = false;

        void initialize(int stage);

        virtual int numInitStages() const
        {
            return 3;
        }
        void finish();

        /**
         * @name Message handlers
         */
        void handleMessage(cMessage *msg);
        void handleUpperMsg(cMessage *msg);
        void handleLowerMsg(cMessage *msg);
        void handleSelfMsg(cMessage* msg);
        void handleBeacon(mpdu *frame);
        void handleData(mpdu* frame);
        void handleAck(cMessage* frame);
        void handleCommand(mpdu* frame);
        void handle_PLME_SET_TRX_STATE_confirm(phyState state);
        void handle_PD_DATA_confirm(phyState status);
        void handle_PLME_CCA_confirm(phyState status);
        void setDefMpib();
        void genMLMEResetConf();
        void genMLMEDisasConf(MACenum status);
        void genDisAssoCmd(DisAssociation* disAss, bool direct);
        void sendDataConf();
        void genPollConf(MACenum status);
        void genStartConf(MACenum status);
        bool filter(mpdu* pdu);
        virtual void receiveChangeNotification(int category, const cPolymorphic *details);
        mpdu *generateMPDU(cMessage *msg);
        void genACK(mpdu* frame, bool fp);
        void sendMCPSDataConf(MACenum status, long id);
        void sendMCPSDataIndication(mpdu* rxData);
        void genSetTrxState(phyState state);
        void genCCARequest();
        void genBeaconInd(mpdu* frame);
        void genAssoResp(MlmeAssociationStatus status, AssoCmdreq* tmpAssoReq);
        void genOrphanInd();
        void sendDown(mpdu* frame);
        void reqMsgBuffer();
        void genGTSConf(GTSDescriptor gts, MACenum status);
        unsigned short calcFCS(mpdu* pdu, cMessage *msg, bool calcFlag, int headerSize);
        void genScanConf(ScanStatus status);
        mpdu* findRxMsg(MACAddressExt dest);
        mpdu* getTxMsg();

        /**
         * @name CSMA related handlers and variables
         */
        void csmacaEntry(char pktType);
        void csmacaResume();
        void csmacaCancel();
        void csmacaStart(bool firsttime, mpdu* frame, bool ackReq);
        void csmacaCallBack(phyState status);
        void csmacaReset(bool bcnEnabled);
        simtime_t csmacaAdjustTime(simtime_t wtime);
        simtime_t csmacaLocateBoundary(bool toParent, simtime_t wtime);
        bool csmacaCanProceed(simtime_t wtime, bool afterCCA);
        void csmaca_handle_RX_ON_confirm(phyState status);
        void csmacaTrxBeacon(char trx);
        int calFrmByteLength(mpdu* mpdu);
        int calMHRByteLength(unsigned char mhr, bool secu);
        simtime_t calDuration(mpdu* mpdu);
        bool toParent(mpdu* mpdu);
        void doScan();

        /**
         * @name Timer starters
         */
        void startBackoffTimer(simtime_t wtime);
        void startdeferRxEnableTimer(simtime_t wtime);
        void startRxOnDurationTimer(simtime_t wtime);
        void startDeferCCATimer(simtime_t wtime);
        void startBcnRxTimer();
        void startBcnTxTimer(bool txFirstBcn, simtime_t startTime);
        void startAckTimeoutTimer();
        void startTxAckBoundTimer(simtime_t wtime);
        void startTxCmdDataBoundTimer(simtime_t wtime);
        void startIfsTimer(bool sifs);
        void startTxSDTimer();
        void startRxSDTimer();
        void startGtsTimer(simtime_t wtime);
        void startFinalCapTimer(simtime_t wtime);
        void startScanTimer(simtime_t wtime);

        /**
         * @name GTS related variables
         */
        bool gtsCanProceed();
        void gtsScheduler();
        unsigned char gts_request_cmd(unsigned short macShortAddr, unsigned char length, bool isReceive);
        simtime_t getFinalCAP(char trxType);
        MACAddressExt associate_request_cmd(MACAddressExt extAddr, const DevCapability& capaInfo);

        /**
         * @name Timer Handlers
         */
        void handleBackoffTimer();
        void handledeferRxEnableTimer();
        void handleRxOnDurationTimer();
        void handleDeferCCATimer();
        void handleBcnRxTimer();
        void handleBcnTxTimer();
        void handleAckTimeoutTimer();
        void handleTxAckBoundTimer();
        void handleTxCmdDataBoundTimer();
        void handleIfsTimer();
        void handleSDTimer();
        void handleGtsTimer();
        void handleFinalCapTimer();
        void handleScanTimer();

        double getRate(char bs);
        /*
         * @name State control and task management functions
         */
        void dispatch(phyState pStatus, const char *frFunc, phyState req_state = phy_SUCCESS, MACenum mStatus = mac_SUCCESS);
        void taskSuccess(char type, bool csmacaRes = true);
        void taskFailed(char type, MACenum status, bool csmacaRes = true);
        void checkTaskOverflow(Ieee802154MacTaskType task);
        void FSM_MCPS_DATA_request(phyState pStatus = phy_SUCCESS, MACenum mStatus = mac_SUCCESS);
        void resetTRX();

    private:

        NotificationBoard *nb;
        // MAC PAN Information Base
        MacPIB mpib;
        // PHY PAN Information Base
        PhyPIB ppib;
        // Data Transfer Mode: 1 = direct; 2 = indirect; 3 = GTS
        Ieee802154TxOption dataTransMode;
        // Msg Sequence Number
        int sequ;
        // Frame Type: Beacon = 000, Data = 001, Ack = 2, Command = 3
        frameType ft;
        macFrameControlField *fcf;
        unsigned short fc;
        bool trxState;
        unsigned int headerSize;
        cMessage* selfMsg;
        //int bitrate;

        // Message Types
        std::map<std::string, PIBMsgTypes> mappedMsgTypes;
        std::map<std::string, mlmeRequestTypes> mappedMlmeRequestTypes;

        // Variables used for channel scanning
        ScanType scanType; // see IEEE802154Enum.h
        unsigned int scanChannels; // 27 bit indicating the channels to be scanned
        unsigned int scanDuration; // The time spent scanning each channel is
        // [aBaseSuperframeDuration * (2n + 1)] symbols, where n is the value of the
        // ScanDuration parameter
        unsigned int* scanEnergyDetectList;
        PAN_ELE* scanPANDescriptorList;
        unsigned short channelPage;
        bool scanning;

        bool startNow;
        bool Poll;
        unsigned int scanSteps;     // Channel list to go through
        unsigned short scanCount;   // current channels that is scanned
        unsigned int scanStep;      // the step in the scanning procedure
        unsigned short scanResultListSize;

        // PAN Variables
        bool associated;
        bool isCoordinator;
        bool isFFD;
        bool syncLoss;

        // 64-Bit Extended MAC-Address
        MACAddressExt myMacAddr;
        // PAN identifier
        unsigned short myPANiD;

        std::string panCoorName;

        taskPending taskP;

        // Container used by coordinator to store info of associated devices
        typedef std::map<unsigned short, DevCapability> DeviceList;
        DeviceList deviceList;

        DevCapability capability;

        // transmit or receive GTS, only used by devices
        bool isRecvGTS;

        // payload of data frames transmitted in GTS, copied from traffic module
        int gtsPayload;

        bool ack4Gts;
        bool mlmeReset;
        bool ack4Asso;
        unsigned int txBuffSlot;
        unsigned int rxBuffSlot;

        // Receive Buffer for Coordinator
        cArray rxBuff;

        // Frame Types for temporary save for frames currently being transmitted
        mpdu* txPkt;

        // for beacon frames to be transmitted without CSMA/CA
        beaconFrame* txBeacon;

        // for beacon or command frames coming from the upper layer, to be transmitted with CSMA/CA
        mpdu* txBcnCmdUpper;

        // for beacon or command frames responding to receiving a packet,to be transmitted with CSMA/CA
        mpdu* txBcnCmd;

        // for data frames to be transmitted
        mpdu* txData;

        // for data frames to be transmitted in GTS
        mpdu* txGTS;

        // small tx Buffer for responses on messages on MAC layer
        cArray txBuff;
        // for ack frames to be transmitted (no wait)
        AckFrame* txAck;

        // Store Disassociation for Confirm parameters and FSM
        DisAssociation* tmpDisAss;

        GTSCmd* txGTSReq;

        // for frames currently being CSMA/CA performed,one of txBcnCmdUpper, txBcnCmd or txData
        mpdu* txCsmaca;

        //set when csmacaStart is called for first time, cleared when csmacaCallBack or csmacaCancel is called
        mpdu* tmpCsmaca;

        // received beacon frames, only used by mlme_scan_request and mlme_rx_enable_request (TBD)
        mpdu* rxBeacon;

        // buffer for received data frames
        mpdu* rxData;

        // buffer for received command frames
        CmdFrame* rxCmd;

        // deferred Rx-Enable Message
        RxEnableRequest* deferRxEnable;

        // CSMA-CA backoff status
        unsigned short int backoffStatus; // 0: no backoff; 1: backoff successful; 2: backoff failed; 99: is backing off

        // number of retries for TXing a beacon or command frame in txBcnCmd
        unsigned short int numBcnCmdRetry;

        // number of retries for TXing a beacon or command frame in txBcnCmdUpper
        unsigned short int numBcnCmdUpperRetry;

        // number of retries for TXing a data frame in txData
        unsigned short int numDataRetry;

        // number of retries for TXing a data frame in txGTS
        unsigned short int numGTSRetry;

        // true while a packet being transmitted at PHY
        bool inTransmission;

        // true while MLME ordered a RX-Enable
        bool mlmeRxEnable;

        // true while a sent beacon or command frame in txBcnCmd is waiting for ACK
        bool waitBcnCmdAck;

        // true while a sent beacon or command frame in txBcnCmdUpper is waiting for ACK
        bool waitBcnCmdUpperAck;

        // true while a sent frame in txData is waiting for ACK
        bool waitDataAck;

        // true while waiting for the Association ACK
        bool waitAssCmdAck;

        // true while a sent frame in txGTS is waiting for ACK
        bool waitGTSAck;

        // store new value of final superframe slot in the CAP after updating GTS settings
        // and put into effect when next beacon is transmitted
        unsigned char tmp_finalCap;

        // index of current running GTS, 99 means not in GTS
        unsigned char indexCurrGts;

        // number of GTS descriptors being maintained
        unsigned char gtsCount;

        // list of GTS descriptors for all existing GTS being maintained */
        GTSDescriptor gtsList[7];

        simtime_t gtsTransDuration;

        unsigned char gtsStartSlot;

        // number of superframe slots for the GTS, calculated in handleBeacon()  */
        unsigned char gtsLength;

        unsigned short numTxAckInactive;

        unsigned char NB;
        unsigned char CW;
        unsigned char BE;

        int bPeriodsLeft; // backoff periods left
        // num of incoming beacons lost in a row */
        unsigned char bcnLossCounter;
        // num of Collisions
        unsigned short numCollision;

        bool waitGTSConf;
        bool csmacaAckReq;
        bool csmacaWaitNextBeacon;

        // flag for using beacon or not */
        bool beaconEnabled;

        // indicating a beacon frame waiting for transmission, suppress all other transmissions */
        bool beaconWaitingTx;

        // outging superframe specification used by coordinators
        SuperframeSpec txSfSpec;

        // incoming superframe specification used by devices
        SuperframeSpec rxSfSpec;

        /**
         * @name Timer Messages
         */

        // backoff timer for CSMA-CA
        cMessage* backoffTimer;

        // timer for locating backoff boundary before sending a CCA request
        cMessage* deferCCATimer;

        // timer for deferred RX-Enable
        cMessage* deferRxEnableTimer;

        // timer for channel / ED scan
        cMessage* scanTimer;

        // timer for Receive On Duration
        cMessage* RxOnDurationTimer;

        // timer for tracking beacons
        cMessage* bcnRxTimer;

        // timer for transmitting beacon periodically
        cMessage* bcnTxTimer;

        // timer for timer for ACK timeout
        cMessage* ackTimeoutTimer;

        // timer for locating backoff boundary before TXing ACK if beacon-enabled
        cMessage* txAckBoundTimer;

        // timer for locating backoff boundary before TXing Command or data if beacon-enabled
        cMessage* txCmdDataBoundTimer;

        // timer for delay of IFS after receiving a data or command packet
        cMessage* ifsTimer;

        // timer for indicating being in the active period of outgoing (TXing) superframe
        cMessage* txSDTimer;

        // timer for indicating being in the active period of incoming (RXed) superframe
        cMessage* rxSDTimer;

        // timer for indicating the end of CAP and the starting of CFP
        // used only by devices to put radio into sleep at the end of CAP if my GTS is not the first one in the CFP
        cMessage* finalCAPTimer;

        // timer for scheduling of GTS, shared by both PAN coordinator and devices
        cMessage* gtsTimer;

        simtime_t lastTime_bcnRxTimer;
        bool txNow_bcnTxTimer;

        //true while in active period of the outgoing superframe
        bool inTxSD_txSDTimer;

        // true while in active period of the incoming superframe
        bool inRxSD_rxSDTimer;

        /** for PAN coordinator: index of GTS descriptor in the GTS list
         *  that GTS timer is currently scheduling for its starting;
         *  for devices: 99 indicating currently being in my GTS
         */
        unsigned short int index_gtsTimer;

        /**
         * @name Beacon related variables
         */

        // beacon order of incoming superframe
        unsigned short rxBO;

        // superframe order of incoming superframe
        unsigned short rxSO;

        // duration (in symbol) of a outgoing superframe slot (aBaseSlotDuration * 2^mpib.macSuperframeOrder)
        unsigned int txSfSlotDuration;

        // duration (in symbol) of a incoming superframe slot (aBaseSlotDuration * 2^rxSO)
        unsigned int rxSfSlotDuration;

        // duration (in backoff periods) of latest outgoing beacon
        unsigned char txBcnDuration;

        // duration (in backoff periods) of latest incoming beacon
        unsigned char rxBcnDuration;

        // length (in s) of a unit of backoff period, aUnitBackoffPeriod/phy_symbolrate
        simtime_t bPeriod;

        // the time that the last beacon was received updated right after the beacon is received at MAC
        simtime_t bcnRxTime;

        // the scheduled time that the latest beacon should have arrived
        simtime_t schedBcnRxTime;

        // current bit rate at PHY
        double phy_bitrate;

        // current symbol rate at PHY
        double phy_symbolrate;

        // Temporary requested state to set in PHY
        phyState trx_state_req;

        /**
         * @name Statistical variables
         */
        // number of data packets received from upper layer, counted in <handleUpperMsg()>
        unsigned short numUpperPkt;

        // number of data packets from upper layer dropped by MAC due to busy MAC or invalid size (e.g. oversize), counted in <handleUpperMsg()>
        unsigned short numUpperPktLost;

        // number of incoming beacons lost, counted in <handleBcnRxTimer()>
        unsigned short numLostBcn;

        // number of transmitted beacons, counted in <taskSuccess('b')>
        unsigned short numTxBcnPkt;

        // number of successfully transmitted data frames, counted in <taskSuccess('d')>
        unsigned short numTxDataSucc;

        // number of data frames that MAC failed to transmit, counted in <taskFailed()>
        unsigned short numTxDataFail;

        // number of successfully transmitted data frames in GTS, counted in <taskSuccess('g')>
        unsigned short numTxGTSSucc;

        // number of data frames that MAC failed to transmit in GTS, counted in <taskFailed()>
        unsigned short numTxGTSFail;

        // number of transmitted ACK frames, counted in <taskSuccess()>
        unsigned short numTxAckPkt;

        // number of received beacons, counted in <handleBeacon()>
        unsigned short numRxBcnPkt;

        // number of received data frames, counted in <MCPS_DATA_indication()>
        unsigned short numRxDataPkt;

        // number of received data frames in GTS, counted in <MCPS_DATA_indication()>
        unsigned short numRxGTSPkt;

        // count only ACKs received before timeout, for both Command and Data in <handleAck()>
        unsigned short numRxAckPkt;

        // outgoing PAN descriptor transmitted used by coordinators (TBD)
        PAN_ELE txPanDescriptor;

        // incoming PAN descriptor transmitted used by devices (TBD)
        PAN_ELE rxPanDescriptor;
};

#endif /* MAC_H_ */
