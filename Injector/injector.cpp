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

/** \file injector.cpp
 * This is the definition for the class Injector
 */

#include "injector.h"

Injector::Injector(): handle_(NULL)
{
}

Injector::Injector( const std::string &deviceName ):handle_(NULL)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	dev_.setDevice(deviceName);
	handle_ = pcap_open_live(dev_.device().c_str(), BUFSIZ, 1, 1000, errbuf);
	if (handle_ == NULL)
	{
		std::cerr << "Couldn't open device " << dev_.device() << std::endl;
		std::cerr << "ERROR: " << errbuf << std::endl;
		exit(2);
	}
}

void Injector::setDevice(const std::string &deviceName)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	if( handle_ )
		pcap_close( handle_ );
	handle_ = NULL;
	dev_.setDevice(deviceName);
	handle_ = pcap_open_live(dev_.device().c_str(), BUFSIZ, 1, 1000, errbuf);
	if (handle_ == NULL)
	{
		std::cerr << "Couldn't open device " << dev_.device() << std::endl;
		std::cerr << "ERROR: " << errbuf << std::endl;
		exit(2);
	}
}

Injector::Injector( const Injector &n ):handle_(NULL)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	dev_ = n.dev_;
	
	handle_ = pcap_open_live(dev_.device().c_str(), BUFSIZ, 1, 1000, errbuf);
	if (handle_ == NULL)
	{
		std::cerr << "Couldn't open device " << dev_.device() << std::endl;
		std::cerr << "ERROR: " << errbuf << std::endl;
		exit(2);
	}
}

Injector& Injector::operator=( const Injector &n )
{
	char errbuf[PCAP_ERRBUF_SIZE];
	dev_ = n.dev_;
	if( handle_ )
	  pcap_close( handle_ );
	handle_ = NULL;
	
	handle_ = pcap_open_live(dev_.device().c_str(), BUFSIZ, 1, 1000, errbuf);
	if (handle_ == NULL)
	{
		std::cerr << "Couldn't open device " << dev_.device() << std::endl;
		std::cerr << "ERROR: " << errbuf << std::endl;
		exit(2);
	}
	return *this;
}

std::string Injector::device() const
{
	return dev_.device();
}

void Injector::inject( const Packet &p ) const
{
	inject( p.makePacket() );
}

void Injector::inject(const PacketBuffer &pb ) const
{
	if( handle_ == NULL )
	{
		std::cerr << "ERROR: Problems injecting packet" << std::endl;
		std::cerr << "NO DEVICE SET" << std::endl;
		exit(2);
	}
	int err = pcap_sendpacket(handle_, pb.buffer(), pb.size());
	if( err )
	{ //clean up
		std::cerr << "ERROR: Problems injecting packet " << std::endl;
		std::cerr << pcap_geterr( handle_ ) << std::endl;
		exit( 2 );
	}
}


Injector::~Injector()
{
	if( handle_ )
		pcap_close(handle_);
}
