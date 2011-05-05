/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra
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

/** \file injector.h
 * This is the declaration for the class Injector
 */

/** \class Injector
 * This class is the main interface for the Injector library
 */

#ifndef INJECTOR_H
#define INJECTOR_H

#include "../Packet/packetBuffer.h"
#include "../Packet/packet.h"
#include "../Device/device.h"
#include <stdint.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>


class Injector
{
	public:
		//!Default constructor
		Injector();
		//!Copy time
		Injector( const Injector &n );
		//!Constructor with device name and Packet object
		Injector(const std::string &deviceName);
		//!Equality for all
		Injector& operator=( const Injector &n );
		//!Set device name
		void setDevice( const std::string &deviceName);
		//!Get device name
		std::string device() const;
		//!Inject data to the network through set device
		void inject( const Packet &p ) const;
		//!Inject data to the network
		void inject( const PacketBuffer &pb ) const;
		//!Destructor
		~Injector();

	private:
		//!Device object
		Device dev_;
		//!Session handle
		pcap_t *handle_;
};

#endif
