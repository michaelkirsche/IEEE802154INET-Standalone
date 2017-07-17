/*
 * Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
 *
 * Copyright (C) 2013 Matti Schnurbusch (original code)
 *   - adjusted INET APIs MACAdress Class for 64 Bit values
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <ctype.h>
#include "MACAddressExt.h"
#include "InterfaceToken.h"

const MACAddressExt MACAddressExt::UNSPECIFIED_ADDRESS;
const MACAddressExt MACAddressExt::BROADCAST_ADDRESS("FF:FF:FF:FF:FF:FF:FF:FF");
const MACAddressExt MACAddressExt::MULTICAST_PAUSE_ADDRESS("01:80:C2:00:00:00:00:01");

unsigned char MACAddressExt::getAddressByte(unsigned int k) const
{
    if (k >= MAC_ADDRESS_SIZE)
    {
        throw cRuntimeError("Array of size 8 indexed with %d", k);
    }
    int offset = (MAC_ADDRESS_SIZE - k - 1) * 8;
    return 0xff & (address >> offset);
}

void MACAddressExt::setAddressByte(unsigned int k, unsigned char addrbyte)
{
    if (k >= MAC_ADDRESS_SIZE)
    {
        throw cRuntimeError("Array of size 8 indexed with %d", k);
    }
    int offset = (MAC_ADDRESS_SIZE - k - 1) * 8;
    address = (address & (~(((uint64) 0xff) << offset))) | (((uint64) addrbyte) << offset);
}

bool MACAddressExt::tryParse(const char *hexstr)
{
    if (!hexstr)
    {
        return false;
    }

    // check syntax
    int numHexDigits = 0;
    for (const char *s = hexstr; *s; s++)
    {
        if (isxdigit(*s))
        {
            numHexDigits++;
        }
        else if (*s != ' ' && *s != ':' && *s != '-')
        {
            return false; // wrong syntax
        }
    }
    if (numHexDigits != 2 * MAC_ADDRESS_SIZE)
    {
        return false;
    }

    // Converts hex string into the address
    // if hex string is shorter, address is filled with zeros;
    // Non-hex characters are discarded before conversion.
    address = 0; // clear top 16 bits too that setAddressByte() calls skip
    int k = 0;
    const char *s = hexstr;
    for (int pos = 0; pos < MAC_ADDRESS_SIZE; pos++)
    {
        if (!s || !*s)
        {
            setAddressByte(pos, 0);
        }
        else
        {
            while (*s && !isxdigit(*s))
            {
                s++;
            }
            if (!*s)
            {
                setAddressByte(pos, 0);
                continue;
            }
            unsigned char d = isdigit(*s) ? (*s - '0') : islower(*s) ? (*s - 'a' + 10) : (*s - 'A' + 10);
            d = d << 4;
            s++;

            while (*s && !isxdigit(*s))
            {
                s++;
            }
            if (!*s)
            {
                setAddressByte(pos, 0);
                continue;
            }
            d += isdigit(*s) ? (*s - '0') : islower(*s) ? (*s - 'a' + 10) : (*s - 'A' + 10);
            s++;

            setAddressByte(pos, d);
            k++;
        }
    }
    return true;
}

void MACAddressExt::setAddress(const char *hexstr)
{
    if (!tryParse(hexstr))
    {
        throw cRuntimeError("MACAddress: wrong address syntax '%s': 16 hex digits expected, with optional embedded spaces, hyphens or colons", hexstr);
    }
}

void MACAddressExt::getAddressBytes(unsigned char *addrbytes) const
{
    for (int i = 0; i < MAC_ADDRESS_SIZE; i++)
    {
        addrbytes[i] = getAddressByte(i);
    }
}

void MACAddressExt::setAddressBytes(unsigned char *addrbytes)
{
    address = 0; // clear top 16 bits too that setAddressByte() calls skip
    for (int i = 0; i < MAC_ADDRESS_SIZE; i++)
    {
        setAddressByte(i, addrbytes[i]);
    }
}

// New (from 802.11 MACAddress.h) definition of str
std::string MACAddressExt::str() const
{
    char buf[24];
    char *s = buf;
    for (int i = 0; i < MAC_ADDRESS_SIZE; i++, s += 3)
    {
        sprintf(s, "%2.2X:", getAddressByte(i));
    }
    *(s - 1) = '\0';
    return std::string(buf);
}

int MACAddressExt::compareTo(const MACAddressExt& other) const
{
    // note: "return address-other.address" is not OK because 64-bit result does not fit into the return type
    return (address < other.address) ? -1 : (address == other.address) ? 0 : 1;
}

MACAddressExt MACAddressExt::generateMacAddressWithNodeIndex(unsigned int index)
{
    uint64_t genMacAddr = 0x0AAA000000000000 + (index & MAC_ADDRESS_MASK);
    MACAddressExt addr(genMacAddr);
    return addr;
}
