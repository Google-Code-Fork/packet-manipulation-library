/* *
 * * injector.h
 * *    Pcap Project
 * *
 * * This program is free software: you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation, either version 3 of the License, or
 * * (at your option) any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */


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
		Injector();
		Injector(std::string deviceName, Packet::Packet packet);
		Injector(std::string deviceName, PacketBuffer::PacketBuffer packet);
		int setDevice(std::string deviceName);
		std::string getDevice();
		int setPacket(Packet::Packet packet);
		Packet::Packet getPacket();
		int setPacketBuffer(PacketBuffer::PacketBuffer packetBuffer);
		PacketBuffer::PacketBuffer getPacketBuffer();
		int inject();
		~Injector();
	private:
		Device::Device dev;
		pcap_t *handle;		/* session handle */
		char errbuf[PCAP_ERRBUF_SIZE];
		PacketBuffer::PacketBuffer packetBuffer;
		Packet::Packet packet;
};

#endif
