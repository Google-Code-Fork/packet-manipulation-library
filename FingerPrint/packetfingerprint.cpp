#include "fingerprint.h"

const std::string PacketFingerprint::SYN_DB = "p0f.fp";
const std::string PacketFingerprint::SYNACK_DB = "p0fa.fp";
const std::string PacketFingerprint::RST_DB = "p0fr.fp";
const std::string PacketFingerprint::OPEN_DB = "p0fo.fp";

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

void PacketFingerprint::init( uint16_t useSignature )
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

void PacketFingerprint::reinit()
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
	init();
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


