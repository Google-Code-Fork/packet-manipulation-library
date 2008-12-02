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

#ifndef NETWORK_H
#define NETWORK_H

#ifndef WIN32 // UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>
#endif

enum NetworkProtocol { TCP, UDP };
#ifndef WIN32 //UNIX
typedef Socket int;
#endif

class Network
{
	public:
		Network( NetworkProtocol networkProtocol = TCP );
		Network( const Network & network );
		~Network( );
		void send( std::string buffer );
		std::string recv( );
		void listen( int port );
		

	private:
		NetworkProtocol networkProtocol_;
		Socket socket_;

};











#endif
