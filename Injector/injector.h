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
		//!Constructor with device name and Packet object
		Injector(std::string deviceName, Packet::Packet packet);
		//!Constructor with device name and PacketBuffer object
		Injector(std::string deviceName, PacketBuffer::PacketBuffer packet);
		//!Set device name
		int setDevice(std::string deviceName);
		//!Get device name
		std::string getDevice();
		//!Set Packet object
		int setPacket(Packet::Packet packet);
		//!Get packet object
		Packet::Packet getPacket();
		//!Set PacketBuffer object
		int setPacketBuffer(PacketBuffer::PacketBuffer packetBuffer);
		//!Get PacketBuffer object
		PacketBuffer::PacketBuffer getPacketBuffer();
		//!Inject data to the network through set device
		int inject();
		//!Destructor
		~Injector();
	private:
		//!Device object
		Device::Device dev;
		//!Session handle
		pcap_t *handle;
		//!Error buffer
		char errbuf[PCAP_ERRBUF_SIZE];
		//!PacketBuffer object
		PacketBuffer::PacketBuffer packetBuffer;
		//!Packet object
		Packet::Packet packet;
};

#endif
