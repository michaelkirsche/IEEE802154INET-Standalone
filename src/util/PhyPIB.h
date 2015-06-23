//
// Copyright (C) 2013 Matti Schnurbusch (original code)
// Copyright (C) 2014 Michael Kirsche   (clean-up, adaptation for newer 802.15.4 revisions, ported for INET 2.x)
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

// TODO: Check and update for IEEE 802.15.4-2006 revision compliance

#ifndef PhyPIB_H_
#define PhyPIB_H_

#include "math.h"
#include "stdlib.h"
#include "omnetpp.h"
#include "IEEE802154Enum.h"

// This Class Represents the PHY - PAN information Base
class PhyPIB
{
    public:
        PhyPIB() {}; // Standard Ctor
        PhyPIB(unsigned short int currChann, unsigned int channSupp[], unsigned char transPow, unsigned short int CCAMode, unsigned short int currPage,
                unsigned short SHRdur, double symbols);
        virtual ~PhyPIB();

        // Getters & Setters ....
        unsigned short int getCurrChann();
        void setCurrChann(unsigned short int currChann);
        std::vector<int> getChannSupp();
        void setChannSupp(std::vector<int> channSupp);
        unsigned char getTransPow();
        void setTransPow(unsigned char setTransPow);
        unsigned short getCCA();
        void setCCA(unsigned short cca);
        unsigned short getCurrPage();
        void setCurrPage(unsigned short currPage);
        unsigned short getSHR();
        void setSHR(unsigned short shr);
        double getSymbols();
        void setSymbols(double sym);

    private:
        unsigned short int phyCurrentChannel;
        std::vector<int> phyChannelsSupported;
        unsigned char phyTransmitPower;
        unsigned short int phyCCAMode;
        unsigned short int phyCurrentPage;
        unsigned short int phyMaxFrameDuration;
        unsigned short int phySHRDuration;
        float phySymbolsPerOctet;

};

#endif /* PhyPIB_H_ */
