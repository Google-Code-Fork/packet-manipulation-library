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

/** \file StreamProcessor.h
 * This is the declaration for the class StreamProcessor
 */

/** \class StreamProcessor
 * This class is used in with a sniffer to handle streams of data (i.e. TCP)
 *
 */



#ifndef STREAM_PROCESSOR_H
#define STREAM_PROCESSOR_H

#include "tcpStream.h"
#include "../Sniffer/sniffer.h"
#include "StreamData.h"

/* Use much like the sniffer class except that we can get streams instead of
 * packets
 */

void* run_streamer( void *data );

class StreamProcessor : public Sniffer
{
	public:
		StreamProcessor( );
		virtual ~StreamProcessor();
		void *streamer();
		void start();
		int numberOfCurrentStreams() const;
		int numberOfFishishedStreams() const;
		TCPStream popFinishedStream() const;
		TCPStream currentStream( const int &index ) const;

	private:
		std::string buildStreamName( const Packet &p ) const;
		Thread streamThread_;
		StreamData currentStreams_;
		StreamData finishedStreams_;
		mutable Mutex streamingMutex_;
		bool streaming_;


};

#endif
