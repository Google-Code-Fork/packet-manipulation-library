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
//
//This is file is to ensure that all instances of an object work 
//This is to find problems with templates and abstract pure functions and
//classes.
#include "../raw.h"
#include <vector>
#include "../app.h"
#include <iostream>

int main()
{
  Raw raw;
  AppData* aptr = &raw;
  std::cout << "Is RAW? " << ( aptr->isRaw() ? "Yes" : "No" ) << std::endl;
  std::vector< App > data;
  data.push_back( raw );
  std::cout << "Is Raw? " << ( data.at( 0 ).is<Raw>() ? "YES!" : "NO" ) << std::endl;
  std::cout << "Is vector<int>? " << ( data.at( 0 ).is< std::vector<int> >() ? "YES" : "NO" ) << std::endl;

  raw = data.at( 0 ).get<Raw>();


  return 0;
}
