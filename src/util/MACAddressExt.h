/*
 * Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
 *
 * Copyright (C) 2013 Matti Schnurbusch (original code)
 *   - adjusted INET APIs MACAdress Class for 64 Bit values
 * Copyright (C) 2018 Michael Kirsche
 *   - restructured class, differentiate between short and long addresses more clearly
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
#pragma once

#ifndef MACADDRESS_H_
#define MACADDRESS_H_

#include <string>
#include "INETDefs.h"

#define MAC_LONG_ADDRESS_SIZE   8
#define MAC_SHORT_ADDRESS_SIZE  2
#define MAC_LONG_ADDRESS_MASK   0xffffffffffffffffUL    // UL to indicate a "unsigned long" hexadecimal constant
#define MAC_ADDRESS_SHORT_MASK  0xffffUL

/**
 * Stores an IEEE 802.15.4 Extended MAC address (8 octets = 64-bits) and a (16-bit) short address.
 */
class MACAddressExt
{
    private:
        uint64 longAddr; // 8*8=64bit address
        unsigned short shortAddr; // 16bit short address, value of 0xffff (65.535) indicates the broadcast address
        //static unsigned int autoAddressCtr; // counter for generateAutoAddress()

    public:

        /** The unspecified MAC address, 00:00:00:00:00:00:00:00 */
        static const MACAddressExt UNSPECIFIED_ADDRESS;

        /** The long broadcast MAC address, FF:FF:FF:FF:FF:FF:FF:FF */
        static const MACAddressExt BROADCAST_LONG_ADDRESS;

        /** The special multicast PAUSE long MAC address, 01:80:C2:00:00:01 */
        static const MACAddressExt MULTICAST_PAUSE_LONG_ADDRESS;

        /** The short broadcast MAC address, FF:FF */
        static const MACAddressExt BROADCAST_SHORT_ADDRESS;

        /**
         * Default constructor initializes short and long addresses to zero.
         */
        MACAddressExt()
        {
            longAddr = 0;
            shortAddr = 0;
        }

        /**
         * Initializes the long address from a 64-bit argument
         */
        explicit MACAddressExt(uint64 longBits)
        {
            longAddr = longBits;
            shortAddr = 0;
        }

        /**
         * Constructor which accepts a hex string (12 hex digits, may also contain spaces, hyphens and colons)
         */
        explicit MACAddressExt(const char *longHexStr)
        {
            setLongAddress(longHexStr);
            shortAddr = 0;
        }

        /**
         * Constructor which initializes long and short address from 64-bit and 16-bit arguments
         */
        explicit MACAddressExt(uint64 longBits, unsigned short shortBits)
        {
            longAddr = longBits;
            shortAddr = shortBits;
        }

        /**
         * Constructor which initializes long longAddr from a hex string and short longAddr from 16-bit argument
         */
        explicit MACAddressExt(const char *longHexStr, unsigned short shortBits)
        {
            setLongAddress(longHexStr);
            shortAddr = shortBits;
        }

        /**
         * Copy constructor.
         */
        MACAddressExt(const MACAddressExt& other)
        {
            longAddr = other.longAddr;
            shortAddr = other.shortAddr;
        }

        /**
         * Assignment.
         */
        MACAddressExt& operator=(const MACAddressExt& other)
        {
            longAddr = other.longAddr;
            shortAddr = other.shortAddr;
            return *this;
        }

        /**
         * Returns the long address size in bytes, that is, 8.
         */
        static const unsigned short getLongAddressSize()
        {
            return MAC_LONG_ADDRESS_SIZE;
        }

        /**
         * Returns the short address size in bytes, that is, 2.
         */
        static const unsigned short getShortAddressSize()
        {
            return MAC_SHORT_ADDRESS_SIZE;
        }

        /**
         * Returns the kth byte of the 64-bit long address.
         */
        unsigned char getLongAddressByte(unsigned int k) const;

        /**
         * Sets the kth byte of the 64-bit long address.
         */
        void setLongAddressByte(unsigned int k, unsigned char addrbyte);

        /**
         * Sets the complete 16-bit short address
         */
        void setShortAddr(unsigned short val)
        {
            shortAddr = val;
        }

        /**
         * generating the short address --> last 16 bit are short address
         */
        void genShortAddr()
        {
            shortAddr = longAddr & (MAC_ADDRESS_SHORT_MASK);
        }

        /**
         * Returns the complete 16-bit short address
         */
        unsigned short getShortAddr() const
        {
            return shortAddr;
        }

        /**
         * Sets the longAddress and returns true if the syntax of the string is correct. (See setLongAddress() for the syntax.)
         */
        bool tryParseLongAddr(const char *hexstr);

        /**
         * Converts longAddr value from hex string (16 hex digits, may also contain spaces, hyphens and colons)
         */
        void setLongAddress(const char *hexstr);

        /**
         * Copies the address to the given pointer (array of 8 unsigned chars).
         */
        void getLongAddressBytes(unsigned char *addrbytes) const;
        void getLongAddressBytes(char *addrbytes) const
        {
            getLongAddressBytes((unsigned char *) addrbytes);
        }

        /**
         * Sets long address bytes. The argument should point to an array of 8 unsigned chars.
         */
        void setLongAddressBytes(unsigned char *addrbytes);
        void setLongAddressBytes(char *addrbytes)
        {
            setLongAddressBytes((unsigned char *) addrbytes);
        }

        /**
         * Sets the longAddr to the broadcast 64-bit long address (hex FF:FF:FF:FF:FF:FF:FF:FF).
         */
        void setLongBroadcast()
        {
            longAddr = MAC_LONG_ADDRESS_MASK;
        }

        /**
         * Sets the shortAddr to the broadcast 16-bit short address (hex FF:FF).
         */
        void setShortBroadcast()
        {
            shortAddr = MAC_ADDRESS_SHORT_MASK;
        }

        /**
         * Returns true if the current 64-bit longAddr is the broadcast long address (hex FF:FF:FF:FF:FF:FF:FF:FF).
         */
        bool isLongBroadcast() const
        {
            return longAddr == MAC_LONG_ADDRESS_MASK;
        }

        /**
         * Returns true if the current 64-bit longAddr is a multicast logical address (first byte's LSB is 1).
         */
        bool isLongMulticast() const
        {
            return getLongAddressByte(0) & 0x01;
        }

        /**
         * Returns true if all longAddr bytes are zero.
         */
        bool isLongUnspecified() const
        {
            return longAddr == 0;
        }

        /**
         * Returns true if the current 16-bit shortAddr is the broadcast short address (hex FF:FF).
         */
        bool isShortBroadcast() const
        {
            return shortAddr == MAC_ADDRESS_SHORT_MASK;
        }

        /**
         * Returns true if all shortAddr bytes are zero.
         */
        bool isShortUnspecified() const
        {
            return longAddr == 0;
        }

        /**
         * Converts longAddr to a hex string.
         */
        std::string str() const;

        /**
         * Converts address to 64 bits integer.
         */
        uint64 getInt() const
        {
            return longAddr;
        }

        /**
         * Returns true if the two 64-bit long addresses are equal.
         */
        bool longEquals(const MACAddressExt& other) const
        {
            return longAddr == other.longAddr;
        }

        /**
         * Returns true if the two 16-bit short addresses are equal.
         */
        bool shortEquals(const MACAddressExt& other) const
        {
            return shortAddr == other.shortAddr;
        }

        // TODO need to be either restructured or completely substituted by shortEquals and longEquals !!!
//        /**
//         * Returns true if the two addresses are equal.
//         */
//        bool operator==(const MACAddressExt& other) const
//        {
//            return longAddress == other.longAddress;
//        }
//
//        /**
//         * Returns true if the two addresses are not equal.
//         */
//        bool operator!=(const MACAddressExt& other) const
//        {
//            return longAddr != other.longAddr;
//        }

        // TODO remove if not needed
//        /**
//         * Returns -1, 0 or 1 as result of comparison of 2 addresses.
//         */
//        int compareTo(const MACAddressExt& other) const;

        // TODO remove if not needed
//        bool operator<(const MACAddressExt& other) const
//        {
//            return longAddr < other.longAddr;
//        }
//
//        bool operator>(const MACAddressExt& other) const
//        {
//            return longAddr > other.longAddr;
//        }

        /**
         * Generates a unique 64-bit MAC long address which begins with 0a:aa and ends in a unique suffix
         * based on the node index
         */
        static MACAddressExt generateMacAddressWithNodeIndex(unsigned int index);

};

inline std::ostream& operator<<(std::ostream& os, const MACAddressExt& mac)
{
    return os << mac.str();
}

#endif
