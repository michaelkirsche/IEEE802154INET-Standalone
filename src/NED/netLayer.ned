//
// Copyright (C) 2013 Matti Schnurbusch (original code)
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

// IEEE 802.15.4 Network Layer 
// Standard LLC and Service Specific Convergence Sublayer
module netlayer
{
    parameters:
        @display("bgb=216,119");

    gates:
        input inApp;
        output outApp;

        input inMCPS;
        input inMLME;

        output outMCPS;
        output outMLME;


    submodules:
        // for completeness
        sscs: sscs {
            @display("p=159,59;i=block/classifier");
        }

        // wrapping first 802.15.4 frames for MAC layer
        stdLLC: llc {
            @display("i=block/join;p=55,59;i2=status/red");
        }

    connections allowunconnected:
        inApp --> stdLLC.inApp;
        stdLLC.outApp --> outApp;

        inMCPS --> stdLLC.inData;
        inMLME --> stdLLC.inMngt;

        stdLLC.outData --> outMCPS;
        stdLLC.outMngt --> outMLME;
}
