//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2015 Michael Kirsche   (fixes, ported for INET 2.x)
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

simple llc
{
    parameters:
        bool llcDebug = default(false);         // debug output switch for the IEEE 802.15.4 LLC module
        
        bool convertMode = default(false);      // set to true if app layer is not compatible to 802.15.4 MAC entity (does not use 802.15.4 service primitives)
        
        int TXoption = default(0);
        // For b0: 1 = acknowledged transmission, 0 = unacknowledged transmission.
        // For b1: 1 = GTS transmission, 0 = CAP transmission (for a beacon-enabled PAN).
        // For b2: 1 = indirect transmission, 0 = direct transmission.
        // --> For a nonbeacon-enabled PAN, bit b1 should always be set to 0!
        // b2 b1 b0 | val
        // --------------
        //  0  0  0 | 0 --> unacknowledged CAP direct transmission
        //  0  0  1 | 1 --> acknowledged CAP direct transmission
        //  0  1  0 | 2 --> unacknowledged GTS direct transmission
        //  0  1  1 | 3 --> acknowledged GTS direct transmission
        //  1  0  0 | 4 --> unacknowledged CAP indirect transmission
        //  1  0  1 | 5 --> acknowledged CAP indirect transmission
        //  1  1  0 | 6 --> unacknowledged GTS indirect transmission
        //  1  1  1 | 7 --> acknowledged GTS indirect transmission
        
        // Variables for startup message
        int PANId = default(0);
        int LogicalChannel = default(0);
        int ChannelPage = default(0);
        int StartTime = default(0);
        int BeaconOrder = default(0);
        int SuperframeOrder = default(0);
        bool BatteryLifeExtension = default(false);
        bool CoordRealignment = default(false);

        double PollFrequency = default(0.5);	// if indirect, choose this wisely (simtime)
        // Initital Scan variables
        int ScanChannels = default(0);  		// 27 bit choose each bit for the channel to be scanned - whereas 1=scan and 0=don't scan -> convert your 27bits into an integer value
        double ScanDuration = default(0.2);		// [aBaseSuperframeDuration * (2^n + 1)] this is n so - value is Symbols
        int ScanPage = default(0);				// initial channel page for the scan (between 0 and 31, while 3-31 are not used (see 2006-Specs Sec. 6.1.2.2)
        
        int ScanType = default(1);				// indicates type of scan, can be:
        										// 0x00 = ED scan (optional for RFD)
												// 0x01 = active scan (optional for RFD)
												// 0x02 = passive scan
												// 0x03 = orphan scan.

    gates:
        // Application interface
        input inApp;
        output outApp;

        // MAC interface
        input inData;
        input inMngt;

        output outData;
        output outMngt;
}