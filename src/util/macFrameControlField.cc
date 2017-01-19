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

unsigned short macFrameControlField::genFCF(frameType ft, bool secu, bool fp, bool arequ, bool pid, AddrMode dam, unsigned short fv, AddrMode sam)
{
    unsigned short fcf = 0;
    // set Frame Type
    fcf = fcf | ((ft << ftShift) & ftMask);
    // set Security Enabled
    fcf = fcf | ((secu << secuShift) & secuMask);
    // set Frame Pending
    fcf = fcf | ((fp << fpShift) & fpMask);
    // set Acknowledge Request
    fcf = fcf | ((arequ << arequShift) & arequMask);
    // set PAN ID Compression
    fcf = fcf | ((pid << pidShift) & pidMask);
    // set Destination Addressing Mode
    fcf = fcf | ((dam << damShift) & damMask);
    // set Frame Version => 0x00 to indicate a IEEE Std 802.15.4-2003 compatible frame, 0x01 to indicate an IEEE 802.15.4 frame
    fcf = fcf | ((fv << fvShift) & fvMask);
    // set Source Addressing Mode
    fcf = fcf | ((sam << samShift) & samMask);

    return fcf;
}

macFrameControlField::macFrameControlField()
{

}

macFrameControlField::~macFrameControlField()
{
    // Auto-generated destructor stub
}
