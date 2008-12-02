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


#include <ctype.h>
#include <string>
#include <algorithm>
#include "xmlParser.h"


std::string xmlParser( std::string xml, std::string searchTerm )
{
	std::transform( xml.begin(), xml.end(), //source
			xml.begin(), //destination
			tolower);  //operation

	std::transform( searchTerm.begin(), searchTerm.end(),
			searchTerm.begin(),
			tolower);

	std::string openTag = "<";
	std::string closeTag = "</";

	std::string::size_type idx = xml.find( openTag );
	while( idx != std::string::npos )
	{
		++idx;
		while( xml.at( idx ) == ' ' ) //Get rid of any white space:)
		{
			++idx;
		}
		if( xml.substr( idx, searchTerm.size() ) == searchTerm ) //is this what we are looking for
		{
			idx += searchTerm.size(); //must find the closing '>'
				while( xml.at( idx ) == ' ' ) //Get rid of any white spaces
				{
					++idx;
				}
			if( xml.at(idx) == '>' ) //found the closer
			{
				++idx;
				break;
			}
		}
		else
		{
			//Keep looking
		idx = xml.find( openTag, idx );
		}
	}

	std::string::size_type start = idx;
	if( start == std::string::npos )
		return std::string();

	idx = xml.find( closeTag, start );
	if( idx == std::string::npos )
		return std::string();
	std::string::size_type stop = idx;
	idx+=closeTag.size();
	while( xml.at( idx ) == ' ' )
	{
		++idx;
	}
	std::string answer;
	if( xml.substr( idx, searchTerm.size() ) == searchTerm )
	{
		answer = xml.substr( start, stop - start );
	}
	return answer;
}
