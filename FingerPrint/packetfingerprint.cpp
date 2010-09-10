#include "packetfingerprint.h"
#include <fstream>
std::string PacketFingerprint::synDB_ = "p0f.fp";
std::string PacketFingerprint::synAckDB_ = "p0fa.fp";
std::string PacketFingerprint::rstDB_ = "p0fr.fp";
std::string PacketFingerprint::openDB_ = "p0fo.fp";

std::vector< Signature* > PacketFingerprint::synHashLookup_;
std::vector< Signature > PacketFingerprint::synSignatures_;
std::vector< Signature* > PacketFingerprint::synAckHashLookup_;
std::vector< Signature > PacketFingerprint::synAckSignatures_;
std::vector< Signature* > PacketFingerprint::rstHashLookup_;
std::vector< Signature > PacketFingerprint::rstSignatures_;
std::vector< Signature* > PacketFingerprint::openHashLookup_;
std::vector< Signature > PacketFingerprint::openSignatures_;

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

PacketFingerprint::~PacketFingerprint()
{
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
	readFile( synDB_, PacketFingerprint::synSignatures_, PacketFingerprint::synHashLookup_ );
}

void PacketFingerprint::initSynAck()
{
	readFile( synAckDB_, synAckSignatures_, synAckHashLookup_ );
}

void PacketFingerprint::initRst()
{
	readFile( rstDB_, rstSignatures_, rstHashLookup_ );
}

void PacketFingerprint::initOpen()
{
	readFile( openDB_, openSignatures_, openHashLookup_ );
}

void PacketFingerprint::readFile( const std::string &file,
																  std::vector< Signature > &signatures,
																	std::vector< Signature* > &hashTable )
{
	std::ifstream infile;
	infile.open( file.c_str() );
	if( !infile.is_open() ) 
		throw std::runtime_error( "Error: opening " + file );
	std::string signatureLine;

  while( infile.good() )
	{
		getline( infile, signatureLine, '\n');
		signatureLine = trim( signatureLine );
		if( signatureLine.size() == 0 )
			continue;
		Signature sig(signatureLine);
		signatures.push_back( sig );
		int index = signatures.size() - 1;
		Signature* ptr = &signatures.at(index);
		Signature* hashptr = hashTable[ sighash( sig.size(), sig.optCount(), sig.dontFragment(), sig.quirks() ) ];
		if( hashptr == NULL )
		{
			hashTable[ sighash( sig.size(), sig.optCount(), sig.dontFragment(), sig.quirks() ) ] = ptr;
		}
		else
		{
			while( hashptr->next() != NULL )
				hashptr = hashptr->next();
			hashptr->setNext( ptr );
		}
	}
}

const std::string PacketFingerprint::trim(const std::string& pString,
                       const std::string& pWhitespace, 
											 const std::string& commentChars)
{
	//Take out comment Characters.
	std::string newString;
	const size_t comment = pString.find_first_of( commentChars );
	if( comment != std::string::npos )
	{
		newString = pString.substr( 0, comment );
	}
	
	//Deal with whitespace...
	const size_t beginStr = newString.find_first_not_of(pWhitespace);
	if (beginStr == std::string::npos)
	{
		// no content
		return "";
	}

	const size_t endStr = newString.find_last_not_of(pWhitespace);
	const size_t range = endStr - beginStr + 1;

	return newString.substr(beginStr, range);
}

Signature PacketFingerprint::fingerprintPacket( const Packet& p ) const 
{
	uint16_t type = PacketFingerprint::NoSignature;

	if( p.transIs<TCP>( 0 ) )
	{
		//Which Database
		if( p.getTrans<TCP>(0).SYN_Flag() ) 
		{
			if( p.getTrans<TCP>(0).ACK_Flag() )
				type = PacketFingerprint::SynAckSignatures;
			else
				type = PacketFingerprint::SynSignatures;
		}
		else if( p.getTrans<TCP>(0).RST_Flag() )
		{
			type = PacketFingerprint::RstSignatures;
		}
		else
			type = PacketFingerprint::OpenSignatures;
		
		//find match :)
		Signature packetSignature( p );

		int sigp_Hash = sighash( packetSignature.size(), packetSignature.optCount(),
				packetSignature.dontFragment(), packetSignature.quirks() );

		std::cout<<type<<std::endl;
		std::cout<<sigp_Hash<<std::endl;

		if( type == PacketFingerprint::SynAckSignatures )
		{					
			Signature* sigptr = synAckHashLookup_.at(sigp_Hash);

			while ( sigptr != NULL)
			{
				if ( packetSignature == *sigptr )
					return *sigptr;
				sigptr = sigptr -> next();
			}	
		}
/*		else// (sigptr == NULL)
		{
			//return default packet?
		}
		*/
		
		else if( type == PacketFingerprint::SynSignatures )
		{
			std::cout<<"***INCOMPLETE***"<<std::endl;
			
			Signature* sigptr = synHashLookup_.at(sigp_Hash);
			while ( sigptr != NULL )
			{
				if ( packetSignature == *sigptr )
					return *sigptr;
				sigptr = sigptr -> next();
			}
		}
		else if( type == PacketFingerprint::RstSignatures )
		{
		}
		else
		{
			//type == PacketFingerprint::OpenSigntures
		}

		//Return signature found...
	}
		//WASN'T TCP
		return Signature();
}

