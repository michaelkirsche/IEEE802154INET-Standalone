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
#pragma once

#ifndef MACFRAMECONTROLFIELD_H_
#define MACFRAMECONTROLFIELD_H_

#include "IEEE802154Enum.h"

class macFrameControlField
{
    public:
        macFrameControlField(); //Standard Ctor
        unsigned short genFCF(frameType ft, bool sec, bool fp, bool arequ, bool pid, AddrMode dam, unsigned short fV, AddrMode sam); // Frame....
        ~macFrameControlField();

//    private:
//        bool ackReq;  // variable not used anymore
};

#endif /* MACFRAMECONTROLFIELD_H_ */
