/**
 * * INAV - Interactive Network Active-traffic Visualization
 * * Copyright © 2007  Nathan Robinson, Jeff Scaparra
 * * Copyright © 2008 Jeff Scaparra
 * *
 * * This file is a part of the INAV project.
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


#include <sstream>
#include <string>

//FOR LEXICAL TYPE CHANGING 
//Call with int a = ss_atoi<int>( std::string );
template<typename RT>
RT ss_atoi( const std::string& the_string )
{
  std::istringstream temp_ss(the_string);
  RT num;
  temp_ss >> num;
  return num;
}

template< typename  RT >
std::string ss_itoa( const RT& num )
{
  std::stringstream ss;
  ss << num;
  return ss.str();
}

