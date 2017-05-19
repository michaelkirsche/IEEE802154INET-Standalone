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

#include "PhyPIB.h"
#include "omnetpp.h"

PhyPIB::PhyPIB(unsigned short currChann, unsigned int channSupp[], unsigned char transPow, unsigned short CCAMode,
        unsigned short currPage, unsigned short SHRdur, double symbols)
{
    phyCurrentChannel = currChann;
    // Copy arrays into each other
    for (int i = 0; i < 3; i++)
    {
        phyChannelsSupported.push_back(*channSupp);
        channSupp++;
    }
    phyTransmitPower = transPow;
    phyCCAMode = CCAMode;
    phyCurrentPage = currPage;
    phySymbolsPerOctet = symbols;
    phySHRDuration = SHRdur;
    phyMaxFrameDuration = phySHRDuration + ceil((aMaxPHYPacketSize+1) * phySymbolsPerOctet);
}

unsigned short PhyPIB::getCurrChann()
{
    return phyCurrentChannel;
}

void PhyPIB::setCurrChann(unsigned short currChann)
{
    phyCurrentChannel = currChann;
    return;
}

std::vector<int> PhyPIB::getChannSupp()
{
    return phyChannelsSupported;
}

void PhyPIB::setChannSupp(std::vector<int> channSupp)
{
    phyChannelsSupported = channSupp;
    return;
}

unsigned char PhyPIB::getTransPow()
{
    return phyTransmitPower;
}

void PhyPIB::setTransPow(unsigned char setTransPow)
{
    phyTransmitPower = setTransPow;
    return;
}

unsigned short PhyPIB::getCCA()
{
    return phyCCAMode;
}

void PhyPIB::setCCA(unsigned short cca)
{
    phyCCAMode = cca;
    return;
}

unsigned short PhyPIB::getCurrPage()
{
    return phyCurrentPage;
}

void PhyPIB::setCurrPage(unsigned short currPage)
{
    phyCurrentPage = currPage;
    return;
}

unsigned short PhyPIB::getSHR()
{
    return phySHRDuration;
}

void PhyPIB::setSHR(unsigned short shr)
{
    phySHRDuration = shr;
    phyMaxFrameDuration = phySHRDuration + ceil((aMaxPHYPacketSize+1) * phySymbolsPerOctet);
    return;
}

double PhyPIB::getSymbols()
{
    return phySymbolsPerOctet;
}

void PhyPIB::setSymbols(double sym)
{
    phySymbolsPerOctet = sym;
    phyMaxFrameDuration = phySHRDuration + ceil((aMaxPHYPacketSize+1) * phySymbolsPerOctet);
    return;
}
