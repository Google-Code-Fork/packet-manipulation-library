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
}

StreamProcessor::StreamProcessor():streaming_( false )
{

}

StreamProcessor::~StreamProcessor()
{
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
//		std::string streamName = buildStreamName( p );
	}
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
		

    QVector< DNSResponse > responses;
    if( p.appSize() && p.appIs< DNS >() )
    {
        QString source;
        if( p.inetSize() && p.inetIs< IPv4 >() )
        {
            IPv4 ip = p.getInet<IPv4>();
            uint32_t address = htonl(ip.destinationAddress());
            source = inet_ntoa( (*(struct in_addr*)&address));
        }
       /* else if( p.inetIs<IPv6>() ) //currently not working in PacMan lib
        {
            IPv6 ip = p.getInet<IPv6>();
            //TODO

        }*/
        DNS dns = p.getApp<DNS>( );
        if( dns.isResponse() ) //don't need to count responses
        {
            for( uint32_t i = 0; i < dns.numberOfAnswers(); ++i )
            {
                //TODO: Need to add DNSSEC Stuff
                DNSResponse r;
                QVector< DNSQuery > queries = queryBuilder(p);
                r.setHost(source);
                r.setTimestamp( p.timestamp().tv_sec );
                if( queries.size() > 0)
                  r.setQuery(queries[0]);
                r.setName( dns.answer(i).domainName().c_str() );
                r.setType( dnsTypeString( dns.answer(i).type() ) );
                r.setClass( dnsClassString( dns.answer(i).dnsClass() ) );
                r.setTTL( dns.answer(i).timeToLive() );
                r.setRecord( dnsAnswerString( dns.answer(i).data(), dns.answer(i).type() ));
                responses.push_back(r);
            }
        }
    }
    return responses;
}
