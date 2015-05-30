//
// Copyright (C) 2013 Matti Schnurbusch
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

#ifndef MSGBUFFER_H_
#define MSGBUFFER_H_

#include "omnetpp.h"
#include "IEEE802154Enum.h"
#include "mcpsData_m.h"

class msgBuffer : public cSimpleModule
{
    public:
        msgBuffer(){}; // std Ctor
        explicit msgBuffer(int size);
        ~msgBuffer();

    protected:
        void initialize();
        void handleMessage(cMessage* msg);
        int spacesFree();
        void add(cMessage* elem);
        bool purgeElem(int msduHandle);
        void delElem();
        cMessage* getElem();

    private:
        cArray buffer; // Message buffer
        unsigned int start; // buffer start position
        unsigned int end; // buffer end position
        bool isEmpty; // buffer status
        unsigned int elems;
        bool firstPack;
};

#endif /* MSGBUFFER_H_ */
