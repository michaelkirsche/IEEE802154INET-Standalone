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

// IEEE 802.15.4 Network Interface Card (NIC) 
// essentially the PHY and MAC layer inside a compound module
module nic
{
    parameters:
        @display("bgb=156,319");

    gates:
        input inData;
        input inMngt;

        output outData;
        output outMngt;

    submodules:
        MAC: Mac {
            @display("p=80,59;i=block/layer");
        }

        PHY: IEEE802154Phy {
            @display("p=80,162;i=block/mac");
        }

        radioInterface: Ieee802154Radio {
            @display("p=80,264");
        }

    connections allowunconnected:
        inData --> MAC.upperLayerInData;
        inMngt --> MAC.upperLayerInMngt;

        MAC.upperLayerOutData --> outData;
        MAC.upperLayerOutMngt --> outMngt;

        PHY.outPD --> MAC.lowerLayerInData;
        PHY.outPLME --> MAC.lowerLayerInMngt;

        MAC.lowerLayerOutData --> PHY.PD_SAP;
        MAC.lowerLayerOutMngt --> PHY.PLME_SAP;

        PHY.outToRadio --> radioInterface.upperLayerIn;
        radioInterface.upperLayerOut --> PHY.inFromRadio;
}
