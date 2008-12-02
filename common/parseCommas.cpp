/**
 * * INAV - Interactive Network Active-traffic Visualization
 * * Copyright © 2007  Nathan Robinson, Jeff Scaparra
 * *
 * * This file is a part of INAV.
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


#include <vector>
#include <string>

std::vector< std::string > parseCommas( std::string destinations )
{
	std::vector< std::string > ips;
	while( true )
	{
		int foundAt = destinations.find( "," );
		if( foundAt == std::string::npos )
		{
			ips.push_back( destinations );
			break;
		}
		std::string tmp;
		tmp = destinations.substr(0, foundAt);
		ips.push_back( tmp );
		destinations = destinations.substr( foundAt + 1 );
	}
	return ips;
}

