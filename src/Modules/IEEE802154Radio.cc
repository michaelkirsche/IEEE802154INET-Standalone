//
// Copyright (C) 2006 Andras Varga, Levente Meszaros
// Copyright (C) 2009 Juan-Carlos Maureira
//     - Multi IEEE802154Radio Support
//     - Drawing Interference and Sensitivity circles
// Based on the Mobility Framework's SnrEval by Marc Loebbers
// Copyright (C) 2013 Matti Schnurbusch (original adaption for 802.15.4 model)
// Copyright (C) 2015 Michael Kirsche   (fixes, ported for INET 2.x)
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

#include "IEEE802154Radio.h"
#include "FWMath.h"
#include "BasicBattery.h"

#define MK_TRANSMISSION_OVER  1
#define MK_RECEPTION_COMPLETE 2

simsignal_t IEEE802154Radio::bitrateSignal = registerSignal("bitrate");
simsignal_t IEEE802154Radio::IEEE802154RadioStateSignal = registerSignal("radioState");
simsignal_t IEEE802154Radio::channelNumberSignal = registerSignal("channelNumber");
simsignal_t IEEE802154Radio::lossRateSignal = registerSignal("lossRate");
simsignal_t IEEE802154Radio::changeLevelNoise = registerSignal("changeLevelNoise");

#define MIN_DISTANCE 0.001 // minimum distance 1 millimeter
#define BASE_NOISE_LEVEL (noiseGenerator?noiseLevel+noiseGenerator->noiseLevel():noiseLevel)

// Center frequencies for our 27 IEEE 802.15.4 radio channels
// FIXME check that the exact center frequency is used instead of ChannelControl carrierFrequency value
const double IEEE802154Radio::channelFreq[27] = { 868.3,  // 1 channel in the 868 MHz band
        906, 908, 910, 912, 914, 916, 918, 920, 922, 924,  // 10 channels in the 915 MHz band
        2405, 2410, 2415, 2420, 2425, 2430, 2435, 2440, 2445, 2450, 2455, 2460, 2465, 2470, 2475, 2480 };  // 16 channels in the 2450 MHz band

Define_Module(IEEE802154Radio);

IEEE802154Radio::IEEE802154Radio() :
        rs(this->getId())
{
    obstacles = NULL;
    radioModel = NULL;
    receptionModel = NULL;
    transceiverConnect = true;
    receiverConnect = true;
    updateString = NULL;
    noiseGenerator = NULL;
}

IEEE802154Radio::~IEEE802154Radio()
{
    delete radioModel;
    delete receptionModel;
    if (noiseGenerator)
    {
        delete noiseGenerator;
    }

    if (updateString)
    {
        cancelAndDelete(updateString);
    }

    if (selfCCAMsg)
    {
        cancelAndDelete(selfCCAMsg);
    }

    if (selfEDMsg)
    {
        cancelAndDelete(selfEDMsg);
    }

    // delete messages being received
    for (RecvBuff::iterator it = recvBuff.begin(); it != recvBuff.end(); ++it)
    {
        delete it->first;
    }
}

void IEEE802154Radio::initialize(int stage)
{
    ChannelAccess::initialize(stage);

    if (stage == 0)
    {
        // initialize the debug ouput bool from NED parameter value
        radioDebug = (hasPar("radioDebug") ? (par("radioDebug").boolValue()) : (false));

        gate("radioIn")->setDeliverOnReceptionStart(true);

        upperLayerIn = findGate("upperLayerIn");
        upperLayerOut = findGate("upperLayerOut");

        getSensitivityList(par("SensitivityTable").xmlValue());

        // read parameters
        transmitterPower = par("transmitterPower");
        if (transmitterPower > (double) (getChannelControlPar("pMax")))
        {
            error("transmitterPower cannot be bigger than pMax in ChannelControl!");
        }

        newChannel = par("channelNumber");
        rs.setChannelNumber(newChannel);
        nb->subscribe(this, NF_RADIOSTATE_CHANGED);

        iD = this->getId();
        rs.setRadioId(iD);

        thermalNoise = FWMath::dBm2mW(par("thermalNoise"));
        sensitivity = FWMath::dBm2mW(par("sensitivity"));

        ccaMode = par("ccaMode");
        ccaMode1 = false;
        ccaMode2 = false;
        activeED = false;

        carrierFrequency = channelFreq[newChannel];

        // initialize noiseLevel
        noiseLevel = thermalNoise;
        std::string noiseModel = par("NoiseGenerator").stdstringValue();
        if (noiseModel != "")
        {
            noiseGenerator = (INoiseGenerator *) createOne(noiseModel.c_str());
            noiseGenerator->initializeFrom(this);
            // register to get a notification when position changes
            subscribe(changeLevelNoise, this);  // the INoiseGenerator must send a signal to this module
        }

        radioEV << "Initialized channel with noise: " << noiseLevel << " sensitivity: " << sensitivity << endl;

        // initialize the pointer of the snrInfo with NULL to indicate
        // that currently no message is received
        snrInfo.ptr = NULL;

        // no channel switch pending
        newChannel = -1;

        // statistics
        numReceivedButGivenUp = 0;
        numReceivedCorrectly = 0;
        lossRate = 0;

        // Initialize IEEE802154Radio state. If thermal noise is already to high,
        // IEEE802154Radio state has to be initialized as RECV
        rs.setState(RadioState::IDLE);
        if (BASE_NOISE_LEVEL >= sensitivity)
        {
            rs.setState(RadioState::RECV);
        }

        obstacles = ObstacleControlAccess().getIfExists();
        if (obstacles)
        {
            radioEV << "Found ObstacleControl \n";
        }

        // this is the parameter of the channel controller (global)
        std::string propModel = getChannelControlPar("propagationModel").stdstringValue();
        if (propModel == "")
        {
            propModel = "FreeSpaceModel";
        }
        doubleRayCoverage = false;
        if (propModel == "TwoRayGroundModel")
        {
            doubleRayCoverage = true;
        }

        receptionModel = (IReceptionModel *) createOne(propModel.c_str());
        receptionModel->initializeFrom(this);

        // adjust the sensitivity in function of maxDistance and reception model
        if (par("maxDistance").doubleValue() > 0)
        {
            if (sensitivityList.size() == 1 && sensitivityList.begin()->second == sensitivity)
            {
                sensitivity = receptionModel->calculateReceivedPower(transmitterPower, carrierFrequency, par("maxDistance").doubleValue());
                sensitivityList[0] = sensitivity;
            }
        }

        receptionThreshold = sensitivity;
        if (par("setReceptionThreshold").boolValue())
        {
            receptionThreshold = FWMath::dBm2mW(par("receptionThreshold").doubleValue());
            if (par("maxDistantReceptionThreshold").doubleValue() > 0)
            {
                receptionThreshold = receptionModel->calculateReceivedPower(transmitterPower, carrierFrequency, par("maxDistantReceptionThreshold").doubleValue());
            }
        }

        // IEEE802154Radio model to handle frame length and reception success calculation (modulation, error correction etc.)
        std::string rModel = par("radioModel").stdstringValue();
        if (rModel == "")
        {
            rModel = "GenericRadioModel";
        }

        radioModel = (IRadioModel *) createOne(rModel.c_str());
        radioModel->initializeFrom(this);

        newBitrate = par("bitrate");
        setBitrate(newBitrate, true);

        if (this->hasPar("drawCoverage"))
        {
            drawCoverage = par("drawCoverage");
        }
        else
        {
            drawCoverage = false;
        }

        if (this->hasPar("refreshCoverageInterval"))
        {
            updateStringInterval = par("refreshCoverageInterval");
        }
        else
        {
            updateStringInterval = 0;
        }

        selfCCAMsg = new cMessage("CCA-Timer");
        selfCCAMsg->setKind(CCA);

        selfEDMsg = new cMessage("ED-Timer");
        selfEDMsg->setKind(ED);

    }
    else if (stage == 1)
    {
        registerBattery();

        WATCH(noiseLevel);
        WATCH(rs);

        WATCH(numReceivedButGivenUp);
        WATCH(numReceivedCorrectly);
        WATCH(lossRate);

        // tell initial values to MAC; must be done in stage 1, because they subscribe in stage 0
        nb->fireChangeNotification(NF_RADIOSTATE_CHANGED, &rs);
        nb->fireChangeNotification(NF_RADIO_CHANNEL_CHANGED, &rs);
    }
    else if (stage == 2)
    {
        // tell initial channel number to ChannelControl; should be done in stage==2 or later,
        // because base class initializes myIEEE802154RadioRef in that stage
        cc->setRadioChannel(myRadioRef, rs.getChannelNumber());

        // statistics
        emit(bitrateSignal, rs.getBitrate());
        emit(IEEE802154RadioStateSignal, rs.getState());
        emit(channelNumberSignal, rs.getChannelNumber());

        // draw the interference distance
        this->updateDisplayString();
    }
}

void IEEE802154Radio::finish()
{

}

bool IEEE802154Radio::processAirFrame(AirFrame *airframe)
{
    return airframe->getChannelNumber() == getChannelNumber();
}

/**
 * The basic handle message function.
 *
 * Depending on the gate a message arrives handleMessage just calls
 * different handle*Msg functions to further process the message.
 *
 * Messages from the channel are also buffered here in order to
 * simulate a transmission delay
 *
 * You should not make any changes in this function but implement all
 * your functionality into the handle*Msg functions called from here.
 *
 * @sa handleUpperMsg, handleLowerMsgStart, handleLowerMsgEnd,
 * handleSelfMsg
 */
void IEEE802154Radio::handleMessage(cMessage *msg)
{
    if (rs.getState() == RadioState::SLEEP || rs.getState() == RadioState::OFF)
    {
        if (!(msg->getArrivalGateId() == upperLayerIn) && !(msg->isSelfMessage()))
        {
            genPhyConf(phy_TRX_OFF);
            radioEV << "Radio is turned off, dropping/ignoring frame! \n";
            delete (msg);
            return;
        }
    }

    if (ev.isGUI())
    {
        char tBuf[45];
        sprintf(tBuf, "#rcvdOK: %lu pks\n#givenUp: %lu pks", numReceivedCorrectly, numReceivedButGivenUp);
        getDisplayString().setTagArg("t", 0, tBuf);
    }

    // handle commands
    if (updateString && updateString == msg)
    {
        this->updateDisplayString();
        return;
    }

    if ((msg->getArrivalGateId() == upperLayerIn) && !(msg->isPacket()))
    {
        if (msg->getKind() == 0)
        {
            error("Message '%s' with length==0 is supposed to be a command, but msg kind is also zero", msg->getName());
        }

        cMsgPar* prop = (cMsgPar *) msg->getParList().get(0);

        handleCommand(msg->getKind(), prop);
        delete (msg);
        return;
    }

    if (msg->getArrivalGateId() == upperLayerIn)
    {
        if (msg->isPacket() == false)
        {
            error("Message '%s' is supposed to be a cPacket, but is not!", msg->getName());
        }
        AirFrame *airframe = encapsulatePacket(PK(msg));
        handleUpperMsg(airframe);
    }
    else if (msg->isSelfMessage())
    {
        handleSelfMsg(msg);
    }
    else if (processAirFrame(check_and_cast<AirFrame*>(msg)))
    {
        if (receiverConnect)
        {
            // must be an AirFrame
            AirFrame *airframe = (AirFrame *) msg;
            if (activeED)
            {
                radioEV << "Received message while performing ED !\n";
                distance = getRadioPosition().distance(airframe->getSenderPos());
                rcvdPow = receptionModel->calculateReceivedPower(airframe->getPSend(), airframe->getCarrierFrequency(), distance);
                radioEV << "Calculated Received Power on ED = " << rcvdPow << endl;

                generateEDconf(rcvdPow, ED_SUCCESS);
                activeED = false;
                delete (msg);
                delete (airframe);    // undisposed AirFrame object fix
                return;
            }
            else if (ccaMode1 || ccaMode2)
            {
                distance = getRadioPosition().distance(airframe->getSenderPos());
                rcvdPow = receptionModel->calculateReceivedPower(airframe->getPSend(), airframe->getCarrierFrequency(), distance);
                if (ccaMode1 && ccaMode2)
                {
                    if (((rcvdPow > noiseLevel) && (airframe->getCarrierFrequency() == carrierFrequency && ((airframe->getBitrate() == newBitrate) && (rcvdPow > noiseLevel)))))
                    {
                        genCCAConf(false);
                        radioEV << "CCA channel not clear! \n";
                    }
                    else
                    {
                        genCCAConf(true);
                    }
                }
                else if (ccaMode1)
                {
                    if (rcvdPow > noiseLevel)
                    {
                        radioEV << "CCA channel not clear! \n";
                        genCCAConf(false);
                    }
                    else
                    {
                        genCCAConf(true);
                    }
                }
                else if (ccaMode2)
                {
                    // mode 2 = report a busy medium only upon the detection of a signal compliant with this standard,
                    // with the same modulation and same spreading characteristics of the PHY that is currently in use by the device

                    // Frequency and bit rate shall be enough
                    if (airframe->getCarrierFrequency() == carrierFrequency && airframe->getBitrate() == newBitrate && rcvdPow > noiseLevel)
                    {
                        genCCAConf(false);
                        radioEV << "CCA channel not clear! \n";
                    }
                    else
                    {
                        genCCAConf(true);
                    }
                }
                else
                {
                    error("handleMessage(): ccaMode checking produced an illegal state!");
                }

                delete (msg);       // undisposed object fix
                return;
            }
            // conditions changed to "support" INET's IDLE radio states
            // or else IDLE would lead to a deadlock situation, when radio is switched to IDLE mode
            // and the higher layers do not have any timers running to set it back to receive mode
            // both IDLE (channel is empty -> radio is in receive mode) and
            // and RECV (channel is busy -> radio is in receive mode)
            // are actually receiving modes, decisions about corrupt packets are made later
            else if ((rs.getState() == RadioState::RECV) || (rs.getState() == RadioState::IDLE))
            {
                handleLowerMsgStart(airframe);
                bufferMsg(airframe);
                return;
            }
            else if (rs.getState() == RadioState::TRANSMIT)
            {
                radioEV << "Frame received during own transmit operation -> dropping airframe! \n";
                delete (msg);
                return;
            }
        }
        else
        {
            radioEV << "Radio not connected / disabled -- dropping airframe! \n";
            delete (msg);
            return;
        }
    }
    else
    {
        radioEV << "Listening to different channel when receiving message -- dropping it! \n";
        delete (msg);
        return;
    }
}

/**
 * The packet is put in a buffer for the time the transmission would
 * last in reality. A timer indicates when the transmission is
 * complete. So, look at unbufferMsg to see what happens when the
 * transmission is complete..
 */
void IEEE802154Radio::bufferMsg(AirFrame *airframe)
{
    // set timer to indicate transmission is complete
    cMessage *endRxTimer = new cMessage("endRx", MK_RECEPTION_COMPLETE);
    endRxTimer->setContextPointer(airframe);
    airframe->setContextPointer(endRxTimer);

    // NOTE: use arrivalTime instead of simTime, because we might be calling this
    // function during a channel change, when we're picking up ongoing transmissions
    // on the channel -- and then the message's arrival time is in the past!
    scheduleAt(airframe->getArrivalTime() + airframe->getDuration(), endRxTimer);
}

AirFrame *IEEE802154Radio::encapsulatePacket(cPacket *frame)
{
    AirFrame *airframe = createAirFrame();
    airframe->setName(frame->getName());
    airframe->setPSend(transmitterPower);
    airframe->setChannelNumber(getChannelNumber());
    airframe->encapsulate(frame);
    airframe->setBitLength(frame->getByteLength() * 8);
    airframe->setBitrate(rs.getBitrate());
    airframe->setDuration(radioModel->calculateDuration(airframe));
    airframe->setSenderPos(getRadioPosition());
    airframe->setCarrierFrequency(carrierFrequency);

    radioEV << "Frame (" << frame->getClassName() << ")" << frame->getName() << " will be transmitted at "
            << (airframe->getBitrate() / 1e3) << "Kbps in " << airframe->getDuration() << "sec \n";
    return airframe;
}

void IEEE802154Radio::sendUp(AirFrame *airframe)
{
    cPacket *frame = airframe->decapsulate();    // this is the Data request
    radioEV << "Sending up PD-Data.indication with SNR ratio: " << airframe->getSnr() << " and LossRate: "
            << airframe->getLossRate() <<" and ReceivedPower: " << airframe->getPowRec() << endl;

    pdDataInd* dataInd = new pdDataInd("PD-DATA.indication");
    dataInd->setPpduLinkQuality(airframe->getSnr());    // setting LQI for the received packet, for later evaluation in MAC and App layer
    dataInd->setPsduLength(frame->getByteLength());

    if (frame->hasEncapsulatedPacket() == true)
    {
        dataInd->encapsulate(frame->decapsulate());
        // FIXME decapsulation is not necessary here, pdDataIndication should directly be sent to MAC, which unwrapps it
        // and uses (e.g.) the LinkQualityIndicator
    }
    else
    {
        dataInd->encapsulate(frame);
    }

    send(dataInd, upperLayerOut);
    delete (frame); // fix for undisposed object: (ppdu) net.IEEE802154Nodes[*].NIC.radioInterface.PD-DATA
}

void IEEE802154Radio::sendDown(AirFrame *airframe)
{
    if (transceiverConnect)
    {
        sendToChannel(airframe);
    }
    else
    {
        radioEV << "transceiver is not connected - airframe " << airframe->getName() << " is deleted!\n";
        delete (airframe);
    }
}

/**
 * Get the context pointer to the now completely received AirFrame and
 * delete the self message
 */
AirFrame *IEEE802154Radio::unbufferMsg(cMessage *msg)
{
    AirFrame *airframe = (AirFrame *) msg->getContextPointer();
    // delete the self message
    delete (msg);

    return airframe;
}

/**
 * If a message is already being transmitted, an error is raised.
 *
 * Otherwise the RadioState is set to TRANSMIT and a timer is started.
 * When this timer expires the RadioState will be set back to RECV
 * (or IDLE respectively) again.
 *
 * If the host is receiving a packet this packet is from now on only
 * considered as noise.
 */
void IEEE802154Radio::handleUpperMsg(AirFrame *airframe)
{
    if (rs.getState() == RadioState::TRANSMIT)
    {
        genPhyConf(phy_BUSY_TX);
        return;
    }

    // if a packet was being received, it is corrupted now and should be treated as noise
    if (snrInfo.ptr != NULL)
    {
        radioEV << "Sending a message while receiving another. The received message is now corrupted! \n";

        // remove the SNR information stored for the message currently being received.
        // This message is treated as noise now and the receive power has to be added to the noiseLevel

        // delete the pointer to indicate that no message is being received
        snrInfo.ptr = NULL;
        // clear the SNR list
        snrInfo.sList.clear();
        // add the receive power to the noise level
        noiseLevel += snrInfo.rcvdPower;

        //genPhyConf(phy_RX_ON);    // XXX radio is currently receiving
        genPhyConf(phy_BUSY_RX);    // generate busy receiving state instead
    }

    // now we are done with all the exception handling and can take care about the "real" stuff

    // change radio status
    radioEV << "Sending packet, changing RadioState to TRANSMIT \n";
    setRadioState(RadioState::TRANSMIT);

    cMessage *timer = new cMessage(NULL, MK_TRANSMISSION_OVER);
    scheduleAt(simTime() + airframe->getDuration(), timer);
    sendDown(airframe);
}

void IEEE802154Radio::handleCommand(int msgkind, cMsgPar* prop)
{
    switch (msgkind)
    {
        case phy_RX_ON: {
            if (rs.getState() == (RadioState::RECV))
            {
                radioEV << "------Receiver is already ON (RECV)--------------- \n";
            }
            else
            {
                radioEV << "------Receiver turned ON (RECV)--------------- \n";
                setRadioState(RadioState::RECV);
            }
            return;
        }

        case phy_TX_ON: {
            if (rs.getState() == (RadioState::IDLE))
            {
                radioEV << "------Transmitter is already ON (IDLE)------------ \n";
            }
            else
            {
                radioEV << "------Transmitter turned ON (IDLE)------------ \n";
                setRadioState(RadioState::IDLE);
            }
            return;
        }

        case phy_TRX_OFF: {
            if (rs.getState() == (RadioState::SLEEP))
            {
                radioEV << "------Transmitter is already OFF (SLEEP)------------ \n";
            }
            else
            {
                radioEV << "------Transmitter turned OFF (SLEEP)------------ \n";
                setRadioState(RadioState::SLEEP);
            }
            return;
        }

        case phy_FORCE_TRX_OFF: {
            radioEV << "------Transmitter forcefully turned OFF------------ \n";
            setRadioState(RadioState::SLEEP);
            return;
        }

        case phy_CHANGE_TRANSMITTER_POWER: {
            if (prop == NULL)
            {
                error("[RADIO]: got a Change Transmitter Power command without Par");
            }

            double newTransmitterPower = prop->doubleValue();
            if (newTransmitterPower != -1)
            {
                if (newTransmitterPower > getChannelControlPar("pMax").doubleValue())
                {
                    newTransmitterPower = getChannelControlPar("pMax").doubleValue();
                }
                else
                {
                    transmitterPower = newTransmitterPower;
                }
            }
            return;
        }

        case phy_CHANGE_CHANNEL: {
            if (prop == NULL)
            {
                error("[RADIO]: got a Change Channel command without Par");
            }

            int newChann = prop->longValue();
            if ((newChann > -1) && (newChann < 27))
            {
                if (rs.getChannelNumber() == newChann)
                {
                    radioEV << "Already operating on that channel, nothing to do \n";
                }
                else if (rs.getState() == RadioState::TRANSMIT)
                {
                    radioEV << "We're transmitting right now, remembering to change after it's completed \n";
                    this->newChannel = newChann;
                }
                else
                {
                    changeChannel(newChann);  // change channel right now
                }
            }
            return;
        }

        case phy_CHANGE_BITRATE: {
            if (newBitrate != -1)
            {
                radioEV << "Command received: change bit rate to " << (newBitrate / 1e3) << "Kbps \n";

                // do it
                if (rs.getBitrate() == newBitrate)
                {
                    radioEV << "Already operating with that bit rate, nothing to do \n";
                }
                else if (rs.getState() == RadioState::TRANSMIT)
                {
                    radioEV << "We're transmitting right now, remembering to change after it's completed \n";
                    this->newBitrate = newBitrate;
                }
                else
                {
                    setBitrate(newBitrate, false);  // change bitrate right now
                }
            }
            return;
        }

        case CCA: {
            radioEV << "Initiating CCA \n";
            if (!snrInfo.sList.empty())
            {
                radioEV << "[CCA]: currently receicing - channel not clear right now! \n";
                genCCAConf(false);
            }
            else
            {
                performCCA();
            }
            return;
        }

        case ED: {
            radioEV << "Initiating ED \n";
            performED();
            return;
        }

        default: {
            error("Unknown command (msgkind=%d)", msgkind);
            return;
        }
    }
}

void IEEE802154Radio::handleSelfMsg(cMessage *msg)
{
    radioEV << "handleSelfMsg with Kind " << msg->getKind() << endl;

    if (msg->getKind() == ED)
    {
        radioEV << "[ED]: detection over \n";
        generateEDconf(0, ED_SUCCESS);
    }
    else if (msg->getKind() == CCA)
    {
        radioEV << "[CCA]: Channel clear \n";
        genCCAConf(true);
    }
    else if (msg->getKind() == MK_RECEPTION_COMPLETE)
    {
        radioEV << "Frame is completely received now \n";

        // unbuffer the message
        AirFrame *airframe = unbufferMsg(msg);

        handleLowerMsgEnd(airframe);
        delete(airframe);   // fix for undisposed object: (AirFrame) net.IEEE802154Nodes[*].NIC.radioInterface.PD-DATA
    }
    else if (msg->getKind() == MK_TRANSMISSION_OVER)
    {
        // Transmission has completed. The RadioState has to be changed to IDLE or RECV,
        // based on the noise level on the channel. If the noise level is bigger than the
        // sensitivity switch to receive mode, otherwise to idle mode.
        RadioState::State newState;
        if (BASE_NOISE_LEVEL < sensitivity)
        {
            // set the RadioState to IDLE
            radioEV << "Transmission over, switch to idle mode (RadioState::IDLE) \n";
            // setRadioState(RadioState::IDLE);
            newState = RadioState::IDLE;
        }
        else
        {
            // set the RadioState to RECV
            radioEV << "Transmission over but noise level too high, switch to RECV mode (RadioState::RECV) \n";
            // setRadioState(RadioState::RECV);
            newState = RadioState::RECV;
        }

        // delete the self message
        delete msg;

        // switch channel if it needs be
        if (newChannel != -1)
        {
            if (newChannel == rs.getChannelNumber())
            {
                setRadioState(newState);  // nothing to do change the state
            }
            else
            {
                // if change the channel the method changeChannel must set the correct radio state
                rs.setState(newState);
                changeChannel(newChannel);
            }
            newChannel = -1;
        }
        else
        {
            // newChannel==-1 the channel doesn't change
            setRadioState(newState);  // now the radio changes the state and sends the signal
        }

        genPhyConf(phy_SUCCESS);
    }
    else
    {
        error("Internal error: unknown self-message `%s'", msg->getName());
    }
    radioEV << "handleSelfMsg END \n";
}

/**
 * This function is called right after a packet arrived, i.e. right
 * before it is buffered for 'transmission time'.
 *
 * First the receive power of the packet has to be calculated and is
 * stored in the recvBuff. Afterwards it has to be decided whether the
 * packet is just noise or a "real" packet that needs to be received.
 *
 * The message is not treated as noise if all of the following
 * conditions apply:
 *
 * -# the power of the received signal is higher than the sensitivity.
 * -# the host is currently not sending a message
 * -# no other packet is already being received
 *
 * If all conditions apply a new SnrList is created and the RadioState
 * is changed to RECV.
 *
 * If the packet is just noise the receive power is added to the noise
 * Level of the channel. Additionally the SNR information of the
 * currently being received message (if any) has to be updated as
 * well as the RadioState.
 */
void IEEE802154Radio::handleLowerMsgStart(AirFrame* airframe)
{
    // calculate distance
    const Coord& framePos = airframe->getSenderPos();
    double distance = getRadioPosition().distance(framePos);

    // Calculate the receive power of the message
    double frequency = carrierFrequency;
    if (airframe->getCarrierFrequency() > 0.0)
    {
        frequency = airframe->getCarrierFrequency();
    }

    if (distance < MIN_DISTANCE)
    {
        distance = MIN_DISTANCE;
    }

    rcvdPow = receptionModel->calculateReceivedPower(airframe->getPSend(), frequency, distance);
    if (obstacles && distance > MIN_DISTANCE)
    {
        rcvdPow = obstacles->calculateReceivedPower(rcvdPow, carrierFrequency, framePos, 0, getRadioPosition(), 0);
    }
    airframe->setPowRec(rcvdPow);
    // store the receive power in the recvBuff
    recvBuff[airframe] = rcvdPow;
    updateSensitivity(airframe->getBitrate());

    // if receive power is bigger than sensitivity and if not sending and
    // currently not receiving another message and the message has arrived in time
    // NOTE: a message may have arrival time in the past here when we are
    // processing ongoing transmissions during a channel change
    if (airframe->getArrivalTime() == simTime() && rcvdPow >= sensitivity && rs.getState() != RadioState::TRANSMIT && snrInfo.ptr == NULL)
    {
        radioEV << "Receiving frame " << airframe->getName() << endl;

        // Put frame and related SnrList in receive buffer
        SnrList snrList;
        snrInfo.ptr = airframe;
        snrInfo.rcvdPower = rcvdPow;
        snrInfo.sList = snrList;

        // add initial SNR value
        addNewSnr();

        if (rs.getState() != RadioState::RECV)
        {
            // Set new RadioState
            radioEV << "Setting radio state to RECV \n";
            setRadioState(RadioState::RECV);
        }
    }
    // receive power is too low or another message is being sent or received
    else
    {
        radioEV << "Frame " << airframe->getName() << " is just noise! \n";
        //add receive power to the noise level
        noiseLevel += rcvdPow;

        // if a message is being received add a new SNR value
        if (snrInfo.ptr != NULL)
        {
            // update SNR info for currently being received message
            radioEV << "Adding new SNR value to SNR list of message being received. \n";
            addNewSnr();
        }

        // update the RadioState if the noiseLevel exceeded the threshold
        // and the radio is currently not in receive or in send mode
        if ((BASE_NOISE_LEVEL >= receptionThreshold) && (rs.getState() == RadioState::IDLE))
        {
            // Set new RadioState
            radioEV << "Setting radio state to RECV \n";
            setRadioState(RadioState::RECV);
        }
    }
}

/**
 * This function is called right after the transmission is over,
 * i.e. right after unbuffering. The noise level of the channel and
 * the SNR information of the buffered messages have to be updated.
 *
 * Additionally the RadioState has to be updated.
 *
 * If the corresponding AirFrame was not only noise the corresponding
 * SnrList and the AirFrame are sent to the decider.
 */
void IEEE802154Radio::handleLowerMsgEnd(AirFrame * airframe)
{
    // check if message has to be send to the decider
    if (snrInfo.ptr == airframe)
    {
        radioEV << "Reception of frame over, preparing to send packet to upper layer. \n";
        // get Packet and list out of the receive buffer:
        SnrList list;
        list = snrInfo.sList;

        // delete the pointer to indicate that no message is currently being received and clear the list
        double snirMin = snrInfo.sList.begin()->snr;
        for (SnrList::const_iterator iter = snrInfo.sList.begin(); iter != snrInfo.sList.end(); iter++)
        {
            if (iter->snr < snirMin)
            {
                snirMin = iter->snr;
            }
        }
        snrInfo.ptr = NULL;
        snrInfo.sList.clear();

        //airframe->setSnr(10 * log10(recvBuff[airframe] / (BASE_NOISE_LEVEL)));        //ahmed
        airframe->setSnr(10 * log10(snirMin));  // TODO check which SNR calculation should be used
        //airframe->setLossRate(lossRate);      // currently only used in INET 2.x, not sent up in 802.15.4 model
        // delete the frame from the recvBuff
        recvBuff.erase(airframe);

        PhyIndication frameState = radioModel->isReceivedCorrectly(airframe, list);
        if (frameState != FRAMEOK)
        {
            airframe->getEncapsulatedPacket()->getEncapsulatedPacket()->setKind(frameState);    // fix for setting of PhyIndications
            airframe->setName(frameState == COLLISION ? "COLLISION" : "BITERROR");  // msg name not evaluated for now

            if (ev.isGUI())    // only supported up to OMNeT 4.6, not compatible with OMNeT 5.x -> use hasGUI() there
            {
                if (frameState == COLLISION)
                {
                    bubble("Packets collided - frameState COLLISION");
                }
                else if (frameState == BITERROR)
                {
                    bubble("Packet got errors - frameState BITERROR");
                }
            }

            numReceivedButGivenUp++;
        }
        else
        {
            numReceivedCorrectly++;
        }

        sendUp(airframe);
    }
    // all other messages are noise
    else
    {
        radioEV << "Reception of noise message over, removing rcvdPower from noiseLevel\n";
        // get the rcvdPower and subtract it from the noiseLevel
        noiseLevel -= recvBuff[airframe];

        // delete message from the recvBuff
        recvBuff.erase(airframe);

        // update SNR info for message currently being received if any
        if (snrInfo.ptr != NULL)
        {
            addNewSnr();
        }

        // noise messages are also count as "received but given up"
        numReceivedButGivenUp++;
    }

    if ((numReceivedCorrectly + numReceivedButGivenUp) % 10 == 0)
    {
        lossRate = (double) numReceivedButGivenUp / ((double) numReceivedCorrectly + (double) numReceivedButGivenUp);
        emit(lossRateSignal, lossRate);
    }

    // check the RadioState and update if necessary
    // change to idle if noiseLevel smaller than threshold and state was not idle before
    // do not change state if currently sending or receiving a message!!!
    if ((BASE_NOISE_LEVEL < receptionThreshold) && (rs.getState() == RadioState::RECV) && (snrInfo.ptr == NULL))
    {
        // set the new RadioState:
        radioEV << "Setting radio state to IDLE. \n";
        setRadioState(RadioState::IDLE);
    }
}

void IEEE802154Radio::addNewSnr()
{
    SnrListEntry listEntry;  // create a new entry
    listEntry.time = simTime();
    listEntry.snr = snrInfo.rcvdPower / (BASE_NOISE_LEVEL);
    snrInfo.sList.push_back(listEntry);
}

void IEEE802154Radio::changeChannel(int channel)
{
    // Basic checks
    if (channel == rs.getChannelNumber())
    {
        return;
    }
    if (rs.getState() == RadioState::TRANSMIT)
    {
        error("Changing channel while transmitting is not allowed");
    }

    // Clear the recvBuff
    for (RecvBuff::iterator it = recvBuff.begin(); it != recvBuff.end(); ++it)
    {
        AirFrame *airframe = it->first;
        cMessage *endRxTimer = (cMessage *) airframe->getContextPointer();
        delete airframe;
        delete cancelEvent(endRxTimer);
    }
    recvBuff.clear();

    // Clear SNR info
    snrInfo.ptr = NULL;
    snrInfo.sList.clear();

    // Reset the noiseLevel
    noiseLevel = thermalNoise;

    if (rs.getState() != RadioState::IDLE)
    {
        rs.setState(RadioState::IDLE);  // Force IEEE802154Radio to Idle
    }

    // Do channel switch
    radioEV << "Changing to channel #" << channel << endl;

    emit(channelNumberSignal, channel);
    rs.setChannelNumber(channel);

    if (channel == 0)
    {
        setBitrate(20000, false);
    }
    else if (channel > 0 && channel <= 10)
    {
        setBitrate(40000, false);
    }
    else if (channel >= 11 && channel <= 26)
    {
        setBitrate(250000, false);
    }
    cc->setRadioChannel(myRadioRef, rs.getChannelNumber());

    cModule *myHost = findHost();

    cGate* IEEE802154RadioGate = this->gate("radioIn")->getPathStartGate();

    radioEV << "RadioGate: " << IEEE802154RadioGate->getFullPath() << " " << IEEE802154RadioGate->getFullName() << endl;

    // pick up ongoing transmissions on the new channel
    radioEV << "Picking up ongoing transmissions on new channel: \n";
    IChannelControl::TransmissionList tlAux = cc->getOngoingTransmissions(channel);
    for (IChannelControl::TransmissionList::const_iterator it = tlAux.begin(); it != tlAux.end(); ++it)
    {
        AirFrame *airframe = check_and_cast<AirFrame *>(*it);
        // time for the message to reach us
        double distance = getRadioPosition().distance(airframe->getSenderPos());
        simtime_t propagationDelay = distance / 3.0E+8;

        // if this transmission is on our new channel and it would reach us in the future, then schedule it
        if (channel == airframe->getChannelNumber())
        {
            radioEV << " - (" << airframe->getClassName() << ")" << airframe->getName() << ": ";
        }

        // if there is a message on the air which will reach us in the future
        if (airframe->getTimestamp() + propagationDelay >= simTime())
        {
            radioEV << "will arrive in the future, scheduling it \n";

            // JcM Fix: we need to this radio only. no need to send the packet to each radioIn
            // since other radios might be not in the same channel
            sendDirect(airframe->dup(), airframe->getTimestamp() + propagationDelay - simTime(), airframe->getDuration(), myHost, IEEE802154RadioGate->getId());
        }
        // if we hear some part of the message
        else if (airframe->getTimestamp() + airframe->getDuration() + propagationDelay > simTime())
        {
            radioEV << "missed beginning of frame, processing it as noise \n";

            AirFrame *frameDup = airframe->dup();
            frameDup->setArrivalTime(airframe->getTimestamp() + propagationDelay);
            handleLowerMsgStart(frameDup);
            bufferMsg(frameDup);
        }
        else
        {
            radioEV << "in the past \n";
        }
    }

    // notify other modules about the channel switch; and actually, IEEE802154Radio state has changed too
    nb->fireChangeNotification(NF_RADIO_CHANNEL_CHANGED, &rs);
    nb->fireChangeNotification(NF_RADIOSTATE_CHANGED, &rs);
}

void IEEE802154Radio::setBitrate(int bitrate, bool firstTime)
{
    // Basic checks
    if (rs.getBitrate() == bitrate)
    {
        return;
    }

    if (bitrate < 0)
    {
        error("SetBitrate(): bit rate cannot be negative (%g)", bitrate);
    }

    if (rs.getState() == RadioState::TRANSMIT)
    {
        error("SetBitrate(): changing the bit rate while transmitting is not allowed");
    }

    // TODO Check and update the symbol rate to newer IEEE 802.15.4 revisions
    switch (bitrate)
    {
        case 20000:
            symbolRate = 20 * 1000;
            break;
        case 40000:
            symbolRate = 40 * 1000;
            break;
        case 250000:
            symbolRate = 62.5 * 1000;
            break;
        default:
            error("SetBitrate(): Bit rate not supported");
            break;
    }

    radioEV << "Setting bit rate to " << (bitrate / 1e3) << "Kbps \n";

    // Don't emit signal during Radio::initialize, only afterwards
    if (!firstTime)
    {
        emit(bitrateSignal, bitrate);
    }

    rs.setBitrate(bitrate);
}

void IEEE802154Radio::setRadioState(RadioState::State newState)
{
    if (rs.getState() != newState)
    {
        emit(IEEE802154RadioStateSignal, newState);

        if (newState == RadioState::SLEEP || newState == RadioState::OFF)
        {
            disconnectTransceiver();
            disconnectReceiver();
        }
        else if (rs.getState() == RadioState::SLEEP || rs.getState() == RadioState::OFF)
        {
            connectTransceiver();
            connectReceiver();
        }

        rs.setState(newState);
        nb->fireChangeNotification(NF_RADIOSTATE_CHANGED, &rs);
    }
}

void IEEE802154Radio::updateSensitivity(double rate)
{
    if (sensitivityList.empty())
    {
        return;
    }

    SensitivityList::iterator it = sensitivityList.find(rate);
    if (it != sensitivityList.end())
    {
        sensitivity = it->second;
    }
    else
    {
        sensitivity = sensitivityList[0.0];
    }

    if (!par("setReceptionThreshold").boolValue())
    {
        receptionThreshold = sensitivity;
    }

    radioEV << "updateSensitivity(): bit rate = " << (rate / 1e3) << "Kbps \n";
    radioEV << "updateSensitivity(): sensitivity after updateSensitivity: " << sensitivity << endl;
}

void IEEE802154Radio::registerBattery()
{
    BasicBattery *bat = BatteryAccess().getIfExists();
    if (bat)
    {
        // read parameters
        double mUsageIEEE802154RadioIdle = par("usage_IEEE802154Radio_idle");
        double mUsageIEEE802154RadioRecv = par("usage_IEEE802154Radio_recv");
        double mUsageIEEE802154RadioSleep = par("usage_IEEE802154Radio_sleep");
        double mUsageIEEE802154RadioSend = par("usage_IEEE802154Radio_send");
        if ( (mUsageIEEE802154RadioIdle < 0) || (mUsageIEEE802154RadioRecv < 0) || (mUsageIEEE802154RadioSleep < 0) || (mUsageIEEE802154RadioSend < 0))
        {
            return;
        }
        bat->registerWirelessDevice(rs.getRadioId(), mUsageIEEE802154RadioIdle, mUsageIEEE802154RadioRecv, mUsageIEEE802154RadioSend, mUsageIEEE802154RadioSleep);
    }
}

void IEEE802154Radio::updateDisplayString()
{
    // draw the interference area and sensitivity area
    // according pathloss propagation only
    // we use the channel controller method to calculate interference distance
    // it should be the methods provided by propagation models, but to
    // avoid a big modification, we reuse those methods.

    if (!ev.isGUI() || !drawCoverage)  // nothing to do
    {
        return;
    }

    if (myRadioRef)
    {
        cDisplayString& d = hostModule->getDisplayString();

        // communication area (up to sensitivity)
        // FIXME this overrides the ranges if more than one radio is present is a host
        double sensitivity_limit = cc->getInterferenceRange(myRadioRef);
        d.removeTag("r1");
        d.insertTag("r1");
        d.setTagArg("r1", 0, (long) sensitivity_limit);
        d.setTagArg("r1", 2, "gray");
        d.removeTag("r2");
        d.insertTag("r2");
        if (doubleRayCoverage)
        {
            d.setTagArg("r2", 0, (long) calcDistDoubleRay());
        }
        else
        {
            d.setTagArg("r2", 0, (long) calcDistFreeSpace());
        }
        d.setTagArg("r2", 2, "blue");
    }

    if (updateString == NULL && updateStringInterval > 0)
    {
        updateString = new cMessage("refresh timer");
    }

    if (updateStringInterval > 0)
    {
        scheduleAt(simTime() + updateStringInterval, updateString);
    }
}

double IEEE802154Radio::calcDistFreeSpace()
{
    // the carrier frequency used
    double carrierFrequency = getChannelControlPar("carrierFrequency");
    // signal attenuation threshold
    // path loss coefficient
    double alpha = getChannelControlPar("alpha");

    double waveLength = (SPEED_OF_LIGHT / carrierFrequency);
    // minimum power level to be able to physically receive a signal
    double minReceivePower = sensitivity;

    double interfDistance = pow(waveLength * waveLength * transmitterPower / (16.0 * M_PI * M_PI * minReceivePower), 1.0 / alpha);
    return interfDistance;
}

double IEEE802154Radio::calcDistDoubleRay()
{
    // the carrier frequency used
    // minimum power level to be able to physically receive a signal
    double minReceivePower = sensitivity;

    double interfDistance = pow(transmitterPower / minReceivePower, 1.0 / 4);

    return interfDistance;
}

void IEEE802154Radio::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj)
{
    ChannelAccess::receiveSignal(source, signalID, obj);
    if (signalID == changeLevelNoise)
    {
        if (BASE_NOISE_LEVEL < receptionThreshold)
        {
            if (rs.getState() == RadioState::RECV && snrInfo.ptr == NULL)
            {
                setRadioState(RadioState::IDLE);
            }
        }
        else
        {
            if (rs.getState() != RadioState::IDLE)
            {
                setRadioState(RadioState::RECV);
            }
        }
    }
}

void IEEE802154Radio::disconnectReceiver()
{
    receiverConnect = false;
    cc->disableReception(this->myRadioRef);
    if (rs.getState() == RadioState::TRANSMIT)
    {
        error("disconnecting the receiver while transmitting is not allowed");
    }

    // Clear the recvBuff
    for (RecvBuff::iterator it = recvBuff.begin(); it != recvBuff.end(); ++it)
    {
        AirFrame *airframe = it->first;
        cMessage *endRxTimer = (cMessage *) airframe->getContextPointer();
        delete airframe;
        delete cancelEvent(endRxTimer);
    }
    recvBuff.clear();

    // clear SNR info
    snrInfo.ptr = NULL;
    snrInfo.sList.clear();
}

void IEEE802154Radio::connectReceiver()
{
    receiverConnect = true;
    cc->enableReception(this->myRadioRef);

    if (rs.getState() != RadioState::IDLE)
    {
        rs.setState(RadioState::IDLE);  // Force IEEE802154Radio to Idle
    }

    cc->setRadioChannel(myRadioRef, rs.getChannelNumber());
    cModule *myHost = findHost();

    cGate* IEEE802154RadioGate = this->gate("radioIn")->getPathStartGate();

    radioEV << "RadioGate: " << IEEE802154RadioGate->getFullPath() << " " << IEEE802154RadioGate->getFullName() << endl;

    // pick up ongoing transmissions on the new channel
    radioEV << "Picking up ongoing transmissions on new channel: \n";
    IChannelControl::TransmissionList tlAux = cc->getOngoingTransmissions(rs.getChannelNumber());
    for (IChannelControl::TransmissionList::const_iterator it = tlAux.begin(); it != tlAux.end(); ++it)
    {
        AirFrame *airframe = check_and_cast<AirFrame *>(*it);
        // time for the message to reach us
        double distance = getRadioPosition().distance(airframe->getSenderPos());
        simtime_t propagationDelay = distance / 3.0E+8;

        // if there is a message on the air which will reach us in the future
        if (airframe->getTimestamp() + propagationDelay >= simTime())
        {
            radioEV << " - (" << airframe->getClassName() << ")" << airframe->getName() << ": ";
            radioEV << "will arrive in the future, scheduling it \n";

            // we need to send to each IEEE802154RadioIn[] gate of this host
            //for (int i = 0; i < IEEE802154RadioGate->size(); i++)
            //    sendDirect(airframe->dup(), airframe->getTimestamp() + propagationDelay - simTime(), airframe->getDuration(), myHost, IEEE802154RadioGate->getId() + i);

            // JcM Fix: we need to this IEEE802154Radio only. no need to send the packet to each IEEE802154RadioIn
            // since other IEEE802154Radios might be not in the same channel
            sendDirect(airframe->dup(), airframe->getTimestamp() + propagationDelay - simTime(), airframe->getDuration(), myHost, IEEE802154RadioGate->getId());
        }
        // if we hear some part of the message
        else if (airframe->getTimestamp() + airframe->getDuration() + propagationDelay > simTime())
        {
            radioEV << "missed beginning of frame, processing it as noise \n";

            AirFrame *frameDup = airframe->dup();
            frameDup->setArrivalTime(airframe->getTimestamp() + propagationDelay);
            handleLowerMsgStart(frameDup);
            bufferMsg(frameDup);
        }
    }
    // notify other modules about the channel switch; and actually, IEEE802154Radio state has changed too
    nb->fireChangeNotification(NF_RADIOSTATE_CHANGED, &rs);
}

void IEEE802154Radio::getSensitivityList(cXMLElement* xmlConfig)
{
    //sensitivityList.empty();      // TODO check if sensitivityList should be cleared or if-case for empty list checking
    if (!sensitivityList.empty())
    {
        sensitivityList.clear();    // XXX fix for previously unused empty check (returns bool)
    }

    if (xmlConfig == 0)
    {
        sensitivityList[0] = FWMath::dBm2mW(par("sensitivity").doubleValue());
        return;
    }

    cXMLElementList sensitivityXmlList = xmlConfig->getElementsByTagName("SensitivityTable");

    if (sensitivityXmlList.empty())
    {
        sensitivityList[0] = FWMath::dBm2mW(par("sensitivity").doubleValue());
        return;
    }

    // iterate over all sensitivity-entries, get a new instance and add
    // it to sensitivityList
    for (cXMLElementList::const_iterator it = sensitivityXmlList.begin(); it != sensitivityXmlList.end(); it++)
    {
        cXMLElement* data = *it;

        cXMLElementList parameters = data->getElementsByTagName("Entry");

        for (cXMLElementList::const_iterator it = parameters.begin(); it != parameters.end(); it++)
        {
            const char* bitRate = (*it)->getAttribute("BitRate");
            const char* sensitivityStr = (*it)->getAttribute("Sensitivity");
            double rate = atof(bitRate);
            if (rate == 0)
            {
                error("invalid bit rate");
            }
            double sens = atof(sensitivityStr);
            sensitivityList[rate] = FWMath::dBm2mW(sens);

        }
        parameters = data->getElementsByTagName("Default");
        for (cXMLElementList::const_iterator it = parameters.begin(); it != parameters.end(); it++)
        {
            const char* sensitivityStr = (*it)->getAttribute("Sensitivity");
            double sens = atof(sensitivityStr);
            sensitivityList[0.0] = FWMath::dBm2mW(sens);
        }

        SensitivityList::iterator sensitivityIt = sensitivityList.find(0.0);
        if (sensitivityIt == sensitivityList.end())
        {
            sensitivityList[0] = FWMath::dBm2mW(par("sensitivity").doubleValue());
        }
    }  // end iterator loop
}

// Functionality of the IEEE 802.15.4 Clear Channel Assessment (CCA) algorithm
void IEEE802154Radio::performCCA()
{
    if (rs.getState() == RadioState::IDLE)
    {
        // change radio state and emit signal
        setRadioState(RadioState::RECV);
    }

    // The CCA Self Timer as described in the IEEE 802.15.4 specification
    simtime_t ccaDuration = 60 / (symbolRate * 8);
    scheduleAt(simTime() + ccaDuration, selfCCAMsg);

    switch (ccaMode)
    {
        case 1:  // Mode 1 - Energy above threshold
        {
            ccaMode1 = true;
            ccaMode2 = false;
            radioEV << "[CCA]: Mode 1 - Energy above threshold \n";
            break;
        }

        case 2:  // Mode 2 - Carrier sensing only
        {
            ccaMode1 = false;
            ccaMode2 = true;
            radioEV << "[CCA]: Mode 2 - Carrier sensing only \n";
            break;
        }

        case 3:  // Mode 3 - Carrier sensing and energy above threshold
        {
            ccaMode1 = true;
            ccaMode2 = true;
            radioEV << "[CCA]: Mode 3 - Carrier sensing and energy above threshold \n";
            break;
        }

        default:
        {
            error("performCCA(): unsupported message parameter for CCA mode in IEEE802154Radio");
            break;
        }
    }

    return;
}

// false if Radio Channel seems to be free (CCA)
void IEEE802154Radio::genCCAConf(bool success)
{
    cMessage* ccaConf = new cMessage("PLME-CCA.confirm");
    ccaConf->setName("PLME-CCA.confirm");
    if (success)
    {
        ccaConf->setKind(phy_IDLE);
    }
    else
    {
        ccaConf->setKind(phy_BUSY);
    }

    send(ccaConf, "upperLayerOut");
    if (selfCCAMsg->isScheduled())
    {
        cancelEvent(selfCCAMsg);
    }

    ccaMode1 = false;
    ccaMode2 = false;
    return;
}

// Functionality for a IEEE 802.15.4 Energy Detection Scan
// We wait for a Message and do not buffer it if received
// just generate a ED-Conf for the UpperLayer if any energy was detected on the selected channel
void IEEE802154Radio::performED()
{
    if (rs.getState() == RadioState::IDLE)
    {
        // change radio state and emit proper signal
        setRadioState(RadioState::RECV);
        // 8 symbols = 1 Byte long ...
        simtime_t edDuration = 60 / (symbolRate * 8);
        scheduleAt(simTime() + edDuration, selfEDMsg);
        activeED = true;
    }
    else
    {
        generateEDconf(0, rs.getState());
    }
    return;
}

void IEEE802154Radio::generateEDconf(double rcvdPower, int status)
{
    cMessage* edConf = new cMessage("PLME-ED.confirm");
    edConf->setName("PLME-ED.confirm");
    // add a double value for received power if ED was a success, otherwise only set the status
    if (status == ED_SUCCESS)
    {
        cMsgPar* power = new cMsgPar();
        power->setDoubleValue(log10(rcvdPower / BASE_NOISE_LEVEL));
        edConf->addPar(power);
        edConf->setKind(status);
    }

    if (selfEDMsg->isScheduled())
    {
        cancelEvent(selfEDMsg);
    }

    edConf->setKind(status);
    send(edConf, "upperLayerOut");
}

void IEEE802154Radio::genPhyConf(phyState state)
{
    cMessage* conf = new cMessage("PD-DATA.confirm");
    conf->setKind(state);
    send(conf, "upperLayerOut");
}
