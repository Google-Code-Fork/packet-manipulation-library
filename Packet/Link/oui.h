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

#ifndef OUI_H
#define OUI_H

/***************************************************************
  Intended to be populated with data from the IEEE OUI listing
  http://standards.ieee.org/develop/regauth/oui/oui.txt

  **************************************************************/

#include <map>
#include <string>
#include <vector>
#include "mac.h"

typedef struct ouitype
{
  std::string company;
  std::string address;
  std::string country;
} ouitype;


class OUILookup
{
public:
    explicit OUILookup( const std::string &ouiListFile );
    std::string company( const MACAddress &mac ) const;
    std::string address( const MACAddress &mac ) const;
    std::string country( const MACAddress &mac ) const;


private:
  uint32_t calculateOUI( const MACAddress &mac ) const;
  std::vector< std::string > readFile( const std::string &filename ) const;
  std::vector< std::vector< std::string > > buildGroups( const std::vector< std::string > &file ) const;
  uint32_t parseOUI( const std::string &dataLine ) const;
  std::string parseCompany( const std::string &dataLine ) const;
  void buildLookupTable( const std::string &ouiListFile );
  static std::map< uint32_t, ouitype > lookup_; //24bit OUI, and then the data
};

#endif // OUI_H
