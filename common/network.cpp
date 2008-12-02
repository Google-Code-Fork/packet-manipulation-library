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

#include "network.h"
#include <stdexcept>

Network::Network( NetworkProtocol networkProtocol ) : networkProtocol_( networkProtocol )
{
	if( networkProtocol_ == TCP )
	{
		socket_ = socket( AF_INET, SOCK_STREAM, 0 );
		if ( socket_ == 0 )
			throw std::runtime_error( "Cannot create TCP socket" );
	}
	else if ( networkProtocol_ == UDP )
	{
		socket_ = socket( AF_INET, SOCK_DGRAM, 0 );
		if ( socket_ == 0 )
			throw std::runtime_error( "Cannot create UDP socket" );
	}

}

Network::Network( const Network & network )
{
	networkProtocol_ = network.networkProtocol_;
	socket_ = network.socket_;
}

Network::~Network()
{
}

void Network::listen( int Port )
{
}
