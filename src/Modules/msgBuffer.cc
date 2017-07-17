//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (fixes and port for INET 2.x)
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

#include "msgBuffer.h"
Define_Module(msgBuffer);

void msgBuffer::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == 0)
    {
        isEmpty = true;
        firstPack = true;
        start = 0;
        end = 0;
        elems = 0;

        WATCH(isEmpty);
        WATCH(firstPack);
        WATCH(start);
        WATCH(end);
        WATCH(elems);

        if (ev.isGUI())
        {
            char buf[60];
            sprintf(buf, "Size: %d pks | Holding : %u pks | firstPack : %s", buffer.size(), elems, firstPack ? "true" : "false");
            getDisplayString().setTagArg("t", 0, buf);
        }
    }
}

int msgBuffer::spacesFree()
{
    return buffer.size() - elems;
}

bool msgBuffer::purgeElem(int msduHandle)
{
    for (unsigned int i = 0; i < elems; i++)
    {
        cMessage* toPurge = check_and_cast<cMessage*>(buffer[(start + i)]);
        if (msduHandle == toPurge->getId())
        {
            buffer.remove(start + i);
        }
        return true;
    }
    return false;
}

void msgBuffer::handleMessage(cMessage* msg)
{
    if (msg->arrivedOn("inSSCS") || msg->arrivedOn("inLLC"))
    {
        if (dynamic_cast<mcpsPurgeReq*>(msg))
        {
            mcpsPurgeReq* purgeReq = check_and_cast<mcpsPurgeReq*>(msg);
            mcpsPurgeConf* purgeConf = new mcpsPurgeConf("MCPS-PURGE.confirm");

            int handle = purgeReq->getMsduHandle();
            purgeConf->setMsduHandle(handle);

            if (purgeElem(handle))
            {
                purgeConf->setStatus(purge_SUCCESS);
            }
            else
            {
                purgeConf->setStatus(purge_INVALID_HANDLE);
            }

            send(purgeConf, "outSSCS");
            delete (msg);        // fix for undisposed object message
            delete (purgeReq);   // fix for undisposed object message
        }
        else
        {
            if (firstPack)
            {
                if (msg->arrivedOn("inSSCS"))       // arrived on upperLayerInData -> forward to IEEE802154Mac.MCPS_SAP
                {
                    send(msg, "outMCPS");
                }
                else if (msg->arrivedOn("inLLC"))  // arrived on upperLayerInMngt -> forward to IEEE802154Mac.MLME_SAP
                {
                    send(msg, "outMLME");
                }

                firstPack = false;
            }
            else
            {
                add(msg);
            }
        }
    }
    else
    {
        if (msg->arrivedOn("inMLME"))
        {
            send(msg, "outLLC");
        }
        else
        {
            if (msg->getKind() == 99)
            {
                if (isEmpty)
                {
                    firstPack = true;
                }
                else
                {
                    cMessage* toMac = getElem();
                    if (toMac != NULL)
                    {
                        if (toMac->arrivedOn("inSSCS"))
                        {

                            send(toMac, "outMCPS");
                        }

                        else
                            send(toMac, "outMLME");
                    }
                }
                delete (msg);    // solving undisposed object error for Buffer-get-Elem
            }
            else
            {
                send(msg, "outSSCS");
            }
        }
    }
    if (ev.isGUI())
    {
        char buf[55];
        sprintf(buf, "Size: %d pks | Holding : %u pks | firstPack : %s", buffer.size(), elems, firstPack ? "true" : "false");
        getDisplayString().setTagArg("t", 0, buf);
    }
    return;
}

void msgBuffer::add(cMessage* elem)
{
    buffer.add(elem);
    isEmpty = false;
    end++;
    elems++;
    return;
}

cMessage* msgBuffer::getElem()
{
    if (isEmpty)
        return NULL;

    // reset if buffer is empty
    if (buffer.size() == 0)
    {
        start = 0;
        end = 0;
        elems = 0;
        isEmpty = true;
        firstPack = true;
        return NULL;
    }

    while ((dynamic_cast<cMessage*>(buffer.get(start)) == NULL) && (start < end))
    {
        start++;
    }

    if (start == end)
    {
        isEmpty = true;
        firstPack = true;
        return NULL;
    }

    cMessage* rpdu = check_and_cast<cMessage*>(buffer.get(start));
    buffer.remove(start);
    start++;
    elems--;
    return rpdu;
}

msgBuffer::~msgBuffer()
{
    buffer.clear();
}
