//
// Copyright (C) 2017 Michael Kirsche   
// adapted from INET 2.x IPvXTrafficGenerator Copyright (C) 2004 Andras Varga
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
// Simple traffic generator that creates IEEE 802.15.4 compatible MAC frames.
// Parameters are number of packets to send, packet sending start and stop times, 
// sendInterval (constant or random value), packet length in bytes, and the 
// destination address(es). Set it to an empty value to deactivate the traffic 
// generator. When multiple addresses are used, one address is randomly chosen 
// for each sendInterval.  
// Destination addresses should be set as EUI-64 MAC addresses 
// (for example: 0A:AA:00:00:00:00:00:01)
//
simple Ieee802154TrafficGenerator like IIeee802154TrafficModules
{
    parameters:
        bool trafficDebug = default(false);         // debug output switch for the IEEE 802.15.4 Traffic Generator
        
        double startTime @unit("s") = default(1s); // time of sending the first packet
        double stopTime @unit("s") = default(-1s);  // time of finishing sending, negative values mean forever
        volatile double sendInterval @unit("s") = default(1s); // may be a random value, e.g., exponential(1)
        
        int numPackets = default(-1); // max number of packets to generate, -1 means forever
        volatile int packetLength @unit("B") = default(20B); // packet length in bytes, max. 102 Bytes
        
        string destAddresses = default(""); // list of destination MAC addresses, separated by spaces
        
        @display("i=block/source");
        
        @signal[sentPk](type=cPacket);
        @signal[rcvdPk](type=cPacket);
        
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[sentPk](title="packets sent"; source=sentPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);
        
        @class(IEEE802154TrafficGenerator);
    gates:
        input trafficIn;
        output trafficOut;
}
