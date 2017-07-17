//
// Copyright (C) 2013 Matti Schnurbusch (original code)
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

#include "sscs.h"

Define_Module (sscs);

void sscs::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == 0)
    {
        // initialize the debug ouput bool from NED parameter value
        sscsDebug = (hasPar("sscsDebug") ? (par("sscsDebug").boolValue()) : (false));
    }
}

void sscs::handleMessage(cMessage *msg)
{
    sscsEV << "Got Message in SSCS ->";

    if (msg->arrivedOn("inApp"))
    {
        if (dynamic_cast<MaUnitdata*>(msg))
        {
            MaUnitdata* maRequ;
            maRequ = check_and_cast<MaUnitdata*>(msg);
            mcpsDataReq* dataMsg = new mcpsDataReq("MCPS-DATA.Request");
            // Can only set stuff we know, source address is set by MAC layer
            dataMsg->setSrcAddrMode(addrLong);
            dataMsg->setDstAddrMode(addrLong);
            dataMsg->setDstAddr(maRequ->getDstAddr());

            sscsEV << "from inApp -> MCPS-DATA.Request -- Forwarding to outMCPS \n";
            cPacket *payload = dynamic_cast<cPacket *>(msg);
            dataMsg->encapsulate(payload);
            send(msg, "outMCPS");
        }
        else
        {
            sscsEV << "from inApp -> Unknown Packet type -- Forwarding to outMCPS \n";
            send(msg, "outMCPS");
        }
    } // if (msg->arrivedOn("inApp")
    else if (msg->arrivedOn("inMCPS"))
    {

        cPacket *packet = dynamic_cast<cPacket *>(msg);
        cPacket* appMsg = packet->decapsulate();
        if (dynamic_cast<MaUnitdata *>(appMsg))
        {
            sscsEV << "from inMCPS -> application Message -- Forwarding to outApp \n";
            send(appMsg, "outApp");
        }
        else if (dynamic_cast<mcpsDataInd*>(msg))
        {
            mcpsDataInd* mcpsInd = check_and_cast<mcpsDataInd*>(msg);
            MaUnitdata* dataInd = new MaUnitdata("MA-UNITDATA.indication");

            dataInd->setSrcAddr(mcpsInd->getSrcAddr());
            dataInd->setDstAddr(mcpsInd->getDstAddr());
            dataInd->encapsulate(appMsg);

            sscsEV << "from inMCPS -> MA-UNITDATA.indication -- Forwarding to outApp \n";
            // everything else NULL
            send(dataInd, "outApp");
        }
        else
        {
            sscsEV << "Unknown Packet type -- Doing nothing at all \n";
        }
    }   // if (msg->arrivedOn("inMCPS")
}
