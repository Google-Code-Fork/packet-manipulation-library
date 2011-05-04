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

/***************************************************************
 *   #### EDIT LOG ####
 *   April 26, 2011 -- Jeff Scaparra (Initial Design)
 *
 **************************************************************/

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
#include <map>
#include "Stream.h"
#include <deque>
#include <vector>
/* Use much like the sniffer class except that we can get streams instead of
 * packets
 */

void* run_streamer( void *data );
void* run_timeouts( void *data );

class StreamProcessor : public Sniffer
{
	public:
		StreamProcessor( );
		virtual ~StreamProcessor();
		//! Called by the run_streamer thread not for userland use.
		void* streamer();
		//! Called by the run_timeouts thread not for userland use.
		void* connectionTimeOutThread();
		//! Use the sniffing capability to gather packets rather than wait for the
		//! user to supply them
		void startSniffing();
		//! Cancels the sniffer thread which can be not very graceful but if your
		//! stopping then you probably don't care.
		void stopSniffing();
		//! Process user supplied packets. Useful if the userland application needs
		//! copies of packets. 
		void processPacket( const Packet &p );
		//! Start the timeout thread to close stream process on streams that haven't
		//! communicated in a while. This also assumes that the packets being
		//! processed are being inputed in realtime. If a pcap is being use the last
		//! edit wila likely be at a time later than the timeout and everything will
		//! time out.
		void enableTimeouts( const uint32_t &seconds = 300 ); //defaults to 5 min [[RFC0793]]
		//! Disables timeouts functionality. A new syn packet starts a new stream.
		void disableTimeouts();
		//! The number of finished streams waiting to pop
		int numberOfFishishedStreams() const;
		//! Returns finished streams in the order they finished
		Stream popFinishedStream();
		//! Returns all streams finished and currently in progress.
		std::deque< Stream > findStreams( const uint32_t &ipa, const uint16_t
				&porta, const uint32_t &ipb, const uint16_t &portb, const std::string
				&protocol = "TCP" ) const;
		//! Returns all streams with a given name as given in the availableStreams
		//! function
		std::deque< Stream > findStreams( const std::string &name ) const; 
		//! Returns the names of all the available streams
		std::vector< std::string > availableStreams() const;

	private:
		//! builds the stream name as used with the stream processor. This is
		//! different than asking the stream for its name. The names provided by the
		//! individual streams are for use by user processes this is not. 
		std::string buildStreamName( const uint32_t &ipa, const uint16_t
				&porta, const uint32_t &ipb, const uint16_t &portb, const std::string
				&portocol = "TCP" ) const;

		void ipv4TCPStreamer( const Packet &p );
		void ipv4UDPStreamer( const Packet &p );


	private: //variabales
		Thread snifferThread_; //if using the sniffer functionality
		Thread timeoutThread_; //if utilizing timeout functionality
		mutable Mutex allStreamsMutex_;
		std::map< std::string, std::deque< Stream* > > allStreams_;
		std::deque< std::string > finishedStreams_;
		mutable Mutex finishedStreamsMutex_;
		mutable Mutex sniffingMutex_;
		bool sniffing_;
		mutable Mutex checkingTimeoutsMutex_;
		bool checkingTimeouts_;
		uint32_t timeout_; //in seconds


};

#endif
