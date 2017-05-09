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

void IEEE802154Phy::initialize()
{
    // initialize the debug ouput bool from NED parameter value
    phyDebug = (hasPar("phyDebug") ? (par("phyDebug").boolValue()) : (false));

    trxState = phy_IDLE;

    mappedMsgTypes["SET-TRX-STATE"] = SETTRXSTATE;
    mappedMsgTypes["GET"] = GET;
    mappedMsgTypes["SET"] = SET;
    mappedMsgTypes["CCA"] = CCA;
    mappedMsgTypes["ED"] = ED;
    mappedMsgTypes["PD-DATA.confirm"] = CONF;
    mappedMsgTypes["PHY-SET.confirm"] = SETCONF;

    tokenizePages();

    pib = PhyPIB(par("currentChannel"), suppPages, par("transmitPower"), par("CCAMode"), par("currentPage"), par("SHRDuration"), par("symbolsPerOctet"));
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
        phyEV << "The Frame length (PHR in PHY) is set to " << (unsigned short) pdu->getPHR() << endl;
        pdu->setByteLength(pk->getByteLength() + 6); // needed for calculation in Radio Module
    }
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
            // just forwarding it
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
        else if (dynamic_cast<CmdFrame*>(msg))
        {
            send(msg, "outToRadio");     // should be a beacon request forward
            return;
        }

        switch (mappedMsgTypes[msg->getName()])
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
                phyEV << "Sending PhyPIB upwards \n";
                GetRequest* PhyPIBGet;
                PhyPIBGet = check_and_cast<GetRequest *>(msg);
                sendPhyPIB(PhyPIBGet->getPIBattr(), PhyPIBGet->getPIBind());
                break;
            }

            case SET: {
                phyEV << "Setting PhyPIB-Attributes \n";
                GetConfirm* PhyPIBSet;
                PhyPIBSet = check_and_cast<GetConfirm *>(msg);
                setPhyPIB(PhyPIBSet);
                delete PhyPIBSet;           // XXX fix for undisposed object GetConfirm
                break;
            }

            case CCA: {
                if (trxState)
                {
                    phyEV << "CCARequest arrived -> performing CCA \n";
                    performCCA(pib.getCCA());
                    delete (msg);
                    return;
                }
                else
                {
                    phyEV << "CCARequest arrived -> returning PLME-CCA.confirm \n";
                    cPacket* ccaConf = new cPacket("PLME-CCA.confirm");
                    ccaConf->setKind(phy_TRX_OFF);
                    send(ccaConf, "outPLME");
                }
                break;

            }

            case ED: {
                if (trxState)
                {
                    phyEV << "Performing ED \n";
                    performED();
                }
                break;

            }

            default: {
                throw cRuntimeError("Message arrived on PLME-SAP is not defined! \n");
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
        }
        else
        {
            ppdu *pdu = generatePPDU(msg, false);
            send(pdu, "outToRadio");
        }
    } // if (msg->arrivedOn("PD_SAP"))
    else if (msg->arrivedOn("inFromRadio")) // --> Message arrived from radioInterface
    {
        // create Conf message for the MAC layer
        if (mappedMsgTypes[msg->getName()] == ED)
        {
            msg->setName("PLME-ED.confirm");
            send(msg, "outPLME");
            return;
        }
        else if (mappedMsgTypes[msg->getName()] == CCA)
        {
            msg->setName("PLME-CCA.confirm");
            send(msg, "outPLME");
        }
        else if (dynamic_cast<AssoCmdreq *>(msg) != NULL)
        {
            send(msg, "outPLME");
        }
        else if (dynamic_cast<AssoCmdresp *>(msg) != NULL)
        {
            send(msg, "outPLME");
        }
        else if (dynamic_cast<pdDataInd *>(msg) != NULL)
        {
            pdDataInd *pdu = check_and_cast<pdDataInd*>(msg);
            if (pdu->getEncapsulatedPacket() != NULL)
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
                // this is a beacon request command
                send(msg, "outPLME");
            }
        }
        else if (dynamic_cast<AckFrame *>(msg) != 0)
        {
            send(msg, "outPLME");
        }
        else if (dynamic_cast<DisAssoCmd*>(msg) != 0)
        {
            send(msg, "outPLME");
        }
        else if (dynamic_cast<GTSCmd*>(msg) != 0)
        {
            send(msg, "outPLME");
        }
        else if (mappedMsgTypes[msg->getName()] == CONF)
        {
            send(msg, "outPD");
        }
        else
        {
            phyEV << "Forwarding unknown MSG-Type to MAC \n";
            send(msg, "outPD");
        }
    } // if (msg->arrivedOn("inFromRadio"))
}

// Just inform the Radio Module to perform a CCA
void IEEE802154Phy::performCCA(unsigned short mode)
{
    cMessage* ccaRequ = new cMessage("ccaRequ");
    cMsgPar* ccaMode = new cMsgPar();
    ccaMode->setLongValue(mode);
    ccaRequ->addPar(ccaMode);
    ccaRequ->setKind(CCA);
    send(ccaRequ, "outToRadio");
    return;
}

// Just inform the Radio Module to perform a ED
void IEEE802154Phy::performED()
{
    // send a ED request out to the antenna module and wait for its answer
    cMessage* edRequ = new cMessage("PLME-ED.request");
    edRequ->setKind(ED);
    send(edRequ, "outToRadio");
    return;
}

void IEEE802154Phy::setPhyPIB(GetConfirm * PhyPIBSet)
{
    GetConfirm * PhyPIBSetConf = new GetConfirm("PLME-SET.confirm");
    PhyPIBSetConf->setPIBattr(PhyPIBSet->getPIBattr());
    PhyPIBSetConf->setPIBind(PhyPIBSet->getPIBind());
    PhyPIBSetConf->setStatus(Success);

    switch (PhyPIBSet->getPIBattr())
    {
        case currentChannel: {
            cMessage* radioPropMsg = new cMessage();
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
            PhyPIBSetConf->setStatus(PhyPIB_READ_ONLY);
            break;
        }

        case transmitPower: {
            cMessage* radioPropMsg = new cMessage();
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

        case SHRduration: {
            pib.setSHR(PhyPIBSet->getValue());
            break;
        }

        case symbolsPerSecond: {
            pib.setSymbols(PhyPIBSet->getValue());
            break;
        }

        default: {
            PhyPIBSet->setStatus(PhyPIB_UNSUPPORTED_ATTRIBUTE);
            break;
        }
    } // switch (PhyPIBSet->getPIBattr())

    send(PhyPIBSetConf, "outPLME");

    return;
}

void IEEE802154Phy::sendPhyPIB(int attr, int index)
{
    GetConfirm* PhyPIBGet = new GetConfirm("PLME-GET.confirm");

    PhyPIBGet->setPIBattr(attr);
    PhyPIBGet->setPIBind(index);
    PhyPIBGet->setStatus(PhyPIB_SUCCESS);

    switch (attr)
    {
        case currentChannel: {
            PhyPIBGet->setValue(pib.getCurrChann());
            break;
        }

        case channelSupported: {
            PhyPIBGet->setValue(pib.getChannSupp()[index]);
            break;
        }

        case transmitPower: {
            PhyPIBGet->setValue(pib.getTransPow());
            break;
        }

        case CCA_Mode: {
            PhyPIBGet->setValue(pib.getCCA());
            break;
        }

        case currentPage: {
            PhyPIBGet->setValue(pib.getCurrPage());
            break;
        }

        case SHRduration: {
            PhyPIBGet->setValue(pib.getSHR());
            break;
        }

        case symbolsPerSecond: {
            PhyPIBGet->setValue(pib.getSymbols());
            break;
        }

        default: {
            PhyPIBGet->setStatus(PhyPIB_UNSUPPORTED_ATTRIBUTE);
            break;
        }
    } // switch (attr)

    send(PhyPIBGet, "outPLME");

    return;
}

void IEEE802154Phy::sendTrxConf(phyState status)
{
    cMessage* mlmeMsg = new cMessage("PLME-SET-TRX-STATE.confirm");
    mlmeMsg->setKind(status);
    send(mlmeMsg, "outPLME");
    return;
}
