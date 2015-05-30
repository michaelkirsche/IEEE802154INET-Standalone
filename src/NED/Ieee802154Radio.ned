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
import inet.linklayer.radio.IRadio;


simple Ieee802154Radio like IRadio
{
    parameters:
        @class(IEEE802154Radio);
        @display("i=block/wrxtx");
        
        bool radioDebug = default(false);         // debug output switch for the IEEE 802.15.4 Radio

        int ccaMode = default(1); // the 3 possible CCA Modes
        double snirThreshold @unit("dB") = default(4dB); // if signal-noise ratio is below this threshold, frame is considered noise (in dB)
        int headerLengthBits @unit(b) = default(0bit); // length of physical layer framing (preamble, etc)
        double bandwidth @unit(Hz) = default(2.4GHz); // signal bandwidth, used for bit error calculation
        string modulation = default("BPSK");    // "BPSK", "16-QAM", "256-QAM" or "null"; selects bit error calculation method
        								        // Its only for BER calculation
        int channelNumber = default(0); // channel identifier this radio listens. Works only with simplified management module. Otherwise it scans all the channels as specified
        double carrierFrequency @unit(Hz) = default(2.4GHz);
        double bitrate @unit(bps);
        double transmitterPower @unit(mW) = default(10mW);      // power used for transmission of messages (in mW)
        double thermalNoise @unit("dBm") = default(-110dBm);    // base noise level (dBm)
        double sensitivity @unit("dBm") = default(-85dBm);      // received signals with power below sensitivity are ignored

		double maxDistance @unit(m) = default(-1m); 	// if the maxDistance is bigger of 0 the sensitivity is adjusted to a maximun reception to this value
        bool setReceptionThreshold = default(false);
        double receptionThreshold @unit("dBm") = default(-110dBm);
        double maxDistantReceptionThreshold @unit(m) = default(-1m);

        string radioModel;  // the radio model implementing the IRadioModel interface (C++). e.g. GenericRadioModel, Ieee80211RadioModel

        xml SensitivityTable = default(xml("<NoSensitivityTable> </NoSensitivityTable>"));

        string NoiseGenerator = default("");
        // generic FreeSpace model parameters
        double pathLossAlpha = default(2);  // used by the path loss calculation
        double TransmissionAntennaGainIndB @unit("dB") = default(0dB);  // Transmission Antenna Gain
        double ReceiveAntennaGainIndB @unit("dB") = default(0dB);       // Receive Antenna Gain
        double SystemLossFactor @unit("dB") = default(0dB);             // System Loss of Hardware
        // two ray model paramaeters
        double TransmiterAntennaHigh @unit(m) = default(1m);            // Transmitter Antenna High
        double ReceiverAntennaHigh @unit(m) = default(1m);              // Receiver Antenna High
        // LogNormalShadowingModel
        double sigma = default(1);
        // NakagamiModel
        double nak_m = default(1);
        // RiceModel
        double K @unit("dB") = default(8dB);
        // SUIModel
        string terrain = default("TerrainB");

         // battery module parameters (if any of them is negative, the battery module is disabled)
         // Fill if you wish that the Battery Module should simulate power consumption
        double usage_IEEE802154Radio_idle @unit(mA) = default(-1mA); // disable battery registration
        double usage_IEEE802154Radio_recv @unit(mA) = default(-1mA); // disable battery registration
        double usage_IEEE802154Radio_sleep @unit(mA) = default(-1mA); // disable battery registration
        double usage_IEEE802154Radio_send @unit(mA) = default(-1mA); // disable battery registration
        
         // misc
        bool drawCoverage = default(true);  // draw the coverage area in Tkenv
        int refreshCoverageInterval @unit(s) = default(0s);  // update period in simulation time for coverage redraw

        @signal[bitrate](type="double"; unit=bps); // current transmit bitrate
        @signal[radioState](type=long);  // enum
        @signal[channelNumber](type=long);
        @signal[lossRate](type="double"); // 0..1; percentage of frames received incorrectly in the last period
        @statistic[bitrate](title="tx bitrate"; record=min,max,timeavg,vector; interpolationmode=sample-hold; unit=bps);
        @statistic[radioState](title="radio state (enum)"; record=count,vector; interpolationmode=sample-hold);
        @statistic[channelNumber](title="channel number"; record=histogram,vector; interpolationmode=sample-hold);
        @statistic[lossRate](title="packet loss rate"; record=min,max,timeavg,vector; interpolationmode=backward-sample-hold);

    gates:
        input upperLayerIn @labels(PhyControlInfo/down); // from higher layer protocol (MAC)
        output upperLayerOut @labels(PhyControlInfo/up); // to higher layer protocol (MAC)
        input radioIn @labels(AirFrame); // to receive frames (AirFrame) on the radio channel
}
