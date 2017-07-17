//
// Copyright (C) 2013 Matti Schnurbusch (original code)
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

#include "IEEE802154Phy.h"

Define_Module(IEEE802154Phy);

void IEEE802154Phy::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == 0)
    {
        // initialize the debug output bool from NED parameter value
        phyDebug = (hasPar("phyDebug") ? (par("phyDebug").boolValue()) : (false));

        trxState = phy_IDLE;

        // assign the message names for Upper Layer messages (typically requests)
        mappedUpperLayerMsgTypes["PLME-SET-TRX-STATE.request"] = SETTRXSTATE;
        mappedUpperLayerMsgTypes["PLME-GET.request"] = GET;
        mappedUpperLayerMsgTypes["PLME-SET.request"] = SET;
        mappedUpperLayerMsgTypes["PLME-CCA.request"] = CCA;
        mappedUpperLayerMsgTypes["PLME-ED.request"] = ED;
        mappedUpperLayerMsgTypes["PD-DATA.request"] = CONF;

        // assign the message names for Lower Layer messages (typically confirms)
        mappedLowerLayerMsgTypes["PLME-SET-TRX-STATE.confirm"] = SETTRXSTATE;
        mappedLowerLayerMsgTypes["PLME-GET.confirm"] = GET;
        mappedLowerLayerMsgTypes["PLME-SET.confirm"] = SET;
        mappedLowerLayerMsgTypes["PLME-CCA.confirm"] = CCA;
        mappedLowerLayerMsgTypes["PLME-ED.confirm"] = ED;
        mappedLowerLayerMsgTypes["PD-DATA.confirm"] = CONF;

        tokenizePages();

        pib = PhyPIB(par("currentChannel"), suppPages, par("transmitPower"), par("CCAMode"), par("currentPage"), par("SHRDuration"), par("symbolsPerOctet"));
    }
}

void IEEE802154Phy::tokenizePages()
{
    cStringTokenizer tokenizer(par("channelsSupported"), ",");
    std::vector<std::string> v = tokenizer.asVector();
    suppPages[0] = atoi(v[0].c_str());
    suppPages[1] = atoi(v[1].c_str());
    suppPages[2] = atoi(v[2].c_str());
    return;
}

ppdu *IEEE802154Phy::generatePPDU(cMessage *psdu, bool ackFlag)
{
    ppdu *pdu = new ppdu("PD-DATA");
    cPacket *pk = dynamic_cast<cPacket *>(psdu);
    pdu->setSFD(229); // set SFD to 11100101 except for TODO ASK

    if (ackFlag)
    {
        pdu->setPHR(5);
    }
    else
    {
        pdu->setPHR(pk->getByteLength() + 6);
        pdu->setByteLength(pk->getByteLength() + 6); // needed for calculation in Radio Module
    }

    phyEV << "The Frame length (PHR in PHY) is set to " << (unsigned short) pdu->getPHR() << endl;
    pdu->encapsulate(pk);
    return pdu;
}

void IEEE802154Phy::handleMessage(cMessage *msg)
{
    phyEV << "Got Message " << msg->getName() << endl;
    if (msg->arrivedOn("PLME_SAP")) // --> Message arrived from MAC over PHY-Management-Layer-Entity SAP
    {
        if (dynamic_cast<AssoCmdreq *>(msg) != NULL)
        {
            send(msg, "outToRadio");
            return;
        }
        else if (dynamic_cast<DisAssoCmd*>(msg) != NULL)
        {
            send(msg, "outToRadio");
            return;
        }
        else if (dynamic_cast<GTSCmd*>(msg) != NULL)
        {
            send(msg, "outToRadio");
            return;
        }
        else if (dynamic_cast<CmdFrame*>(msg) != NULL)
        {
            send(msg, "outToRadio");
            return;
        }

        switch (mappedUpperLayerMsgTypes[msg->getName()])
        {
            case SETTRXSTATE: {
                if (trxState == msg->getKind())
                {
                    sendTrxConf((phyState) msg->getKind());
                }
                else
                {
                    sendTrxConf(phy_SUCCESS);
                }
                trxState = (phyState) msg->getKind();
                phyEV << "Setting TRX State to " << phyStateToString(trxState) << endl;
                send(msg, "outToRadio");
                break;
            }

            case GET: {
                phyEV << "PLME-GET.request received -> sending PhyPIB attribute with PLME-GET.confirm upwards \n";
                GetRequest* PhyPIBGet;
                PhyPIBGet = check_and_cast<GetRequest *>(msg);
                getPhyPIB(PhyPIBGet->getPIBattr(), PhyPIBGet->getPIBind());
                delete (msg);       // XXX fix for undisposed object
                break;
            }

            case SET: {
                phyEV << "PLME-SET.request received -> setting PhyPIB attribute and confirming with PLME-SET.confirm \n";
                SetRequest* PhyPIBSet;
                PhyPIBSet = check_and_cast<SetRequest *>(msg);
                setPhyPIB(PhyPIBSet);
                delete (PhyPIBSet);   // XXX fix for undisposed object
                break;
            }

            case CCA: {
                if (trxState)
                {
                    phyEV << "PLME-CCA.request arrived -> performing CCA \n";
                    performCCA(pib.getCCA());
                }
                else
                {
                    phyEV << "PLME-CCA.request arrived -> returning PLME-CCA.confirm \n";
                    cPacket* ccaConf = new cPacket("PLME-CCA.confirm");
                    ccaConf->setName("PLME-CCA.confirm");
                    ccaConf->setKind(phy_TRX_OFF);
                    send(ccaConf, "outPLME");
                }
                delete (msg);   // XXX fix for undisposed object
                break;
            }

            case ED: {
                if (trxState)
                {
                    phyEV << "PLME-ED.request arrived -> performing ED \n";
                    performED();
                }
                delete (msg);   // XXX fix for undisposed object
                break;
            }

            default: {
                error("Message with kind: %d and name: %s arrived on PLME-SAP is not defined! \n", msg->getKind(), msg->getName());
                break;
            }
        } // switch (mappedMsgTypes[msg->getName()])
    } // if (msg->arrivedOn("PLME_SAP"))
    else if (msg->arrivedOn("PD_SAP")) // --> Message arrived from MAC layer over PHY-DATA SAP
    {
        // check which type of MAC packet is arriving to decide how to generate a PPDU and calculate correct MAC payload size
        if (dynamic_cast<AckFrame *>(msg) != 0)
        {
            ppdu *pdu = generatePPDU(msg, true);
            send(pdu, "outToRadio");
            return;
        }
        else    // PD-DATA.request
        {
            ppdu *pdu = generatePPDU(msg, false);
            send(pdu, "outToRadio");
            return;
        }
    } // if (msg->arrivedOn("PD_SAP"))
    else if (msg->arrivedOn("inFromRadio")) // --> Message arrived from lower layer radioInterface
    {
        if (dynamic_cast<AckFrame *>(msg) != NULL)
        {
            send(msg, "outPD");
            return;
        }
        else if (dynamic_cast<AssoCmdreq *>(msg) != NULL)
        {
            send(msg, "outPD");
            return;
        }
        else if (dynamic_cast<AssoCmdresp *>(msg) != NULL)
        {
            send(msg, "outPD");
            return;
        }
        else if (dynamic_cast<DisAssoCmd*>(msg) != NULL)
        {
            send(msg, "outPD");
            return;
        }
        else if (dynamic_cast<GTSCmd*>(msg) != NULL)
        {
            send(msg, "outPD");
            return;
        }
        else if (dynamic_cast<CmdFrame*>(msg) != NULL)
        {
            error("just for testing remove later, this should be a beacon request, name is %s \n", msg->getName()); // XXX remove after testing
            send(msg, "outPD");
            return;
        }
        else if (dynamic_cast<pdDataInd *>(msg) != NULL)
        {
            pdDataInd *pdu = check_and_cast<pdDataInd*>(msg);
            if (pdu->hasEncapsulatedPacket() == true)
            {
                cPacket* payload = pdu->decapsulate();  // use cPacket since it can either be an MPDU or an ACK
                //payload->setKind(pdu->getPpduLinkQuality());  // FIXME we cannot hide LQI in kind because PhyIndication enums are saved there for MAC filtering
                // XXX PHY should actually forward the pdDataIndication to the MAC, not decapsulate and only forward the PPDU
                // LQI from pdDataIndication is needed for mscp.DataIndication
                // in function: void IEEE802154Mac::sendMCPSDataIndication(mpdu* rxData)
                phyEV << "is sending up the Payload of " << pdu->getName() << " which is a " << payload->getName() << endl;

                send(payload, "outPD");
                delete (pdu);
            }
            else
            {
                // this should be a beacon request command
                error("just for testing remove later, this should be a beacon request, name is %s \n", msg->getName()); // XXX remove after testing
                send(msg, "outPD"); // can probably be removed
            }
            return;
        }

        // forward PLME-xxx.confirm messages from the lower radio layer to the MAC layer
        switch (mappedLowerLayerMsgTypes[msg->getName()])
        {
            case CONF: {
                send(msg, "outPD");
                return;
            }

            case SETTRXSTATE:
            case GET:
            case SET:
            case CCA:
            case ED: {
                send(msg, "outPLME");
                return;
            }

            default: {
                error("[802154PHY] Undetermined msg kind %d | msg name %s -->", msg->getKind(), msg->getName());
                break;
            }
        }
    } // if (msg->arrivedOn("inFromRadio"))
}

// Just inform the Radio Module to perform a CCA
void IEEE802154Phy::performCCA(unsigned short mode)
{
    cMessage* ccaRequ = new cMessage("PLME-CCA.request");
    cMsgPar* ccaMode = new cMsgPar();
    ccaMode->setLongValue(mode);
    ccaRequ->addPar(ccaMode);
    ccaRequ->setKind(CCA);
    ccaRequ->setName("PLME-CCA.request");
    send(ccaRequ, "outToRadio");
    return;
}

// Just inform the Radio Module to perform a ED
void IEEE802154Phy::performED()
{
    // send a ED request out to the antenna module and wait for its answer
    cMessage* edRequ = new cMessage("PLME-ED.request");
    edRequ->setKind(ED);
    edRequ->setName("PLME-ED.request");
    send(edRequ, "outToRadio");
    return;
}

void IEEE802154Phy::setPhyPIB(SetRequest * PhyPIBSet)
{
    SetConfirm* PhyPIBSetConf = new SetConfirm("PLME-SET.confirm");
    PhyPIBSetConf->setPIBattr(PhyPIBSet->getPIBattr());
    PhyPIBSetConf->setName("PLME-SET.confirm");
    PhyPIBSetConf->setStatus(PhyPIB_SUCCESS);

    switch (PhyPIBSet->getPIBattr())
    {
        case currentChannel: {
            cMessage* radioPropMsg = new cMessage("phy_change_Channel");
            cMsgPar* prop = new cMsgPar();

            pib.setCurrChann(PhyPIBSet->getValue());
            radioPropMsg->setName("phy_change_Channel");
            radioPropMsg->setKind(phy_CHANGE_CHANNEL);
            prop->setLongValue(PhyPIBSet->getValue());
            radioPropMsg->addPar(prop);
            send(radioPropMsg, "outToRadio");
            break;
        }

        case channelSupported: {
            PhyPIBSetConf->setStatus(PhyPIB_READ_ONLY); // Read-Only according to the specification
            break;
        }

        case transmitPower: {
            cMessage* radioPropMsg = new cMessage("phy_change_Transmitter_Power");
            cMsgPar* prop = new cMsgPar();

            pib.setTransPow(PhyPIBSet->getValue());
            radioPropMsg->setName("phy_change_Transmitter_Power");
            radioPropMsg->setKind(phy_CHANGE_TRANSMITTER_POWER);
            prop->setDoubleValue(PhyPIBSet->getValue());
            radioPropMsg->addPar(prop);
            send(radioPropMsg, "outToRadio");
            break;
        }

        case CCA_Mode: {
            pib.setCCA(PhyPIBSet->getValue());
            break;
        }

        case currentPage: {
            pib.setCurrPage(PhyPIBSet->getValue());
            break;
        }

        case SHRDuration: {
            PhyPIBSetConf->setStatus(PhyPIB_READ_ONLY); // Read-Only according to the specification
            break;
        }

        case symbolsPerSecond: {
            PhyPIBSetConf->setStatus(PhyPIB_READ_ONLY); // Read-Only according to the specification
            break;
        }

        default: {
            PhyPIBSetConf->setStatus(PhyPIB_UNSUPPORTED_ATTRIBUTE);
            break;
        }
    } // switch (PhyPIBSet->getPIBattr())

    send(PhyPIBSetConf, "outPLME");

    return;
}

void IEEE802154Phy::getPhyPIB(int attr, int index)
{
    GetConfirm* PhyPIBGetConf = new GetConfirm("PLME-GET.confirm");
    PhyPIBGetConf->setName("PLME-GET.confirm");
    PhyPIBGetConf->setPIBattr(attr);
    PhyPIBGetConf->setPIBind(index);
    PhyPIBGetConf->setStatus(PhyPIB_SUCCESS);

    switch (attr)
    {
        case currentChannel: {
            PhyPIBGetConf->setValue(pib.getCurrChann());
            break;
        }

        case channelSupported: {
            PhyPIBGetConf->setValue(pib.getChannSupp()[index]);
            break;
        }

        case transmitPower: {
            PhyPIBGetConf->setValue(pib.getTransPow());
            break;
        }

        case CCA_Mode: {
            PhyPIBGetConf->setValue(pib.getCCA());
            break;
        }

        case currentPage: {
            PhyPIBGetConf->setValue(pib.getCurrPage());
            break;
        }

        case SHRDuration: {
            PhyPIBGetConf->setValue(pib.getSHR());
            break;
        }

        case symbolsPerSecond: {
            PhyPIBGetConf->setValue(pib.getSymbols());
            break;
        }

        default: {
            PhyPIBGetConf->setStatus(PhyPIB_UNSUPPORTED_ATTRIBUTE);
            PhyPIBGetConf->setValue(0);
            break;
        }
    } // switch (attr)

    send(PhyPIBGetConf, "outPLME");

    return;
}

void IEEE802154Phy::sendTrxConf(phyState status)
{
    cMessage* setTRXStateConf = new cMessage("PLME-SET-TRX-STATE.confirm");
    setTRXStateConf->setName("PLME-SET-TRX-STATE.confirm");
    setTRXStateConf->setKind(status);
    send(setTRXStateConf, "outPLME");
    return;
}
