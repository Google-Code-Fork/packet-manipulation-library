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


#include <string>
#include <stdexcept>
#include <vector>

std::string parser(int argc, char *argv[], std::string option)
{
	const static std::string nullString;
	static std::vector<std::string> commandLineOptions;
	
	if( commandLineOptions.size() == 0 )
	{
    for( int i = 1; i < argc; ++i )
		{
			commandLineOptions.push_back( argv[i] );
		}
	}

	commandLineOptions.push_back("-");

	std::vector<std::string>::iterator itr;
  std::string::size_type foundAt = std::string::npos;
	for( itr = commandLineOptions.begin(); itr != commandLineOptions.end(); ++itr )
	{
		foundAt = (*itr).find( option );
		if( foundAt != std::string::npos )
		{
			if( foundAt > 0 && (*itr).at(foundAt-1) == '-')
				continue;
			break;
		}
	}

	/* Debug Code
	std::cerr << "itr: " << *itr << std::endl;
	std::cerr << "foundAt: " << foundAt << std::endl;
	*/

	if( itr != commandLineOptions.end() )
	{
		if( foundAt != std::string::npos )
		{
			try
			{
				if( (*itr).at(foundAt+option.size()) == '=' )
					return (*itr).substr(foundAt + 1 + option.size());
			}
			catch( std::out_of_range error )
			{
				//This can happen and it is normal
			}
			try
			{
				if( (*(itr+1)).at(0) != '-' )
					return *(itr+1);
			}
			catch( std::out_of_range error )
			{
				//This can happen and it is normal
			}
			return "set";
		}
	}
				
	return nullString;
}

