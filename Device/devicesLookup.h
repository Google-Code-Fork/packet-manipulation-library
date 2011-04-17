/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2008  Jeff Scaparra, Gaurav Yadav, Andrie Tanusetiawan
 *
 * This file is a part of PacMan.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/***********************************************************************
 * Last Edited:
 * Apr 6, 2011 --- Jeff Scaparra
 *
 *
 * ********************************************************************/

/** \file devicesLookup.h
 * This is the declaration for the class DevicesLookup
 */

/** \class DevicesLookup
 * This class is the main interface for the DevicesLookup library
 */

#ifndef DEVICELOOKUP_H
#define DEVICELOOKUP_H

#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>


class DevicesLookup
{
	public:
		//!Default constructor
		DevicesLookup();
		//!Index specifies the index of Device in alldevs
		pcap_if_t* operator[](const int &index);
		//!name specifies the name of Device in alldevs
		pcap_if_t* operator[](const std::string &name);
		//!Destructor
		~DevicesLookup();
		//!Returns true if device exists in the system, false otherwise
		bool isValid(const std::string &name) const;
		//!Prints all existing devices to the screen
		void printAllDevices() const;
		//!Returns true if device is a loopback device
		bool isLoopback(const std::string &device) const;
		//!Returns the address of the device
		std::string address(const std::string &device) const;
		//!Returns the address family of the device
		std::string addressFamily( const std::string &device) const;
		//!Returns the netmask of the device
		std::string netmask( const std::string &device );

	private:
		//!Converts IP to string
		std::string iptos(const uint32_t &in) const;

		//!Stores all devices
		pcap_if_t *alldevs_;
};

#endif
