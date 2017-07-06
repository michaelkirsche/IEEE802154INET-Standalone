//
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

package ieee802154.src.NED;

//
// Module interface for modules that genrate or receive IEEE 802.15.4 MAC traffic
//
// @see ~Ieee802154TrafficSink, ~Ieee802154TrafficGenerator
//
moduleinterface IIeee802154TrafficModules
{
    @display("i=block/app");
    gates:
        input trafficIn;
        output trafficOut;
}