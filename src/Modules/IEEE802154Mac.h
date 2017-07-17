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

#include "MacPIB.h"

#include "PPDU_m.h"
#include "MPDU_m.h"
#include "mcpsData_m.h"

#include "MACAddressExt.h"
#include "IEEE802154Consts.h"
#include "IEEE802154Enum.h"
#include "IEEE802154Fields.h"
#include "RadioState.h"             // from INET - provides RadioState enums
#include "PhyControlInfo_m.h"       // from INET - provides PhyIndication enums
#include "NotificationBoard.h"      // from INET - provides NotificationBoard access

#define macEV (ev.isDisabled()||!macDebug) ? EV : EV << "[802154_MAC]: "    // switchable debug output

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
            mcps_data_request_TxOption = (Ieee802154TxOption) 0; // needs to be changed to a valid option (1 - 3)
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
                {
                    return mcps_data_request;
                }
                case TP_CCA_CSMACA:
                {
                    return CCA_csmaca;
                }
                case TP_RX_ON_CSMACA:
                {
                    return RX_ON_csmaca;
                }
                default:
                {
                    ASSERT(0);
                    return RX_ON_csmaca;
                }
            }
        }

        unsigned char &taskStep(Ieee802154MacTaskType task)
        {
            switch (task)
            {
                case TP_MCPS_DATA_REQUEST:
                {
                    return mcps_data_request_STEP;
                }
                case TP_CCA_CSMACA:
                {
                    return CCA_csmaca_STEP;
                }
                case TP_RX_ON_CSMACA:
                {
                    return RX_ON_csmaca_STEP;
                }
                default:
                {
                    ASSERT(0);
                    return RX_ON_csmaca_STEP;
                }
            }
        }

        char *taskFrFunc(Ieee802154MacTaskType task)
        {
            switch (task)
            {
                case TP_MCPS_DATA_REQUEST:
                {
                    return mcps_data_request_frFunc;
                }
                default:
                {
                    ASSERT(0);
                    return mcps_data_request_frFunc;
                }
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
        virtual int numInitStages() const { return 3; }

        void finish();

        /**
         * @name Message handlers
         */
        void handleMessage(cMessage* msg);

        // XXX to be deleted after final testing
        void handleUpperMsg(cMessage* msg); // XXX refactor into separate functions for MCPS and MLME
        void handleUpperMLMEMsg(cMessage* msg);
        void handleUpperMCPSMsg(cMessage* msg);

        void handleLowerPLMEMsg(cMessage* msg);
        void handleLowerPDMsg(cMessage* msg);

        void handleSelfMsg(cMessage* msg);
        void handleBeacon(mpdu* frame);

        void handleData(mpdu* frame);
        void handleAck(cMessage* frame);
        void handleCommand(mpdu* frame);

        void handle_PLME_SET_TRX_STATE_confirm(phyState state);
        void handle_PLME_CCA_confirm(phyState status);
        void handle_PLME_GET_confirm(cMessage* msg);
        void handle_PLME_SET_confirm(cMessage* msg);

        void handle_PD_DATA_confirm(phyState status);

        void setDefMpib();
        void calcMacAckWaitDuration();
        void genMLMEResetConf();
        void genMLMEDisasConf(MACenum status);
        void genDisAssoCmd(DisAssociation* disAss, bool direct);
        void sendDataConf();
        void genPollConf(MACenum status);
        void genStartConf(MACenum status);
        bool filter(mpdu* pdu);
        virtual void receiveChangeNotification(int category, const cPolymorphic *details);
        unsigned short genFCF(frameType ft, bool secu, bool fp, bool arequ, bool pid, AddrMode dam, unsigned short fv, AddrMode sam);
        void genACK(unsigned char dsn, bool fp);
        void sendMCPSDataConf(MACenum status, unsigned char msdu);
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
        unsigned char calFrameByteLength(cPacket* mpdu);
        unsigned char calMacHeaderByteLength(unsigned char mhr, bool secu);
        simtime_t calDuration(cPacket* mpdu);
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
        void startIfsTimer(IFSType ifsType);
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

        /**
         * @name Get/Set functions for PHY / PHY-PIB values
         */
        double getRate(char bs);
        void getRadioChannel();
        void setRadioChannel(unsigned short newRadioChannel);
        void getCurrentChannelPage();
        void setCurrentChannelPage(unsigned int newChannelPage);
        void getSHRDuration();
        void getSymbolsPerOctet();

        /**
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
        Ieee802154TxOption dataTransMode; // see IEEE802154Enum.h
        frameType ft; // see IEEE802154Enum.h
        unsigned short fc;
        bool trxState;
        unsigned int headerSize;
        cMessage* selfMsg;

        // Message Types
        std::map<std::string, PIBMsgTypes> mappedMsgTypes;
        std::map<std::string, mlmeRequestTypes> mappedMlmeRequestTypes;

        // Variables used for channel scanning
        ScanType scanType; // see IEEE802154Enum.h
        unsigned int scanChannels; // 27 bit indicating the channels to be scanned
        unsigned int scanDuration; // The time spent scanning each channel is
        // [aBaseSuperframeDuration * (2n + 1)] symbols, where n is the value of the ScanDuration parameter
        unsigned char scanEnergyDetectList[26] = { 0 };
        PAN_ELE scanPANDescriptorList[26];
        unsigned short channelPage;
        bool scanning;

        bool startNow;
        bool Poll;

        unsigned int scanSteps;     // Channel list to go through
        unsigned short scanCount;   // current channels that is scanned
        unsigned short scanStep;    // the step in the scanning procedure
        unsigned short scanResultListSize;

        // PAN Variables
        bool associated;
        bool associationProcessStarted;
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

        // for beacon or command frames responding to receiving a packet, to be transmitted with CSMA/CA
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
        unsigned short backoffStatus; // 0: no backoff; 1: backoff successful; 2: backoff failed; 99: is backing off

        // number of retries for TXing a beacon or command frame in txBcnCmd
        unsigned short numBcnCmdRetry;

        // number of retries for TXing a beacon or command frame in txBcnCmdUpper
        unsigned short numBcnCmdUpperRetry;

        // number of retries for TXing a data frame in txData
        unsigned short numDataRetry;

        // number of retries for TXing a data frame in txGTS
        unsigned short numGTSRetry;

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

        // list of GTS descriptors for all existing GTS being maintained - max # defined as constant
        GTSDescriptor gtsList[maxGTSAllocations];

        simtime_t gtsTransDuration;

        unsigned char gtsStartSlot;

        // number of superframe slots for the GTS, calculated in handleBeacon()
        unsigned char gtsLength;

        unsigned short numTxAckInactive;

        unsigned char NB;
        unsigned char CW;
        unsigned char BE;

        // backoff periods left
        int bPeriodsLeft;

        // num of incoming beacons lost in a row
        unsigned char bcnLossCounter;

        bool waitGTSConf;
        bool csmacaAckReq;
        bool csmacaWaitNextBeacon;

        // flag for using beacon or not
        bool beaconEnabled;

        // indicating a beacon frame waiting for transmission, suppress all other transmissions
        bool beaconWaitingTx;

        // outging superframe specification used by coordinators
        SuperframeSpec txSfSpec = { //
                                    /*.BO=*/ 0, // initial Beacon Order
                                    /*.BI=*/ 0, // initial Beacon Interval
                                    /*.SO=*/ 0, // initial Superframe Order
                                    /*.SD=*/ 0, // Initial Superframe Duration
                                    /*.finalCAP=*/ 0, // Initial final Superframe slot used by CAP
                                    /*.battLifeExt*/ false, // Initial bool for battery life extension
                                    /*.panCoor*/ false, // Initial PAN coordinator yes/no decision
                                    /*.assoPmt*/ false // Initial Association permit yes/no decision
                                  };

        // incoming superframe specification used by devices
        SuperframeSpec rxSfSpec = { //
                                    /*.BO=*/ 0, // initial Beacon Order
                                    /*.BI=*/ 0, // initial Beacon Interval
                                    /*.SO=*/ 0, // initial Superframe Order
                                    /*.SD=*/ 0, // Initial Superframe Duration
                                    /*.finalCAP=*/ 0, // Initial final Superframe slot used by CAP
                                    /*.battLifeExt*/ false, // Initial bool for battery life extension
                                    /*.panCoor*/ false, // Initial PAN coordinator yes/no decision
                                    /*.assoPmt*/ false // Initial Association permit yes/no decision
                                  };

        /** @name Timer Messages */

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

        /** @name Beacon related variables */

        // beacon order of incoming superframe
        unsigned short rxBO = 0;

        // superframe order of incoming superframe
        unsigned short rxSO = 0;

        // duration (in symbol) of a outgoing superframe slot (aBaseSlotDuration * 2^mpib.macSuperframeOrder)
        unsigned int txSfSlotDuration = 0;

        // duration (in symbol) of a incoming superframe slot (aBaseSlotDuration * 2^rxSO)
        unsigned int rxSfSlotDuration = 0;

        // duration (in backoff periods) of latest outgoing beacon
        unsigned char txBcnDuration = 0;

        // duration (in backoff periods) of latest incoming beacon
        unsigned char rxBcnDuration = 0;

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

        // current radio channel at PHY
        unsigned short phy_channel;

        // Temporary requested state to set in PHY
        phyState trx_state_req;

        /** @name Statistical variables */
        // number of data packets received from upper layer, counted in <handleUpperMsg()>
        unsigned long numUpperPkt;

        // number of data packets from upper layer dropped by MAC due to busy MAC or invalid size (e.g. oversize), counted in <handleUpperMsg()>
        unsigned long numUpperPktLost;

        // number of incoming beacons lost, counted in <handleBcnRxTimer()>
        unsigned long numLostBcn;

        // number of transmitted beacons, counted in <taskSuccess('b')>
        unsigned long numTxBcnPkt;

        // number of successfully transmitted data frames, counted in <taskSuccess('d')>
        unsigned long numTxDataSucc;

        // number of data frames that MAC failed to transmit, counted in <taskFailed()>
        unsigned long numTxDataFail;

        // number of successfully transmitted data frames in GTS, counted in <taskSuccess('g')>
        unsigned long numTxGTSSucc;

        // number of data frames that MAC failed to transmit in GTS, counted in <taskFailed()>
        unsigned long numTxGTSFail;

        // number of transmitted ACK frames, counted in <taskSuccess()>
        unsigned long numTxAckPkt;

        // number of received beacons, counted in <handleBeacon()>
        unsigned long numRxBcnPkt;

        // number of received data frames, counted in <MCPS_DATA_indication()>
        unsigned long numRxDataPkt;

        // number of received data frames in GTS, counted in <MCPS_DATA_indication()>
        unsigned long numRxGTSPkt;

        // count only ACKs received before timeout, for both Command and Data in <handleAck()>
        unsigned long numRxAckPkt;

        // number of Collisions detected during frame reception and reported back from PHY to MAC
        unsigned long numCollisions;

        // num of BitErrors detected during frame reception and reported back from PHY to MAC
        unsigned long numBitErrors;

        // outgoing PAN descriptor transmitted used by coordinators (TBD)
        PAN_ELE txPanDescriptor;

        // incoming PAN descriptor transmitted used by devices (TBD)
        PAN_ELE rxPanDescriptor;
};

#endif /* MAC_H_ */
