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

/***********************************************************************
 * Last Edited:
 * Apr 6, 2011 --- Jeff Scaparra
 *
 *
 * ********************************************************************/

/** \file devicesLookup.cpp
 * This is the definition for the class DevicesLookup
 */

#include "devicesLookup.h"
#include <string>
#include <iostream>
#include <stdio.h>

pcap_if_t* DevicesLookup::alldevs_ = NULL;

DevicesLookup::DevicesLookup()
{
	char errbuf[PCAP_ERRBUF_SIZE+1];
	/* Retrieve the device list */
	if( (alldevs_ == NULL) && (pcap_findalldevs(&alldevs_, errbuf) == -1))
	{
		std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
		exit(1);
	}
}

pcap_if_t* DevicesLookup::operator[](const int &index)
{
	pcap_if_t *dev = alldevs_;
	int count = 0;		/* device traversal index */

	while(count != index && dev != NULL)
	{
		dev = dev->next;
		count++;
	}

	return dev;
}

pcap_if_t* DevicesLookup::operator[](const std::string &name)
{
	pcap_if_t *dev = alldevs_;

  for(dev = alldevs_; (dev != NULL) && !strcmp(dev->name, name.c_str()); dev = dev->next)
  {
  }

	return dev;
}

void DevicesLookup::refresh()
{
    pcap_freealldevs(alldevs_);		/* Free the device list */

	char errbuf[PCAP_ERRBUF_SIZE+1];
	/* Retrieve the device list */
	if( (alldevs_ == NULL) && (pcap_findalldevs(&alldevs_, errbuf) == -1))
	{
		std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
		exit(1);
	}
}

DevicesLookup::~DevicesLookup()
{
    //DO NOT FREE THE LIST SINCE IT IS NOW STATIC. It will be needed on follow up calls to deviceslookup.


  //std::cout << "Freeing the device list..." << std::endl;
  //	pcap_freealldevs(alldevs_);		/* Free the device list */
}

bool DevicesLookup::isValid(const std::string &name) const
{
	pcap_if_t *dev = alldevs_;

  for(dev = alldevs_; dev != NULL && !strcmp(dev->name, name.c_str()); dev = dev->next)
  {
  }

	return (dev != NULL); 

}

void DevicesLookup::printAllDevices() const
{
	/* Scan the list printing every entry */
	for(pcap_if_t* dev=alldevs_;dev != NULL;dev=dev->next)
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
				std::cout << "\tAddress Family: " << static_cast<uint16_t>(addrEl->addr->sa_family) << std::endl;
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

bool DevicesLookup::isLoopback( const std::string &device ) const
{
	/* Scan the list printing every entry */
	for( pcap_if_t* dev=alldevs_; dev != NULL; dev=dev->next)
	{
		
		std::string name = dev->name;
		if( name == device )
		{
			return ((dev->flags & PCAP_IF_LOOPBACK) ? true : false);
		}
		else
			continue;
	}
	return false;
}

std::string DevicesLookup::iptos(const uint32_t &in) const
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

std::string DevicesLookup::exec(const char *cmd) const
{
  FILE* pipe = popen( cmd, "r" );
  if( !pipe )
    return "Error";
  char buffer[128];
  std::string result = "";
  while( !feof(pipe) )
  {
    if( fgets( buffer, 128, pipe ) != NULL )
      result += buffer;
  }
  pclose( pipe );
  return result;
}

std::vector< std::string > DevicesLookup::devicesAvailable() const
{
  std::vector< std::string > results;
  std::string deviceName = "";

  for(pcap_if_t* dev=alldevs_;dev != NULL;dev=dev->next)
  {
     deviceName = dev->name;
     results.push_back( deviceName );
  }
  return results;
}

std::string DevicesLookup::gateway() const
{
#ifdef __APPLE__
  std::string cmd = "netstat -nr | awk '/default/ {print $2}'";
#else
  std::string cmd = "ip route | awk '/via/ {print $3}'";
#endif
  return exec( cmd.c_str() );
}

std::string DevicesLookup::macAddress(const std::string &device) const
{
  std::string cmd = "ifconfig " + device + " | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}'";
  return exec( cmd.c_str() );
}

std::string DevicesLookup::netmask(const std::string &device, const uint32_t &family) const
{
  std::string netmask = "";
  pcap_if_t* dev = 0;
  for(dev=alldevs_; dev != NULL; dev=dev->next)
  {
     if( dev->name == device )
       break;
  }

  for(pcap_addr_t *addrEl=dev->addresses;addrEl != NULL;addrEl=addrEl->next)
  {
    if( addrEl->addr && addrEl->addr->sa_family == family )//Needed incase of a tun interface
    {
      switch(addrEl->addr->sa_family)
      {
        case AF_INET:
          if (addrEl->netmask)
              netmask = iptos(((struct sockaddr_in *)addrEl->netmask)->sin_addr.s_addr);
          break;
        case AF_INET6:
          //TODO: add ipv6 support
          break;
        default:
          break;
      }
    }
  }

  return netmask;
}

std::vector< std::string > DevicesLookup::addressFamilies(const std::string &device) const
{
  std::vector< std::string > results;
  pcap_if_t* dev = 0;
  for(dev=alldevs_; dev != NULL; dev=dev->next)
  {
     if( dev->name == device )
       break;
  }

  for(pcap_addr_t *addrEl=dev->addresses;addrEl != NULL;addrEl=addrEl->next)
  {
    if( addrEl->addr )//Needed incase of a tun interface
    {
      switch(addrEl->addr->sa_family)
      {
      case AF_INET:
        results.push_back( "AF_INET" );
        break;
      case AF_INET6:
        results.push_back( "AF_INET6" );
        break;
      case AF_UNIX: //Same as AF_LOCAL and AF_FILE
        results.push_back( "AF_UNIX" );
        break;
      case AF_APPLETALK:
        results.push_back( "AF_APPLETALK" );
        break;
      case AF_IPX:
        results.push_back("AF_IPX");
        break;
      case AF_UNSPEC:
        results.push_back("AF_UNSPEC");
        break;
     /* case AF_AX25:
        results.push_back( "AF_AX25" );
        break;
      case AF_NETROM:
        results.push_back( "AF_NETROM" );
        break;
      case AF_BRIDGE:
        results.push_back( "AF_BRIDGE" );
        break;
      case AF_ATMPVC:
        results.push_back( "AF_ATMPVC" );
        break;
      case AF_X25:
        results.push_back( "AF_X25" );
        break;
      case AF_ROSE:
        results.push_back( "AF_ROSE" );
        break;
      case AF_DECnet:
        results.push_back( "AF_DECnet" );
        break;
      case AF_NETBEUI:
        results.push_back( "AF_NETBEUI" );
        break;
      case AF_SECURITY:
        results.push_back( "AF_SECURITY" );
        break;
      case AF_KEY:
        results.push_back( "AF_KEY" );
        break;
      case AF_NETLINK: //same a AF_ROUTE
        results.push_back( "AF_NETLINK" );
        break;
      case AF_PACKET:
        results.push_back( "AF_PACKET" );
        break;
      case AF_ASH:
        results.push_back( "AF_ASH" );
        break;
      case AF_ECONET:
        results.push_back( "AF_ECONET" );
        break;
      case AF_ATMSVC:
        results.push_back( "AF_ATMSVC" );
        break;
      case AF_SNA:
        results.push_back( "AF_SNA" );
        break;
      case AF_IRDA:
        results.push_back( "AF_IRDA" );
        break;
      case AF_PPPOX:
        results.push_back( "AF_PPPOX" );
        break;
      case AF_WANPIPE:
        results.push_back( "AF_WANPIPE" );
        break;
      case AF_BLUETOOTH:
        results.push_back( "AF_BLUETOOTH" );
        break;
      case AF_MAX:
        results.push_back( "AF_MAX" );
        break;*/
      default:
        results.push_back( "UNKNOWN" );
        break;
      }
    }
  }

  return results;
}

std::string DevicesLookup::address(const std::string &device, const uint32_t &family) const
{
  std::string address = "";
  pcap_if_t* dev = 0;
  for(dev=alldevs_; dev != NULL; dev=dev->next)
  {
    if( dev->name == device )
      break;
  }

  for(pcap_addr_t *addrEl=dev->addresses;addrEl != NULL;addrEl=addrEl->next)
  {
    if( addrEl->addr && addrEl->addr->sa_family == family )//Needed incase of a tun interface
    {
      switch(addrEl->addr->sa_family)
      {
      case AF_INET:
        if (addrEl->addr)
          address = iptos(((struct sockaddr_in *)addrEl->addr)->sin_addr.s_addr);
        break;
      case AF_INET6:
        break;
      }
    }
  }
  return address;
}
