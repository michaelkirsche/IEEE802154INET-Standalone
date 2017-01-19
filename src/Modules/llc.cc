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

void llc::initialize()
{
    if (hasPar("llcDebug"))
    {
        llcDebug = par("llcDebug").boolValue();
    }
    else
    {
        llcDebug = false;
    }

    /* This is for Application layers which cannot send out MCPS primitives
     * if a true LLC is available, it will take care of it
     * just make sure the Application is sending cPackets
     */
    double seed = dblrand();
    convertingMode = par("convertMode").boolValue();

    TXoption = par("TXoption");
    logicalChannel = par("LogicalChannel");

    firstDevice = true;
    associateSuccess = false;

    WATCH(firstDevice);
    WATCH(associateSuccess);

    if (convertingMode)
    {
        // Check if startWithoutStartRequest was enabled by user
        if (getModuleByPath("net.IEEE802154Nodes[0].NIC.MAC.IEEE802154Mac")->par("startWithoutStartReq").boolValue() == false)
        {
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

}

MACAddressExt* llc::tokenDest(cMessage* msg)
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
    // create 8 groups with each 16 bit's (aka 8 tupels)
    uint16_t groups[8] = { uint16_t(*&destAddr.words()[0] >> 16), uint16_t(*&destAddr.words()[0] & 0xffff), uint16_t(*&destAddr.words()[1] >> 16),
            uint16_t(*&destAddr.words()[1] & 0xffff), uint16_t(*&destAddr.words()[2] >> 16), uint16_t(*&destAddr.words()[2] & 0xffff), uint16_t(
                     *&destAddr.words()[3] >> 16), uint16_t(*&destAddr.words()[3] & 0xffff) };

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

    // create a new 64-bit EUI MAC address from the destination string
    MACAddressExt* dest = new MACAddressExt(destString.c_str());
    llcEV << "Tokenized Destination Address from IFI / IPvXTrafGen is: " << dest->str() << endl;
    return dest;
}

void llc::genAssoReq()
{
    AssociationRequest* assoReq = new AssociationRequest("MLME-ASSOCIATE.request");
    MACAddressExt* coordId = new MACAddressExt(coordPANId);
    assoReq->setCoordAddrMode(coordAddrMode);
    assoReq->setCoordPANId(*coordId);
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
        if (msg->getKind() == 0)
        {
            llcEV << "Got Startup Msg - Sending out Scan Request \n";
            genScanReq();
            delete (msg);
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
            llcEV << "FIXME(!) Register Protocol Message is not handled yet - FullPath: " << msg->getFullPath() << endl;
            delete (msg);
            return;
        }

        if (convertingMode)
        {
            if (!msg->isPacket())
                error("[802154LLC]: Application layer in convertingMode has to send out cPackets!");

            cPacket* pack = check_and_cast<cPacket*>(msg);

            mcpsDataReq* data = new mcpsDataReq("MCPS-DATA.request");
            data->encapsulate(pack);
            //data->setMsduHandle(pack->getId());   // using the message ID can get problematic during longer simulations
                                                    // because the 8 bit DSN value on the MAC layer is going to overflow
            data->setMsduHandle(msgHandle);
            if (msgHandle < 255)
            {
                msgHandle++;
            }
            else
            {
                msgHandle = 0;
            }
            data->setMsduLength(pack->getByteLength());
            data->setTxOptions(TXoption);
            // try to generate the MAC destination address from the packet's IPvX address destination address
            MACAddressExt* destination = tokenDest(msg);
            data->setDstAddr(*destination);

            send(data, "outData");
            return;
        }
        else
        {
            send(msg, "outData");
        }
    } // if (msg->arrivedOn("inApp"))
    else if (msg->arrivedOn("inMngt"))
    {
        if (convertingMode)
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
                    llcEV << "Beacon Notify received an not yet associated -> generate Association Request for the existing PAN Coordinator \n";
                    genAssoReq();
                }
                else
                {
                    llcEV << "Beacon Notify received and associated - no further processing of the Beacon Notify \n";
                }
            }

            if (dynamic_cast<StartConfirm*>(msg))
            {
                // TODO divide between "started your own PAN" and "found a PAN and starting association process" ??
                llcEV << "Got MLME-START.confirm from lower layer \n";
            }

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
                    }
                    else
                    {
                        llcEV << "No results - scan again \n";
                        genScanReq();
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
                    bool batteryLifeExtension = par("BatteryLifeExtension");
                    bool coordRealignment = par("CoordRealignment");        

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
                }
            }

            if (dynamic_cast<AssociationConfirm*>(msg))
            {
                llcEV << "Association Confirm received - association process was successful \n";
                associateSuccess = true;
            }

            if (dynamic_cast<OrphanIndication*>(msg))
            {
                // just for convenience of functional tests
                OrphanIndication* oi = check_and_cast<OrphanIndication*>(msg);
                genOrphanResp(oi);
            }

            // Since we are converting assume application layer won't understand any MLME messages
            llcEV << "convertingMode -> deleting MLME Message without forwarding it to higher layer -> " << msg->getFullName() << endl;
            delete (msg);
            return;
        }

        llcEV << "Forwarding MLME Message (" << msg->getFullName() << ") to the higher layer \n";
        send(msg, "outApp");

    } // if (msg->arrivedOn("inMngt"))

    if (msg->arrivedOn("inData"))
    {
        if (convertingMode)
        {
            // this can only be a confirm or indication
            if (dynamic_cast<mcpsDataInd*>(msg))
            {
                mcpsDataInd* ind = check_and_cast<mcpsDataInd*>(msg);
                cPacket* payload = ind->decapsulate();
                llcEV << "Forwarding MCPS-Data.indication for Message #" << (int) ind->getDSN() << " to the higher layer \n";
                send(payload, "outApp");
                //delete (msg); // XXX fix for undisposed object: (mcpsDataInd) net.IEEE802154Nodes[0].Network.stdLLC.MCPS-DATA.indication
                return;
            }
            else if (dynamic_cast<mcpsDataConf*>(msg))
            {
                mcpsDataConf* conf = check_and_cast<mcpsDataConf*>(msg);
                llcEV << "Got a Confirmation from MAC entity with Status: " << MCPSStatusToString(MCPSStatus(conf->getStatus())) << " for Message #" << (int) conf->getMsduHandle() << endl;
                send(conf, "outApp");
                //delete (msg); // XXX fix for undisposed object: (mcpsDataConf) net.IEEE802154Nodes[0].Network.stdLLC.MCPS-DATA.confirmation
                return;
            }
            else
            {
                error("[LLC]: Undefined Message arrived on inData gate!");
            }
        }
        else
        {
            llcEV << "Forwarding MCPS-Data to the higher layer -> " << msg->getFullName() << endl;
            send(msg, "outApp");
            return;
        }
    }
}

llc::llc()
{
    logicalChannel = 0;
    convertingMode = false;
    TXoption = 0;
    msgHandle = 0;
    associateSuccess = false;
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
