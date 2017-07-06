//
// Copyright (C) 2017 Michael Kirsche   
// adapted from INET 2.x IPvXTrafficSink Copyright (C) 2004 Andras Varga
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
// Consumes/discards IEEE 802.15.4 MAC packets and prints their info.
// Compatible with different IEEE 802.15.4 MAC frame types.
//
simple Ieee802154TrafficSink like IIeee802154TrafficModules
{
    parameters:
        bool trafficDebug = default(false);         // debug output switch for the IEEE 802.15.4 Traffic Sink
        
        @display("i=block/sink");
        
        @signal[rcvdPk](type=cPacket);
        
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);
        
        @class(IEEE802154TrafficSink);
    gates:
        input trafficIn;
        output trafficOut;
}
