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

// IEEE 802.15.4 Medium Access Control Layer 
// Essentially the 802.15.4 MAC and a ring buffer
module Mac
{
    parameters:
        @display("bgb=144,206");

    gates:
        input upperLayerInData;
        input upperLayerInMngt;

        input lowerLayerInData;
        input lowerLayerInMngt;

        output upperLayerOutData;
        output upperLayerOutMngt;

        output lowerLayerOutData;
        output lowerLayerOutMngt;

    submodules:
        IEEE802154Mac: IEEE802154Mac {
            @display("p=74,139;i=old/prot1");
        }

        Buffer: msgBuffer {
            @display("p=74,58;i=block/buffer");
        }

    connections allowunconnected:
        upperLayerInData --> Buffer.inSSCS;
        upperLayerInMngt --> Buffer.inLLC;

        Buffer.outSSCS --> upperLayerOutData;
        Buffer.outLLC --> upperLayerOutMngt;

        Buffer.outMCPS --> IEEE802154Mac.MCPS_SAP;
        Buffer.outMLME --> IEEE802154Mac.MLME_SAP;

        IEEE802154Mac.outMCPS --> Buffer.inMCPS;
        IEEE802154Mac.outMLME --> Buffer.inMLME;

        IEEE802154Mac.outPLME --> lowerLayerOutMngt;
        IEEE802154Mac.outPD --> lowerLayerOutData;

        lowerLayerInMngt --> IEEE802154Mac.inPLME;
        lowerLayerInData --> IEEE802154Mac.inPD;
}
