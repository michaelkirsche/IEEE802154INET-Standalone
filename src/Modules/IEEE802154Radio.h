//
// Copyright (C) 2006 Andras Varga, Levente Meszaros
// Based on the Mobility Framework's SnrEval by Marc Loebbers
// Copyright (C) 2013 Matti Schnurbusch (original adaption for 802.15.4 model)
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

#ifndef IEEE802154Radio_H
#define IEEE802154Radio_H

#include "ChannelAccess.h"
#include "RadioState.h"
#include "AirFrame_m.h"
#include "IRadioModel.h"
#include "IReceptionModel.h"
#include "SnrList.h"
#include "ObstacleControl.h"
#include "INoiseGenerator.h"
#include "Modulation.h"
#include "IEEE802154Enum.h"
#include "PhyPIB.h"
#include "PPDU_m.h"

#define radioEV (ev.isDisabled()||!radioDebug) ? EV : EV << "[802154_RADIO]: " // switchable debug output

/**
 * Abstract base class for IEEE802154Radio modules.
 * This is an extension of INET's abstract Radio Class by Andras Varga and Levente Meszaros
 *
 * IEEE802154Radio modules deal with the transmission of frames over a wireless medium (the IEEE802154Radio channel).
 * See the IEEE802154Radio module's NED documentation for an overview of IEEE802154Radio modules.
 *
 * This class implements common functionality of the IEEE802154Radio, and abstracts
 * out specific parts into two interfaces, IReceptionModel and IIEEE802154RadioModel.
 * The reception model is responsible for modeling path loss, interference and antenna gain.
 * The IEEE802154Radio model is responsible for calculating frame duration, and modeling
 * modulation scheme and possible forward error correction.
 * Subclasses must redefine <tt>createReceptionModel()</tt> and <tt>createIEEE802154RadioModel()</tt>
 * methods to create and return appropriate reception model and IEEE802154Radio model objects.
 *
 * <b>History</b>
 *
 * The implementation is based on INET and subsequently Mobility Framework's
 * SnrEval and Decider modules.
 * Credits go to the original authors.
 *
 * @author Andras Varga, Levente Meszaros
 *
 */
class IEEE802154Radio : public ChannelAccess
{
    protected:
        typedef std::map<double, double> SensitivityList; // Sensitivity list
        SensitivityList sensitivityList;
        virtual void getSensitivityList(cXMLElement* xmlConfig);
    public:
        IEEE802154Radio();
        ~IEEE802154Radio();

    protected:
        /** @brief Debug output switch for the IEEE 802.15.4 Radio */
        bool radioDebug = false;

        /** added functionality for IEEE 802.15.4 support */
        void performED();
        void generateEDconf(double power, int EDval);
        void performCCA();
        void genCCAConf(bool success);
        void genPhyConf(phyState state);
        void initChannels();

        virtual void initialize(int stage);
        virtual int numInitStages() const { return 3; }

        virtual void finish();

        virtual void handleMessage(cMessage *msg);

        virtual void handleUpperMsg(AirFrame*);

        virtual void handleSelfMsg(cMessage*);

        virtual void handleCommand(int msgkind, cMsgPar* prop);

        /** @brief Buffer the frame and update noise levels and SNR information */
        virtual void handleLowerMsgStart(AirFrame *airframe);

        /** @brief Unbuffer the frame and update noise levels and SNR information */
        virtual void handleLowerMsgEnd(AirFrame *airframe);

        /** @brief Buffers message for 'transmission time' */
        virtual void bufferMsg(AirFrame *airframe);

        /** @brief Unbuffers a message after 'transmission time' */
        virtual AirFrame *unbufferMsg(cMessage *msg);

        /** Sends a message to the upper layer */
        virtual void sendUp(AirFrame *airframe);

        /** Sends a message to the channel */
        virtual void sendDown(AirFrame *airframe);

        /** Encapsulates a MAC frame into an Air Frame */
        virtual AirFrame *encapsulatePacket(cPacket *msg);

        /** Sets the IEEE802154Radio state, and also fires change notification */
        virtual void setRadioState(RadioState::State newState);

        /** Returns the current channel the IEEE802154Radio is tuned to */
        virtual int getChannelNumber() const
        {
            return rs.getChannelNumber();
        }

        /** Updates the SNR information of the relevant AirFrame */
        virtual void addNewSnr();

        /** Create a new AirFrame */
        virtual AirFrame *createAirFrame()
        {
            return new AirFrame();
        }

        /**
         * Change transmitter and receiver to a new channel.
         * This method throws an error if the IEEE802154Radio state is transmit.
         * Messages that are already sent to the new channel and would reach us in
         * the future - thus they are on the air - will be received correctly.
         */
        virtual void changeChannel(int channel);

        /**
         * Change the bit rate to the given value and set symbol rate to proper value.
         * This method throws an error if the IEEE802154Radio state is transmit.
         */
        virtual void setBitrate(int bitrate, bool firstTime);

        /** @brief updates the sensitivity value if the bit rate varies */
        virtual void updateSensitivity(double bitrate);

        /**
         *  check if the packet must be processes
         */
        virtual bool processAirFrame(AirFrame *airframe);

        /**
         * Routines to connect or disconnect the transmission and reception of packets
         */
        virtual void connectTransceiver()
        {
            transceiverConnect = true;
        }
        virtual void disconnectTransceiver()
        {
            transceiverConnect = false;
        }
        virtual void connectReceiver();
        virtual void disconnectReceiver();

        virtual void registerBattery();

        virtual void updateDisplayString();

        /** Methods to calculate distances and minimum power level to receive signals */
        double calcDistFreeSpace();
        double calcDistDoubleRay();

    protected:
        /**
         * Support of noise generators
         * Noise generators allow the IEEE802154Radio to change between RECV <--> IDLE without receiving a frame
         */
        static simsignal_t changeLevelNoise;
        virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);

        INoiseGenerator *noiseGenerator;
        cMessage *updateString;
        simtime_t updateStringInterval;
        ObstacleControl* obstacles;
        IRadioModel *radioModel;
        IReceptionModel *receptionModel;

        /** Power used to transmit messages */
        double transmitterPower;

        /** @name Gate IDs */
        //@{
        int upperLayerOut;
        int upperLayerIn;
        //@}

        /**
         * Struct to store a pointer to the message, rcvdPower AND a SnrList, needed in addNewSnr().
         */
        struct SnrStruct
        {
                AirFrame *ptr;    ///< pointer to the message this information belongs to
                double rcvdPower; ///< received power of the message
                SnrList sList;    ///< stores SNR over time
        };

        /**
         * State: SnrInfo stores the snrList and the the recvdPower for the
         * message currently being received, together with a pointer to the
         * message.
         */
        SnrStruct snrInfo;

        /**
         * Typedef used to store received messages together with receive power.
         */
        struct Compare
        {
                bool operator()(AirFrame* const &lhs, AirFrame* const &rhs) const
                {
                    ASSERT(lhs && rhs);
                    return lhs->getId() < rhs->getId();
                }
        };
        typedef std::map<AirFrame*, double, Compare> RecvBuff;

        /**
         * State: A buffer to store a pointer to a message and the related
         * receive power.
         */
        RecvBuff recvBuff;

        /** State: the current IEEE802154RadioState of the NIC; includes channel number */
        RadioState rs;

        /** State: if not -1, we have to switch to that channel once we finished transmitting */
        int newChannel;

        /** State: if not -1, we have to switch to that bit rate once we finished transmitting */
        double newBitrate;

        /** State: the current noise level of the channel.*/
        double noiseLevel;

        /**
         * Configuration: The carrier frequency used. It is read from the ChannelControl module.
         * FIXME use the channelNumber and according center frequency instead of carrierFrequency
         */
        double carrierFrequency;

        /**
         * Configuration: Thermal noise on the channel. Can be specified in omnetpp.ini. Default: -110dBm
         */
        double thermalNoise;

        /**
         * Configuration: Defines up to what Power level (in dBm) a message can be
         * understood. If the level of a received packet is lower, it is
         * only treated as noise. Can be specified in omnetpp.ini. Default: -85 dBm
         */
        double sensitivity;

        /**
         * minimum signal necessary to change the channel state to RECV
         */
        double receptionThreshold;

        /**
         * this variable is used to disconnect the possibility of sent packets to the ChannelControl
         */
        bool transceiverConnect;
        bool receiverConnect;

        /**
         * Symbol rate of the PHY
         * Different symbol rates for different frequencies and bit rates (refer to IEEE 802.15.4 specs)
         */
        double symbolRate;

        /** if true --> draw coverage circles */
        bool drawCoverage;
        bool doubleRayCoverage;

        // if true --> we are performing an energy detection on current channel
        bool activeED;
        cMessage* selfEDMsg;

        /** Boolean values for the 3 different CCAModes */
        bool ccaMode1;
        bool ccaMode2;
        unsigned short ccaMode;
        cMessage* selfCCAMsg;

        /** used for CCA and ED answer  */
        double rcvdPow;
        double distance;
        static const double channelFreq[27];

        /** ID of this Module, required for RadioID */
        int iD;

        /** @name Statistics */
        static simsignal_t bitrateSignal;
        static simsignal_t IEEE802154RadioStateSignal; //enum
        static simsignal_t channelNumberSignal;
        static simsignal_t lossRateSignal;

        unsigned long numReceivedButGivenUp;
        unsigned long numReceivedCorrectly;
        double lossRate;
};

#endif /* IEEE802154Radio_H */
