/* *
 * * device.h
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


#ifndef DEVICE_H
#define DEVICE_H

#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
//#include "packet.h"
#include "devicesLookup.h"


class Device
{
	public:
		Device();
		void setDevice(std::string dev, int isDev);
		std::string getDevice();
		int isDevice();		/* returns 1 if it's a device, 0 if it's a pcap file */
		~Device();

	private:
		std::string dev;
		int isDev;
		static DevicesLookup deviceLookup;
};

#endif
