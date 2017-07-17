//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (smaller fixes, extended WPAN startup and management, ported for INET 2.x)
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

#include "llc.h"
#include "IPSocket.h"

bool llc::firstDevice;

Define_Module(llc);

void llc::initialize(int stage)
{
    cSimpleModule::initialize (stage);
    if (stage == 0)
    {
        // initialize the debug output bool from NED parameter value
        llcDebug = (hasPar("llcDebug") ? (par("llcDebug").boolValue()) : (false));
    }
    else if (stage == 1)
    {
        /* This is for Application layers which cannot send out MCPS primitives
         * if a true LLC is available, it will take care of it
         * just make sure the Application is sending cPackets
         */
        convertingMode = par("convertMode").boolValue();

        TXoption = par("TXoption");
        ASSERT(TXoption <= 7);  // check if TXoption value is a recognized value

        logicalChannel = par("LogicalChannel");

        WATCH(firstDevice);
        WATCH(associateSuccess);
        WATCH(associateStarted);
        WATCH(coordPANId);
        WATCH(coordAddress);
        WATCH(coordAddrMode);
    }
    else if (stage == 2)
    {
        if (convertingMode)
        {
            llcEV << "LLC is operating in 'Converting Mode' \n";
            ASSERT(getModuleByPath("^.^.NIC.MAC.IEEE802154Mac") != NULL);    // getModuleByPath shall return the MAC module
            // Check if startWithoutStartRequest was enabled by user
            if (getModuleByPath("^.^.NIC.MAC.IEEE802154Mac")->par("startWithoutStartReq").boolValue() == false)
            {
                double seed = dblrand();
                llcEV << "Sending Start Request in " << seed << endl;
                selfMsg = new cMessage("LLC-Start");
                selfMsg->setKind(0);
                scheduleAt(seed, selfMsg);
            }
            else
            {
                llcEV << "Starting without an explicit Start Request right now (startwithoutStartReq == true) \n";
            }

            scanChannels = par("ScanChannels");
            scanDuration = par("ScanDuration");
            scanPage = par("ScanPage");
            scanType = par("ScanType");
            pollFreq = par("PollFrequency");

            if (TXoption >= 4)
            {
                pollTimer = new cMessage("LLC-POLL-Timer");
                llcEV << "TXoption set to indirect - starting Poll timer \n";
                pollTimer->setKind(1);
                scheduleAt(pollFreq, pollTimer);
            }
        }
        else
        {
            llcEV << "LLC is operating in transparent forwarding / non-converting mode \n";
        }
    }
}

MACAddressExt llc::tokenDest(cMessage* msg)
{
    // get the IPv6 destination address from the IPv6 Control Info block
    IPv6ControlInfo * controlInfo;
    controlInfo = check_and_cast<IPv6ControlInfo*>(msg->getControlInfo());

    IPv6Address destAddr = controlInfo->getDestAddr();

    if (destAddr.isUnspecified())
    {
        error("[802154LLC]: tokenDest ==> no destination address set / address unspecified");
    }

    // Use the internal representation of the IPv6 address to create the 64-bit EUI MAC address
    // create 8 groups with each 16 bit's (a.k.a. 8 tupels)
    uint16_t groups[8] = { uint16_t(*&destAddr.words()[0] >> 16), uint16_t(*&destAddr.words()[0] & 0xffff), uint16_t(*&destAddr.words()[1] >> 16), uint16_t(*&destAddr.words()[1]
            & 0xffff), uint16_t(*&destAddr.words()[2] >> 16), uint16_t(*&destAddr.words()[2] & 0xffff), uint16_t(*&destAddr.words()[3] >> 16), uint16_t(*&destAddr.words()[3]
            & 0xffff) };

    std::string destString;

    // take the last four tuples
    for (int i = 4; i < 8; ++i)
    {
        std::string sHelp;
        char cHelp[5];

        // convert uint16_t to hex and to string
        sprintf(cHelp, "%x", groups[i]);
        sHelp.append(cHelp);

        // as IPv6 addresses might be compressed, we need to add up "compressed" zeros
        while (sHelp.length() < 4)
        {
            sHelp.insert(0, "0");
        }
        // write everything into the destination string
        destString.append(sHelp);
    }

    // return a new 64-bit EUI MAC address from the destination string
    return (MACAddressExt(destString.c_str()));
}

void llc::genAssoReq()
{
    AssociationRequest* assoReq = new AssociationRequest("MLME-ASSOCIATE.request");
    assoReq->setCoordAddrMode(coordAddrMode);
    assoReq->setCoordPANId(coordPANId);
    assoReq->setCoordAddress(coordAddress);
    DevCapability capInfo;
    capInfo.alloShortAddr = true;
    capInfo.FFD = true;
    capInfo.recvOnWhenIdle = true;
    capInfo.secuCapable = false;
    assoReq->setCapabilityInformation(capInfo);
    assoReq->setChannelPage(0);
    assoReq->setLogicalChannel(logicalChannel);

    send(assoReq, "outMngt");
}

void llc::genPollReq()
{
    PollRequest* pollReq = new PollRequest("MLME-POLL.request");
    pollReq->setCoordAddrMode(addrShort);
    pollReq->setCoordPANId(coordPANId);
    pollReq->setCoordAddress(coordAddress);

    send(pollReq, "outMngt");
}

void llc::genScanReq()
{
    ScanRequest* scanReq = new ScanRequest("MLME-SCAN.request");
    scanReq->setScanType(scanType);  // see enum
    scanReq->setScanChannels(scanChannels);  // 27 bit indicating the channels to be scanned
    scanReq->setScanDuration(scanDuration);  // time spent on scanning each channel
    scanReq->setChannelPage(scanPage);

    send(scanReq, "outMngt");
}

void llc::genOrphanResp(OrphanIndication* oi)
{
    OrphanResponse* oR = new OrphanResponse("MLME-ORPHAN.response");
    oR->setOrphanAddress(oi->getOrphanAddress());
    oR->setShortAddress(0xffff);
    oR->setAssociatedMember(false);

    send(oR, "outMngt");
}

void llc::handleMessage(cMessage *msg)
{
    llcEV << "Got Message in LLC - " << msg->getName() << endl;

    if (msg->isSelfMessage())
    {
        if ((msg->getKind() == 0) && (associateSuccess == false))
        {
            llcEV << "Got Startup Msg && not yet associated -> sending out Scan Request \n";
            genScanReq();
            delete (msg);
        }
        else if ((msg->getKind() == 0) && (associateSuccess == true))
        {
            llcEV << "Got Startup Msg && already associated -> ignoring Startup Msg \n";
            delete (msg);
            return;
        }
        else if (msg->getKind() == 1)
        {
            llcEV << "Got POLL Timer - Sending POLL Request \n";
            genPollReq();
            scheduleAt(simTime() + pollFreq, msg);
        }
        return;
    }

    if (msg->arrivedOn("inApp"))
    {
        if ((msg->getKind() == IP_C_REGISTER_PROTOCOL))
        {
            // FIXME add "register protocol message" handling
            llcEV << "FIXME(!) Register Protocol Message is not handled yet - FullPath: " << msg->getFullPath() << endl;
            delete (msg);
            return;
        }

        if (convertingMode)
        {
            if (!msg->isPacket())
            {
                error("[802154LLC]: Application layer in convertingMode has to send out cPackets!");
            }

            cPacket* pack = check_and_cast<cPacket*>(msg);

            mcpsDataReq* data = new mcpsDataReq("MCPS-DATA.request");
            data->encapsulate(pack);
            //data->setMsduHandle(pack->getId());   // using the message ID can get problematic during longer simulations
            // because the 8 bit DSN value on the MAC layer is going to overflow

            ASSERT(msgHandle <= 255);   // sequence number in MPDU is 8-bit / unsigned char
            data->setMsduHandle(msgHandle);
            (msgHandle < 255) ? msgHandle++ : msgHandle = 0;    // check if 8-bit sequence number needs to roll over

            data->setMsduLength(pack->getByteLength());
            data->setTxOptions(TXoption);
            // try to generate the MAC destination address from the packet's IPvX address destination address
            data->setDstAddr(tokenDest(msg));
            llcEV << "Tokenized Destination Address from IFI / IPvXTrafGen is: " << (data->getDstAddr().str()) << endl;

            send(data, "outData");
            return;
        }
        else
        {
            send(msg, "outData");
        }
    } // if (msg->arrivedOn("inApp"))

    if (msg->arrivedOn("inMngt"))
    {
        if (convertingMode == false)
        {
            llcEV << "Forwarding MLME Message (" << msg->getFullName() << ") to the higher layer \n";
            send(msg, "outApp");
        }
        else
        {
            if (dynamic_cast<beaconNotify*>(msg))
            {
                if (associateSuccess == false)
                {
                    beaconNotify* bN = check_and_cast<beaconNotify*>(msg);
                    coordAddrMode = bN->getPANDescriptor().CoordAddrMode;
                    coordPANId = bN->getPANDescriptor().CoordPANId;
                    coordAddress = bN->getPANDescriptor().CoordAddress;  // shared by both 16 bit short address or 64 bit extended address
                    logicalChannel = bN->getPANDescriptor().LogicalChannel;
                    llcEV << "Beacon Notify received and not yet associated -> generate Association Request for beacon received from existing PAN Coordinator \n";
                    if (ev.isGUI())
                    {
                        this->setDisplayString("i=block/join,#FFFF80,45;i2=status/yellow");
                        char buf[20];
                        sprintf(buf, "status/yellow");
                        getModuleByPath("^.^")->getDisplayString().setTagArg("i2", 0, buf);
                    }
                    genAssoReq();
                    delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                    return;
                }
                else
                {
                    llcEV << "Beacon Notify received and already associated - no further processing of the Beacon Notify \n";
                    delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                    return;
                }
            } // (dynamic_cast<beaconNotify*>(msg))

            if (dynamic_cast<StartConfirm*>(msg))
            {
                // TODO divide between "started your own PAN" and "found a PAN and starting association process" ??
                llcEV << "Got MLME-START.confirm from lower layer \n";

                llcEV << "TODO - add processing of StartConfirm message \n";

                delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                return;
            } // (dynamic_cast<StartConfirm*>(msg))

            if (dynamic_cast<ScanConfirm*>(msg))
            {
                ScanConfirm* scanConf = check_and_cast<ScanConfirm*>(msg);

                if (scanConf->getResultListSize() == 0)
                {
                    llcEV << "Got MLME-SCAN.confirm with ResultListSize == 0 \n";

                    if (firstDevice)
                    {
                        llcEV << "First global device without results sends out MLME-START for Coordinator \n";

                        startMsg = new StartRequest("MLME-START.request");
                        startMsg->setPANId(par("PANId"));
                        startMsg->setLogicalChannel(logicalChannel);
                        startMsg->setChannelPage(par("ChannelPage"));
                        startMsg->setStartTime(par("StartTime"));
                        startMsg->setBeaconOrder(par("BeaconOrder"));
                        startMsg->setSuperframeOrder(par("SuperframeOrder"));
                        startMsg->setBatteryLifeExtension(par("BatteryLifeExtension"));
                        startMsg->setPANCoordinator(true);
                        startMsg->setCoordRealignment(false);   // override user parameter here since 1st device starts PAN and doesn't realign it

                        firstDevice = false;
                        send(startMsg, "outMngt");
                        delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                        return;
                    }
                    else
                    {
                        llcEV << "No results - scan again \n";
                        genScanReq();
                        delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                        return;
                    }
                }
                else
                {
                    llcEV << "Got MLME-SCAN.confirm with ResultListSize > 0 \n";

                    unsigned short panId = par("PANId");
                    logicalChannel = par("LogicalChannel");
                    unsigned short channelPage = par("ChannelPage");
                    unsigned int startTime = par("StartTime");
                    unsigned short beaconOrder = par("BeaconOrder");
                    unsigned short superframeOrder = par("SuperframeOrder");
                    bool batteryLifeExtension = par("BatteryLifeExtension").boolValue();
                    bool coordRealignment = par("CoordRealignment").boolValue();

                    startMsg = new StartRequest("MLME-START.request");
                    startMsg->setPANId(panId);
                    startMsg->setLogicalChannel(logicalChannel);
                    startMsg->setChannelPage(channelPage);
                    startMsg->setStartTime(startTime);
                    startMsg->setBeaconOrder(beaconOrder);
                    startMsg->setSuperframeOrder(superframeOrder);
                    startMsg->setBatteryLifeExtension(batteryLifeExtension);
                    startMsg->setCoordRealignment(coordRealignment);

                    startMsg->setPANCoordinator(false);
                    send(startMsg, "outMngt");
                    delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                    return;
                }
            } // (dynamic_cast<ScanConfirm*>(msg))

            if (dynamic_cast<AssociationConfirm*>(msg)) // MLME-Association.confirm
            {
                llcEV << "Association Confirm received --> association process was successful \n";
                if (ev.isGUI())
                {
                    bubble("Association successful");
                    this->setDisplayString("i=block/join,#80FF00,45;i2=status/green");
                    char buf[20];
                    sprintf(buf, "status/green");
                    getModuleByPath("^.^")->getDisplayString().setTagArg("i2", 0, buf);
                }
                associateSuccess = true;
                associateStarted = false;
                delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                return;
            } // (dynamic_cast<AssociationConfirm*>(msg))

            if (dynamic_cast<Association*>(msg))    // MLME-Association.indication
            {
                llcEV << "Association Indication received --> association response will be sent automatically by the MAC \n";

                if (ev.isGUI())
                {
                    this->setDisplayString("i=block/join,#FFFF80,45;i2=status/yellow");
                    char buf[20];
                    sprintf(buf, "status/yellow");
                    getModuleByPath("^.^")->getDisplayString().setTagArg("i2", 0, buf);
                }
                // actually need to wait for ACK to confirm the correct association
                // as the LLC currently does not cover processes / tasks, check during the reception of mcpsDataConf
                // if an acknowledge was received
                associateStarted = true;

                delete (msg);   // delete received msg because in convertingMode the higher layer does not understand MLME messages and is not further notified
                return;
            } // (dynamic_cast<Association*>(msg))

            if (dynamic_cast<OrphanIndication*>(msg))
            {
                // just for convenience of functional tests
                OrphanIndication* oi = check_and_cast<OrphanIndication*>(msg);
                genOrphanResp(oi);
                delete (msg);
                return;
            } // (dynamic_cast<OrphanIndication*>(msg))

            // For all other msg types -> since we are converting assume application layer won't understand any MLME messages
            llcEV << "convertingMode -> deleting MLME Message: " << msg->getFullName() << " without forwarding it to higher layer \n";
            delete (msg);
            return;
        }   // if (convertingMode)
    } // if (msg->arrivedOn("inMngt"))

    if (msg->arrivedOn("inData"))
    {
        if (convertingMode == false)
        {
            llcEV << "Forwarding MCPS-Data to the higher layer -> " << msg->getFullName() << endl;
            send(msg, "outApp");
            return;
        }
        else
        {
            // this can only be a confirm or indication
            if (dynamic_cast<mcpsDataInd*>(msg))
            {
                mcpsDataInd* ind = check_and_cast<mcpsDataInd*>(msg);
                cPacket* payload = ind->decapsulate();
                llcEV << "Forwarding MCPS-Data.indication for Message #" << (int) ind->getDSN() << " to the higher layer \n";
                send(payload, "outApp");
                delete (msg);   // fix for undisposed object: (mcpsDataInd) net.IEEE802154Nodes[*].Network.stdLLC.MCPS-DATA.indication
                return;
            } // (dynamic_cast<mcpsDataInd*>(msg))
            else if (dynamic_cast<mcpsDataConf*>(msg))
            {
                mcpsDataConf* conf = check_and_cast<mcpsDataConf*>(msg);
                if (associateStarted)
                {
                    if (conf->getStatus() == SUCCESS)
                    {
                        associateSuccess = true;
                        associateStarted = false;
                        llcEV << "Acknowledge for MLME-ASSOCIATE.response received --> association process was successful \n";
                        if (ev.isGUI())
                        {
                            bubble("Association successful");
                            this->setDisplayString("i=block/join,#80FF00,45;i2=status/green");
                            char buf[22];
                            sprintf(buf, "status/green");
                            getModuleByPath("^.^")->getDisplayString().setTagArg("i2", 0, buf);
                        }
                    }
                    else if (conf->getStatus() == NO_ACK)
                    {
                        llcEV << "No ACK for MLME-ASSOCIATE.response received --> association process was NOT successful!!! \n";
                    }
                }
                else
                {
                    llcEV << "Got CONFIRM from MAC with Status: " << MCPSStatusToString(MCPSStatus(conf->getStatus())) << " for Message #" << (int) conf->getMsduHandle() << endl;
                }
                send(conf, "outApp");
                return;
            } // (dynamic_cast<mcpsDataConf*>(msg))
            else
            {
                error("[802154LLC]: Undefined Message arrived at inData gate!");
            }
        } // if (convertingMode)
    } // if msg->arrivedOn("inData")
}

llc::llc()
{
    logicalChannel = 0;
    convertingMode = false;
    TXoption = 0;
    firstDevice = true;
    associateSuccess = false;
    msgHandle = intrand(255);
    associateSuccess = false;
    associateStarted = false;
    coordAddrMode = 0;
    coordPANId = 0;
    scanChannels = 0;
    scanDuration = 0.0;
    scanPage = 0;
    scanType = 0;
    startMsg = NULL;
    selfMsg = NULL;
    pollTimer = NULL;
}

llc::~llc()
{
    if (TXoption >= 4)
    {
        if (pollTimer)
            cancelAndDelete(pollTimer);
    }
}
