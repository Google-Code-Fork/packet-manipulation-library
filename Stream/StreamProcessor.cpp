/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011 Jeff Scaparra
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

#include "StreamProcessor.h"

void* run_streamer( void* data )
{
	StreamProcessor* processor = static_cast< StreamProcessor* >( data );
  processor->streamer();
  return NULL;
}

StreamProcessor::StreamProcessor():streaming_( false )
{

}

StreamProcessor::~StreamProcessor()
{
}

void* StreamProcessor::connectionTimeOutThread()
{
  while( true )
  {
    std::vector< std::string > itemsToDelete;
    sleep( timeout_ );
    MutexLocker lock( allStreamsMutex_ );
    std::map< std::string, std::deque< Stream* > >::iterator itr;
    for( itr = allStreams_.begin(); itr != allStreams_.end(); ++itr )
    {
      if( time(NULL) - itr->second.back()->lastAccess() > timeout_ )
      {
        itemsToDelete.push_back( itr->first );
      }
    }
  }

  return NULL;
}

void StreamProcessor::startSniffing()
{
	Sniffer::start();
  MutexLocker lock( sniffingMutex_ );
	streaming_ = true;
	lock.unlock();
  snifferThread_.setStartRoutine( run_streamer );
  snifferThread_.start( this );
}

void* StreamProcessor::streamer( )
{
	//runs inside spawned thread after a call to start.
	while( streaming_ )
	{
		Packet p = popPacket();
//std::string streamName = buildStreamName( p );
	}
  return NULL;
}

void StreamProcessor::stopSniffing()
{
  MutexLocker lock( sniffingMutex_ );
	streaming_ = false;
}

std::string StreamProcessor::buildStreamName( const Packet &p ) const
{
	if( p.inetSize() && p.transSize() && p.inetIs< IPv4 >() )
	{
		uint32_t ipa = p.getInet<IPv4>().sourceAddress();
		uint32_t ipb = p.getInet<IPv4>().destinationAddress();
		if( p.transIs<TCP>() )
		{

		}
		else if( p.transIs< UDP >() )
		{

		}

	}
	else if( p.inetSize() && p.transSize() && p.inetIs< IPv6 >() )
	{

	}
	return "";
}
