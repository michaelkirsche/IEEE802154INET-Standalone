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

#include <IEEE802154TrafficGenerator.h>

Define_Module(IEEE802154TrafficGenerator);

void IEEE802154TrafficGenerator::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == 0)
    {
        // initialize the debug ouput bool from NED parameter value
        trafficDebug = (hasPar("trafficDebug") ? (par("trafficDebug").boolValue()) : (false));
    }
}

