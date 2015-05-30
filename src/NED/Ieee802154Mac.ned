//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (ported for INET 2.x)
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

package ieee802154.src.NED;

simple IEEE802154Mac
{
    parameters:
        bool macDebug = default(false);         	// debug output switch for the IEEE 802.15.4 MAC module
        
        string macAddr = default("auto"); 	    	// MAC address as hex string (16 hex digits), or "auto" 
                                                	// "auto" values are replaced by a generated MAC address in init stage 0    
        bool isPANCoordinator = default(false); 	// either first device online chooses to be PAN coordinator or set manually together with startWithoutStartReq
        bool startWithoutStartReq = default(false); // start immediately without requiring a MLME-START.request
        string panCoordinatorName;              	// name your PAN coordinator
        
        int BeaconOrder = default (15);         	// value (0..15), default 15 = beacon disabled 
        int SuperframeOrder = default (15);     	// value (0..15), default 15 = superframe/beacons disabled

        bool isRecvGts;
        int gtsPayload;
        int defChann;
        bool ackForGts;
        bool promiscuousMode = default(false);  	// set to true to enable promicious mode (accept all packages)
        bool SecurityEnabled = default(false);
        bool isFFD = default(true);             	// full function devices yes/no

    gates:
        // LLC interface
        input MLME_SAP;
        input MCPS_SAP;

        output outMLME;
        output outMCPS;

        // PHY interface
        input inPD;
        input inPLME;

        output outPD;
        output outPLME;
}
