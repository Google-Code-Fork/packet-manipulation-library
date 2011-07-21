/**
 * * Copyright © 2011 Jeff Scaparra
 * *
 * * This file is a part of the PacMan project.
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

#include "stringUtils.h"
#include <stdint.h>

std::vector< std::string > split( const std::string &string, const char &del )
{
	std::vector< std::string > stringList;
	std::string tmpString;
  for( uint32_t i = 0; i < string.size(); ++i )
	{
    if( string[i] != del )
		{
			tmpString += string[i];
		}
		else
		{
			stringList.push_back( tmpString );
			tmpString = "";
		}
	}
	if( tmpString.size() )
		stringList.push_back( tmpString );

	return stringList;
}


std::string removeLeadingWhiteSpace(const std::string &string)
{
  std::string newString = "";
  bool foundChar = false;
  for( int i = 0; i < string.size(); ++i )
  {
    if( foundChar )
    {
      newString.push_back( string[i] );
      continue;
    }
    switch( string[i] )
    {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
      break;
      default:
       newString.push_back( string[i] );
       foundChar = true;
    };
  }
  return newString;
}
