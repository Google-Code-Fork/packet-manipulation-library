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

#include "oui.h"
#include <string>
#include <vector>
#include <fstream>
#include "../../common/stringUtils.h"
#include "../../common/helper.h"

std::map< uint32_t, ouitype > OUILookup::lookup_;

OUILookup::OUILookup( const std::string &ouiListFile )
{
  buildLookupTable(ouiListFile);
}

void OUILookup::buildLookupTable(const std::string &ouiListFile)
{
  lookup_.clear();
  std::vector< std::vector< std::string > > groups = buildGroups(
        readFile( ouiListFile ) );
  for( uint32_t i = 1; i < groups.size(); ++i ) //0 group is informational
  {
    std::vector< std::string > group = groups[i];
    uint32_t oui = parseOUI( group[1] );
    std::string company = parseCompany( group[1] );
    std::string address = "";
    for( uint32_t i = 2; i < (group.size() - 1); ++i )
    {
      address += group[i];
    }
    std::string country = group[ group.size() - 1 ];
    lookup_[ oui ].company = company;
    lookup_[ oui ].address = address;
    lookup_[ oui ].country = country;
  }
}

std::string OUILookup::parseCompany(const std::string &dataLine) const
{
  std::string result = "";
  uint32_t index = 0;
  while( index < dataLine.size() && dataLine[index] != ')' )
  {
    index++;
  }
  index+=2;
  for( ; index < dataLine.size(); ++index )
    result.push_back( dataLine[index] );

  return result;
}

uint32_t OUILookup::parseOUI(const std::string &dataLine) const
{
  std::string stringNum = "";
  uint32_t i = 0;
  while( ( ( dataLine[i] >= '0' && dataLine[i] <= '9')
           || ( dataLine[i] >= 'A' && dataLine[i] <= 'B' ) )
           && i < dataLine.size() )
  {
    stringNum.push_back( dataLine[i] );
    ++i;
  }

  return ss_atoi< uint32_t >( stringNum, true );
}

std::vector< std::string > OUILookup::readFile( const std::string &filename ) const
{
  std::vector<std::string> file;
  std::string line;
  file.clear();
  std::ifstream infile ( filename.c_str(), std::ios_base::in);
  while (getline(infile, line, '\n'))
  {
    file.push_back ( removeLeadingWhiteSpace(line) );
  }

  return file;
}

std::vector< std::vector< std::string > > OUILookup::buildGroups( const std::vector< std::string > &file ) const
{
  std::vector< std::vector< std::string > > groups;
  std::vector< std::string > group;

  for( uint32_t i = 0; i < file.size(); ++i )
  {
    if( file[i].size() == 0 )
    {
      if( group.size() > 0 )
        groups.push_back( group );
      group.clear();
    }
    else
    {
      group.push_back( file[i] );
    }
  }
  return groups;
}

std::string OUILookup::company( const MACAddress &mac ) const
{
  uint32_t oui = calculateOUI( mac );
  return lookup_[oui].company;
}

std::string OUILookup::address( const MACAddress &mac ) const
{
  uint32_t oui = calculateOUI( mac );
  return lookup_[oui].address;
}

std::string OUILookup::country( const MACAddress &mac ) const
{
  uint32_t oui = calculateOUI( mac );
  return lookup_[oui].country;
}

uint32_t OUILookup::calculateOUI(const MACAddress &mac) const
{
  uint32_t oui = 0;
  std::vector< uint8_t > macBytes = mac.makePacket().vector();
  oui |= macBytes[0] << 16;
  oui |= macBytes[1] << 8;
  oui |= macBytes[2];
  return oui;
}

