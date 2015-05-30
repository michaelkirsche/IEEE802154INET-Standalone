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

import inet.mobility.contract.IMobility;
import inet.base.NotificationBoard;
import inet.battery.IBattery;
import inet.applications.generic.IPvXTrafGen;	// FIXME IPvXTrafGen wants to register IP protocol -> 802.15.4 LLC dismisses this message

module IEEE802154Host
{
    parameters:
        string mobilityType = default("StationaryMobility");
        string batteryType = default("InetSimpleBattery");

        @node();
        @display("bgb=240,330;bgl=2");
        @labels(node,ieee802154-node);

    gates:
        input in;
        output out;

    submodules:
        application: IPvXTrafGen {
            @display("p=174,38");
        }

        notificationBoard: NotificationBoard {
            @display("p=60,38");
        }

        // optional battery module
        battery: <batteryType> like IBattery if batteryType != "" {
            @display("p=60,266;is=n;i=block/plug,#008080");
        }

        // optional mobility module
        mobility: <mobilityType> like IMobility if mobilityType != "" {
            @display("p=60,151");
        }

        // Network layer for IEEE 802.15.4 node
        Network: netlayer {
            @display("p=174,151;i=block/network2");
        }

        // Network interface card (PHY and MAC) for IEEE 802.15.4 node
        NIC: nic {
            @display("i=block/ifcard;p=174,266");
        }

    connections allowunconnected:
        application.ipv6Out --> Network.inApp;
        Network.outApp --> application.ipv6In;

        Network.outMCPS --> NIC.inData;
        Network.outMLME --> NIC.inMngt;

        NIC.outData --> Network.inMCPS;
        NIC.outMngt --> Network.inMLME;
}
