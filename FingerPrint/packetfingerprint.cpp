#include "packetfingerprint.h"

std::string PacketFingerprint::synDB_ = "p0f.fp";
std::string PacketFingerprint::synAckDB_ = "p0fa.fp";
std::string PacketFingerprint::rstDB_ = "p0fr.fp";
std::string PacketFingerprint::openDB_ = "p0fo.fp";

const int PacketFingerprint::MAXSIGS = 1024;
const int PacketFingerprint::MAXLINE = 1024;
const int PacketFingerprint::MAXDIST = 40;
const int PacketFingerprint::MAXOPT = 16;
const int PacketFingerprint::MY_MAXDNS = 32;
const int PacketFingerprint::DEFAULT_QUERY_CACHE = 120;
const int PacketFingerprint::MAX_TIMEDIF = 600;
const int PacketFingerprint::PKT_DLEN = 16;
const int PacketFingerprint::PKT_MAXPAY = 45;
const int PacketFingerprint::PACKET_BIG = 100;
const int PacketFingerprint::PACKET_SNAPLEN = 200;
const int PacketFingerprint::QUERY_TIMEOUT = 2;

const int PacketFingerprint::SIGHASH_SIZE = 16;
bool PacketFingerprint::hasBeenInit_=false;

PacketFingerprint::PacketFingerprint( uint16_t useSignature ) 
{
		init( useSignature );
}

void PacketFingerprint::init( const uint16_t &useSignature )
{
	if( ! hasBeenInit_ )
	{
		for( int i = 0; i < SIGHASH_SIZE; ++i )
		{
			synHashLookup_.push_back( NULL );
			synAckHashLookup_.push_back( NULL );
			rstHashLookup_.push_back( NULL );
			openHashLookup_.push_back( NULL );
		}
		if( useSignature & SynSignatures )
		{
			initSyn();
		}
		if( useSignature & SynAckSignatures )
		{
			initSynAck();
		}
		if( useSignature & RstSignatures )
		{
			initRst();
		}
		if( useSignature & OpenSignatures )
		{
			initOpen();
		}
		hasBeenInit_ = true;
	}
}
/*
void PacketFingerprint::reinit(const uint16_t &useSignature)
{
	synHashLookup_.clear();
	synSignatures_.clear();
	synAckHashLookup_.clear();
	synAckSignatures_.clear();
	rstHashLookup_.clear();
	rstSignatures_.clear();
	openHashLookup_.clear();
	openSignatures_.clear();
	hasBeenInit_ = false;
	init(useSignature);
}
*/

void PacketFingerprint::setSynDB( const std::string &file )
{
	synHashLookup_.clear();
	synSignatures_.clear();
	synDB_ = file;
	for( int i = 0; i < SIGHASH_SIZE; ++i )
		synHashLookup_.push_back( NULL );
	initSyn();
}

void PacketFingerprint::setSynAckDB( const std::string &file )
{
	synAckHashLookup_.clear();
	synAckSignatures_.clear();
	synAckDB_ = file;
	for( int i = 0; i < SIGHASH_SIZE; ++i )
		synAckHashLookup_.push_back( NULL );
	initSynAck();
}

void PacketFingerprint::setRstDB( const std::string &file )
{
	rstHashLookup_.clear();
	rstSignatures_.clear();
	rstDB_ = file;
	for( int i = 0; i < SIGHASH_SIZE; ++i )
		rstHashLookup_.push_back( NULL );
	initRst();
}

void PacketFingerprint::setOpenDB( const std::string &file )
{
	openHashLookup_.clear();
	openSignatures_.clear();
	openDB_ = file;
	for( int i = 0; i < SIGHASH_SIZE; ++i )
		openHashLookup_.push_back( NULL );
	initOpen();
}

void PacketFingerprint::initSyn()
{
}

void PacketFingerprint::initSynAck()
{
}

void PacketFingerprint::initRst()
{
}

void PacketFingerprint::initOpen()
{
}


