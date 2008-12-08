/* *
 * * devicesLookup.h
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


#include "devicesLookup.h"


DevicesLookup::DevicesLookup()
{
	char errbuf[PCAP_ERRBUF_SIZE+1];
	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
		exit(1);
	}
}

pcap_if_t*& DevicesLookup::operator[](int index)
{
	dev = alldevs;
	int count = 0;		/* device traversal index */

	while(count != index && dev != NULL)
	{
		dev = dev->next;
		count++;
	}

	return dev;
}

pcap_if_t*& DevicesLookup::operator[](std::string name)
{
	dev = alldevs;

	for(dev = alldevs; dev != NULL && !strcmp(dev->name, name.c_str()); dev = dev->next)
	std::cout << "Comparing device names: " << dev->name;

	return dev;
}

DevicesLookup::~DevicesLookup()
{
	std::cout << "Freeing the device list..." << std::endl;
	pcap_freealldevs(alldevs);		/* Free the device list */
}

int DevicesLookup::isValid(std::string name)
{
        return (DevicesLookup::operator[](name) != NULL);
}

void DevicesLookup::printAllDevices()
{
	/* Scan the list printing every entry */
	for(pcap_if_t* dev=alldevs;dev != NULL;dev=dev->next)
	{
		/* Name */
		std::cout << dev->name << std::endl;
		/* Description */
		if (dev->description)
		{
			std::cout << "\tDescription: " << dev->description << std::endl;
		}
		/* Loopback Address*/
		std::cout << "\tLoopback: " << ((dev->flags & PCAP_IF_LOOPBACK)?"yes":"no") << std::endl;
		/* IP addresses */
		for(pcap_addr_t *addrEl=dev->addresses;addrEl != NULL;addrEl=addrEl->next)
		{
			if( addrEl->addr )//Needed incase of a tun interface
			{
				std::cout << "\tAddress Family: " << addrEl->addr->sa_family << std::endl;
				switch(addrEl->addr->sa_family)
				{
					case AF_INET:
						std::cout << "\tAddress Family Name: AF_INET" << std::endl;
						if (addrEl->addr)
							std::cout << "\tAddress: " << 
								iptos(((struct sockaddr_in *)addrEl->addr)->sin_addr.s_addr) << std::endl;
						if (addrEl->netmask)
							std::cout << "\tNetmask: " << 
								iptos(((struct sockaddr_in *)addrEl->netmask)->sin_addr.s_addr) << std::endl;
						if (addrEl->broadaddr)
							std::cout << "\tBroadcast Address: " << 
								iptos(((struct sockaddr_in *)addrEl->broadaddr)->sin_addr.s_addr) << std::endl;
						if (addrEl->dstaddr)
							std::cout << "\tDestination Address: " << 
								iptos(((struct sockaddr_in *)addrEl->dstaddr)->sin_addr.s_addr) << std::endl;
						break;
					case AF_INET6:
						std::cout << "\tAddress Family Name: AF_INET6" << std::endl;
						break;
					default:
						std::cout << "\tAddress Family Name: Unknown" << std::endl;
						break;
				}
			}
			std::cout << std::endl;
		} 
	}
}

std::string DevicesLookup::iptos(u_long in)
{
	std::stringstream output;
	u_char *pByte;
	pByte = (u_char *)&in;
	output << (unsigned int) pByte[0]
	<< "." << (unsigned int) pByte[1]
	<< "." << (unsigned int) pByte[2]
	<< "." << (unsigned int) pByte[3] << std::flush;
	return output.str();
}
