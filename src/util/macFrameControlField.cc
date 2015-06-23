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

#include "macFrameControlField.h"
#include "omnetpp.h"

unsigned short macFrameControlField::genFCF(frameType ft, bool sec, bool fp, bool arequ, bool pid, AddrMode dam, unsigned short fV, AddrMode sam)
{
    unsigned short fc = 0;

    fc = (ft << ftShift) & ftMask;

    if (sec)
        fc = (fc | (1 << secShift)) & secMask;

    if (fp)
        fc = (fc | (1 << fpShift)) & fpMask;

    if (arequ)
        fc = (fc | (1 << arequShift)) & arequMask;

    if (pid)
        fc = (fc | (1 << pidShift)) & pidMask;

    if (dam != none)
        fc = (fc | (dam << damShift)) & damMask;

    // fV(ersion) Should always be 001 for 802.15.4-2003 and 2006
    fc = (fc | (fV << fvShift)) & fvMask;

    fc = fc | sam;

    return fc;
}

macFrameControlField::macFrameControlField()
{

}

macFrameControlField::~macFrameControlField()
{
    // Auto-generated destructor stub
}
