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
#include "ethernet.h"
#include "mac.h"
#include "link.h"
//This is file is to ensure that all instances of an object work 
//This is to find problems with templates and abstract pure functions and
//classes.
#include <iostream>

//! \file test.cpp 
//! This is a test program for PacMan
//


int main()
{
  LinkData* l;
  Ethernet e;
  MACAddress m;
  l = &e;
  l = new Ethernet;
  *l = e;
  std::cout << "l = &e" << std::endl;
  std::cout << "Ethernet: " <<  (l->isEthernet() ? "yes" : "no") << std::endl;
  std::cout << "MAC: " <<  (l->isMac() ? "yes" : "no") << std::endl; 
  delete l;
  l = &m;
  std::cout << "l = &m" << std::endl;
  std::cout << "Ethernet: " <<  (l->isEthernet() ? "yes" : "no") << std::endl;
  std::cout << "MAC: " <<  (l->isMac() ? "yes" : "no") << std::endl; 
  
  std::vector< LinkData* > ldata;
  l = new Ethernet(e);
  ldata.push_back( l );
  ldata.push_back( (new MACAddress(m)) );
  std::cout << "ldata.at(0)" << std::endl;
  std::cout << "Ethernet: " <<  (ldata.at(0)->isEthernet() ? "yes" : "no") << std::endl;
  std::cout << "MAC: " <<  (ldata.at(0)->isMac() ? "yes" : "no") << std::endl; 
  std::cout << "ldata.at(1)" << std::endl;
  std::cout << "Ethernet: " <<  (ldata.at(1)->isEthernet() ? "yes" : "no") << std::endl;
  std::cout << "MAC: " <<  (ldata.at(1)->isMac() ? "yes" : "no") << std::endl; 
  
  std::vector< Link > data;
  data.push_back( e );
  data.push_back( m );
  std::cout << ( data.at( 0 ).is<Ethernet>() ? "yes" : "no" ) << std::endl;

  e = data.at( 0 ).get<Ethernet>();

  Ethernet* eptr;
  l = &e;
  eptr = (Ethernet*)l;
  std::cout << "Ethernet: " <<  (eptr->isEthernet() ? "yes" : "no") << std::endl;
  std::cout << "MAC: " <<  (eptr->isMac() ? "yes" : "no") << std::endl; 


  return 0;
}
