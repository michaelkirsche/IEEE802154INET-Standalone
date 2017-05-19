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
#pragma once

#ifndef MACADDRESS_H_
#define MACADDRESS_H_

#include <string>
#include "INETDefs.h"

#define MAC_ADDRESS_SIZE 8
#define MAC_ADDRESS_MASK 0xffffffffffffffffUL    // UL to indicate a "unsigned long" hexadecimal constant
#define MAC_ADDRESS_SHORT_MASK 0xFFFFUL

// Extended version of INET API's MACAddress Class

/**
 * Stores an IEEE 802.15.4 Extended MAC address (8 octets = 64 bits) and a (corresponding 16bit) shortAddress.
 */
class MACAddressExt
{
    private:
        uint64 address; // 8*8=64bit address
        unsigned short shortAddr; // 16bit short address, value of 0xffff (65.535) indicates that the device does not have a short address
        static unsigned int autoAddressCtr; // counter for generateAutoAddress()

    public:

        /** The unspecified MAC address, 00:00:00:00:00:00:00:00 */
        static const MACAddressExt UNSPECIFIED_ADDRESS;

        /** The broadcast MAC address, FF:FF:FF:FF:FF:FF:FF:FF */
        static const MACAddressExt BROADCAST_ADDRESS;

        /** The special multicast PAUSE MAC address, 01:80:C2:00:00:01 */
        static const MACAddressExt MULTICAST_PAUSE_ADDRESS;

        /**
         * Default constructor initializes address bytes to zero.
         */
        MACAddressExt()
        {
            address = 0;
            shortAddr = 65535;          // FIXME what should be the correct initialization value for shortAddr?
        }

        /**
         * Initializes the address from the the 64-bit argument
         */
        explicit MACAddressExt(uint64 bits)
        {
            address = bits;
            shortAddr = 65535;          // FIXME what should be the correct initialization value for shortAddr?
        }

        /**
         * Constructor which accepts a hex string (12 hex digits, may also contain spaces, hyphens and colons)
         */
        explicit MACAddressExt(const char *hexstr)
        {
            setAddress(hexstr);
            shortAddr = 65535;          // FIXME what should be the correct initialization value for shortAddr?
        }

        /**
         * Copy constructor.
         */
        MACAddressExt(const MACAddressExt& other)
        {
            address = other.address;
            shortAddr = other.shortAddr;
        }

        /**
         * Assignment.
         */
        MACAddressExt& operator=(const MACAddressExt& other)
        {
            address = other.address;
            shortAddr = other.shortAddr;
            return *this;
        }

        /**
         * Returns the address size in bytes, that is, 8.
         */
        static const unsigned int getAddressSize()
        {
            return MAC_ADDRESS_SIZE;
        }

        /**
         * Returns the kth byte of the address.
         */
        unsigned char getAddressByte(unsigned int k) const;

        /**
         * Sets the kth byte of the address.
         */
        void setAddressByte(unsigned int k, unsigned char addrbyte);

        void setShortAddr(unsigned short val)
        {
            shortAddr = val;
        }

        /**
         * generating the short address --> last 16 bit are short address
         */
        void genShortAddr()
        {
            shortAddr = address & (MAC_ADDRESS_SHORT_MASK);
        }

        unsigned short getShortAddr() const
        {
            return shortAddr;
        }

        /**
         * Sets the address and returns true if the syntax of the string is correct. (See setAddress() for the syntax.)
         */
        bool tryParse(const char *hexstr);

        /**
         * Converts address value from hex string (16 hex digits, may also contain spaces, hyphens and colons)
         */
        void setAddress(const char *hexstr);

        /**
         * Copies the address to the given pointer (array of 8 unsigned chars).
         */
        void getAddressBytes(unsigned char *addrbytes) const;
        void getAddressBytes(char *addrbytes) const
        {
            getAddressBytes((unsigned char *) addrbytes);
        }

        /**
         * Sets address bytes. The argument should point to an array of 8 unsigned chars.
         */
        void setAddressBytes(unsigned char *addrbytes);
        void setAddressBytes(char *addrbytes)
        {
            setAddressBytes((unsigned char *) addrbytes);
        }

        /**
         * Sets the address to the broadcast address (hex FF:FF:FF:FF:FF:FF:FF:FF).
         */
        void setBroadcast()
        {
            address = MAC_ADDRESS_MASK;
        }

        /**
         * Returns true if this is the broadcast address (hex FF:FF:FF:FF:FF:FF:FF:FF).
         */
        bool isBroadcast() const
        {
            return address == MAC_ADDRESS_MASK;
        }

        /**
         * Returns true if this is a multicast logical address (first byte's LSB is 1).
         */
        bool isMulticast() const
        {
            return getAddressByte(0) & 0x01;
        }
        ;

        /**
         * Returns true if all address bytes are zero.
         */
        bool isUnspecified() const
        {
            return address == 0;
        }

        /**
         * Converts address to a hex string.
         */
        std::string str() const;

        /**
         * Converts address to 64 bits integer.
         */
        uint64 getInt() const
        {
            return address;
        }

        /**
         * Returns true if the two addresses are equal.
         */
        bool equals(const MACAddressExt& other) const
        {
            return address == other.address;
        }

        /**
         * Returns true if the two addresses are equal.
         */
        bool operator==(const MACAddressExt& other) const
        {
            return address == other.address;
        }

        /**
         * Returns true if the two addresses are not equal.
         */
        bool operator!=(const MACAddressExt& other) const
        {
            return address != other.address;
        }

        /**
         * Returns -1, 0 or 1 as result of comparison of 2 addresses.
         */
        int compareTo(const MACAddressExt& other) const;

        /**
         * Generates a unique MAC address which begins with 0a:aa and ends in a unique suffix
         * based on the node index
         */
        static MACAddressExt generateMacAddressWithNodeIndex(unsigned int index);

        bool operator<(const MACAddressExt& other) const
        {
            return address < other.address;
        }

        bool operator>(const MACAddressExt& other) const
        {
            return address > other.address;
        }

};

inline std::ostream& operator<<(std::ostream& os, const MACAddressExt& mac)
{
    return os << mac.str();
}

#endif
