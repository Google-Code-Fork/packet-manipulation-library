/* *
 * * deviceLookup.h
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
//#include "packet.h"


class DevicesLookup
{
	public:
		DevicesLookup();
		pcap_if_t*& operator[](int index);		/* index specifies the index of Device in alldevs */
		pcap_if_t*& operator[](std::string name);		/* name specifies the name of Device in alldevs */
		~DevicesLookup();
		int isValid(std::string name);     /* returns 1 if device exists in the system, returns 0 otherwise) */
		void printAllDevices();

	private:
		std::string iptos(u_long in);

		// Member variables
		pcap_if_t *alldevs;
		pcap_if_t *dev;
};

#endif
