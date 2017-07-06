//
// Copyright (C) 2004 Andras Varga      (IPvXTrafGen in INET 2.x)
// Copyright (C) 2017 Michael Kirsche
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
#pragma once

#ifndef IEEE802154TRAFFICGENERATOR_H_
#define IEEE802154TRAFFICGENERATOR_H_

#include <omnetpp.h>
#include <stdio.h>
#include <stdlib.h>

#include "MPDU_m.h"
#include "mcpsData_m.h"

#define trafficEV (ev.isDisabled()||!trafficDebug) ? EV : EV << "[802154_TRAFFIC]: " // switchable debug output

class IEEE802154TrafficGenerator : public cSimpleModule
{
    public:
        IEEE802154TrafficGenerator();
        virtual ~IEEE802154TrafficGenerator();
};

#endif /* IEEE802154TRAFFICGENERATOR_H_ */
