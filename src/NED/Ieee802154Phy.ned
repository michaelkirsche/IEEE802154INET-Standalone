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

simple IEEE802154Phy
{
    parameters:
        bool phyDebug = default(false);         // debug output switch for the IEEE 802.15.4 PHY module
        
        // PHY-PIB attributes
        // !!!!! TODO add default values    !!!!
        int currentChannel;         // initial channel to be used
        string channelsSupported;   // possible channels to be used
        int transmitPower;          // transmission power to be used
        int CCAMode;                // 3 possible CCA Modes as described in the 2006 revision of the standard
        int currentPage;            // initial page to be used
        int SHRDuration;            // Duration of the sync header
        int symbolsPerOctet;        // Number of symbols to identify 1 octet of data          

    gates:
        // MAC interfaces
        input PD_SAP;
        input PLME_SAP;

        output outPD;
        output outPLME;

        // Antenna interfaces
        input inFromRadio;
        output outToRadio;
}
