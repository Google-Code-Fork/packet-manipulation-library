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
//! \file test.cpp 
//! This is a test program for PacMan

#include "packetBuilder.h"
#include <iostream>

int main()
{
  Ethernet e;
  IPv4 ip;
  TCP tcp;
  Raw raw;
  Packet p;
  e.setType( ethernetProtocol::ETH_P_IP );
  p.pushBackLink( e );
  ip.setProtocol( ipProtocols::IPPROTO_TCP );
  p.pushBackInet( ip );
  p.pushBackTrans( tcp );
  std::vector< uint8_t > data( 100 );
  raw.setData( data );
  p.pushBackApp( raw );

  //TEST getting the byte buffer associated with packet p;
  PacketBuffer packBuff;
  packBuff = p.makePacket();

  //Test building packet with a packet buffer
  PacketBuilder pb;
  Packet p2 = pb.buildPacket<Ethernet>( packBuff );

  std::cout << "p2.size(): " << p2.getSize() << std::endl;
  std::cout << "p.size(): " << p.getSize() << std::endl;
  std::cout << "packetBuff.size(): " << packBuff.size() << std::endl;

  std::cout << "p is " <<  (p.linkIs<Ethernet>( 0 ) ? "Ethernet" : "Not Ethernet" ) << std::endl;
  std::cout << "p2 is " << (p2.linkIs<Ethernet>( 0 ) ? "Ethernet" : "Not Ethernet" ) << std::endl;

  

  return 0;
}
