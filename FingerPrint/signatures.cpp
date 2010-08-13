#include "signatures.h"
#include "../common/helper.h"
#include "../Packet/Trans/tcpOptions.h"
#include "../Packet/Inet/ipv4.h"
#include "../Packet/Trans/tcp.h"
#include <stdexcept>

const uint32_t Signature::QUIRK_PAST = 0x00000001; //P
const uint32_t Signature::QUIRK_ZEROID = 0x00000002; //Z
const uint32_t Signature::QUIRK_IPOPT = 0x00000004; //I
const uint32_t Signature::QUIRK_URG = 0x00000008; //U
const uint32_t Signature::QUIRK_X2 = 0x00000010; //X
const uint32_t Signature::QUIRK_ACK = 0x00000020; //A
const uint32_t Signature::QUIRK_T2 = 0x00000040; //T
const uint32_t Signature::QUIRK_FLAGS = 0x00000080; //F
const uint32_t Signature::QUIRK_DATA = 0x00000100; //D
const uint32_t Signature::QUIRK_BROKEN = 0x00000200; //!
const uint32_t Signature::QUIRK_RSTACK = 0x00000400; //K
const uint32_t Signature::QUIRK_SEQEQ = 0x00000800; //!
const uint32_t Signature::QUIRK_SEQ0 = 0x00001000; //0

const uint32_t Signature::MOD_CONST = 1;
const uint32_t Signature::MOD_MSS = 2;
const uint32_t Signature::MOD_MTU = 3;
const uint32_t Signature::MOD_NULL = 0;


Signature::Signature( const std::string &fingerPrint ):
	noDetail_(0),
	generic_(0),
	userland_(0),
	windowSize_(0),
	windowSizeMod_(0),
	dontFragment_(0),
	ttl_(0),
	zeroStamp_(0),
	size_(0),
	optCount_(0),
	wsc_(0),
	mss_(0),
	wscMod_(0),
	mssMod_(0),
	quirks_(0),
	configFileLine_(0),
	next_(0)
{
	setFromSignature( fingerPrint );
}

Signature::Signature( const Packet &packet ):
	noDetail_(0),
	generic_(0),
	userland_(0),
	windowSize_(0),
	windowSizeMod_(0),
	dontFragment_(0),
	ttl_(0),
	zeroStamp_(0),
	size_(0),
	optCount_(0),
	wsc_(0),
	mss_(0),
	wscMod_(0),
	mssMod_(0),
	quirks_(0),
	configFileLine_(0),
	next_(0)
{
	setFromPacket( packet );
}

Signature::Signature():
	noDetail_(0),
	generic_(0),
	userland_(0),
	windowSize_(0),
	windowSizeMod_(0),
	dontFragment_(0),
	ttl_(0),
	zeroStamp_(0),
	size_(0),
	optCount_(0),
	wsc_(0),
	mss_(0),
	wscMod_(0),
	mssMod_(0),
	quirks_(0),
	configFileLine_(0),
	next_(0)
{
}

Signature::Signature( const Signature &n )
{
	os_ = n.os_;
	desc_ = n.desc_;
	noDetail_ = n.noDetail_;
	generic_ = n.generic_;
	userland_ = n.userland_;
	windowSize_ = n.windowSize_;
	windowSizeMod_ = n.windowSizeMod_;
	dontFragment_ = n.dontFragment_;
	ttl_ = n.ttl_;
	zeroStamp_ = n.zeroStamp_;
	size_ = n.size_;
	optCount_ = n.optCount_;
	tcpOptions_ = n.tcpOptions_;
	wsc_ = n.wsc_;
	mss_ = n.mss_;
	wscMod_ = n.wscMod_;
	mssMod_ = n.mssMod_;
	quirks_ = n.quirks_;
	configFileLine_ = n.configFileLine_;
	next_ = n.next_;
}

Signature::~Signature()
{
}

void Signature::setFromPacket( const Packet &p )
{
	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		IPv4 ip = p.getInet<IPv4>( 0 );
		TCP tcp = p.getTrans<TCP>( 0 );
		std::vector< SmartPtr< TCPOption > > options = tcp.options();
		uint32_t quirks = 0;

		//set IP stuff
		setDontFragment( ip.dontFragment() );
		setTtl( ip.ttl() );
		//set TCP stuff
		setWindowSize( tcp.windowSize() );

		//set TCP options
		std::vector< uint8_t > tcpOptions;
		std::vector< SmartPtr< TCPOption > >::iterator itr;
		for( itr = options.begin(); itr != options.end(); ++itr )
		{
			uint8_t kind = (*itr)->kind();
			if( kind == TCPOption::MAXIMUM_SEGMENT_SIZE )
			{
				MSSOption* mss = static_cast<MSSOption*>((*itr).data());
				mss_ = mss->mss(); 
			}
		  checkForQuirks( p ); 
			tcpOptions.push_back( kind );
		}
		setTcpOptions( tcpOptions );
	}
}

void Signature::checkForQuirks( const Packet &packet ) 
{
	quirks_ = 0;

	//TODO: check for more than just SYN packet quirks.

	if( quirkPast( packet ) )
		quirks_ |= QUIRK_PAST;

	if( quirkZeroId( packet ) )
		quirks_ |= QUIRK_ZEROID;

	if( quirkIPOpt( packet ) )
		quirks_ |= QUIRK_IPOPT;

	if( quirkUrg( packet ) )
		quirks_ |= QUIRK_URG;

	if( quirkX2( packet ) )
		quirks_ |= QUIRK_X2;

	if( quirkAck( packet ) )
		quirks_ |= QUIRK_ACK;

	if( quirkT2( packet ) )
		quirks_ |= QUIRK_T2;

	if( quirkFlags( packet ) )
		quirks_ |= QUIRK_FLAGS;

	if( quirkData( packet ) )
		quirks_ |= QUIRK_DATA;
}

bool Signature::quirkPast( const Packet &p ) const
{
	//Checks for options after EOL
	
	bool eol = false;

	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		IPv4 ip = p.getInet<IPv4>( 0 );
		TCP tcp = p.getTrans<TCP>( 0 );
		std::vector< SmartPtr< TCPOption > > options = tcp.options();
	
		for( int i = 0; i < options.size(); ++i )
		{
			TCPOption * opt = options[i];

			if( !eol && opt->kind() == TCPOption::END_OF_LIST )
			{
				eol = true; 
			}
			else if( eol && opt->kind() != TCPOption::END_OF_LIST )
			{
				return true;
			}
		} 
	}
	return false;
}

bool Signature::quirkZeroId( const Packet &p ) const
{
	if( p.inetIs< IPv4 >( 0 ) )
	{
		return p.getInet<IPv4>( 0 ).identification() == 0;
	}
	return false;
}

bool Signature::quirkIPOpt( const Packet &p ) const
{
	//TODO: IP packets can't currently have options! :(
	
	if( p.inetIs< IPv4 >( 0 ) )
	{
		IPv4 ip = p.getInet< IPv4 >( 0 );
		
	}
}

bool Signature::quirkUrg( const Packet &p ) const 
{
	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		TCP tcp = p.getTrans<TCP>( 0 );
		return tcp.URG_Flag();
	}
}

bool Signature::quirkX2( const Packet &p ) const
{
	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		TCP tcp = p.getTrans<TCP>( 0 );
		if( tcp.x2() != 0 )
			return true;
	}
	return false;
}

bool Signature::quirkAck( const Packet &p ) const
{
	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		TCP tcp = p.getTrans<TCP>( 0 );
		if( tcp.acknowledgementNumber() != 0 )
			return true;
	}
	return false;
}

bool Signature::quirkT2( const Packet &p ) const
{
	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		TCP tcp = p.getTrans<TCP>( 0 );
		std::vector< SmartPtr< TCPOption > > options = tcp.options();
		for( int i = 0; i < options.size(); ++i )
		{
			if( options[i]->kind() == TCPOption::TIME_STAMP_OPTION )
			{
				TimeStampOption* tsopt = static_cast<TimeStampOption*>(options[i].data());
				if( tsopt->tsecr() != 0 )
					return true;
			}
		}
	}

	return false;
}


bool Signature::quirkFlags( const Packet &p ) const 
{
	if( p.inetIs< IPv4 >( 0 ) && p.transIs< TCP >( 0 ) )
	{
		TCP tcp = p.getTrans<TCP>( 0 );
		if( tcp.URG_Flag() || tcp.PSH_Flag() )
			return true;
	}
	return false;
}

bool Signature::quirkData( const Packet &p ) const 
{
	if( p.appSize() > 0 ) 
		return true;
	return false;
}
void Signature::setFromSignature( const std::string &fingerPrint )
{
	std::string windowSignature;
	std::string ttlSignature;
	std::string dontFragmentSignature;
	std::string synPacketSizeSignature;
	std::string optionsSignature;
	std::string quirksSignature;
	std::string osGenreSignature;
	std::string detailsSignature;


	int start = 0;
	
	//Window Size
	int pos = fingerPrint.find( ':' );
	if( pos != std::string::npos )
	{
		windowSignature = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//TTL
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		ttlSignature = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//Don't Fragment
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		dontFragmentSignature = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//Syn Packet size
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		synPacketSizeSignature = fingerPrint.substr( start , pos - start );
		start = pos + 1;
	}

	//Options
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		optionsSignature = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//Quirks
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		quirksSignature = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//OS Genre
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		osGenreSignature = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}	
	//Details
	detailsSignature = fingerPrint.substr( start );

	setWindowSignature( windowSignature );
	setTTLSignature( ttlSignature );
	setDontFragmentSignature( dontFragmentSignature );
	setSynSizeSignature( synPacketSizeSignature );
	setOptionsSignature( optionsSignature );
	setQuirksSignature( quirksSignature );
	setOSGenreSignature( osGenreSignature );
	setDetailsSignature( detailsSignature );
}

void Signature::setWindowSignature( std::string fp )
{
	if( fp.at(0) == '*' )
	{ //wildcard
		windowSize_ = 1;
		windowSizeMod_ = MOD_CONST;
	}
	else if ( tolower( fp.at(0) ) == 's' )
	{ //Multiple of MSS
		windowSizeMod_ = MOD_MSS;
		windowSize_ = ss_atoi<int>(fp.substr(1));
	}
	else if ( tolower( fp.at(0) )  == 't' )
	{
		windowSizeMod_ = MOD_MTU;
		windowSize_ = ss_atoi<int>( fp.substr(1) );
	}
	else if ( fp.at(0)  == '%' )
	{
		windowSizeMod_ = MOD_CONST;
		windowSize_ = ss_atoi<int>( fp.substr( 1 ) );
	}
	else
	{
		windowSizeMod_ = MOD_NULL;
		windowSize_ = ss_atoi<int>( fp );
	}
}

void Signature::setTTLSignature( std::string fp )
{
  ttl_ = ss_atoi<uint32_t>(fp);	
}

void Signature::setDontFragmentSignature( std::string fp )
{
	dontFragment_ = static_cast<uint8_t>(ss_atoi<uint32_t>(fp)); 
}

void Signature::setSynSizeSignature( std::string fp )
{
	size_ = ss_atoi<uint32_t>(fp);
}

void Signature::setOptionsSignature( std::string fp )
{
	zeroStamp_ = true; //only matters if timestamp option is set
	std::string::iterator itr;
	for( itr = fp.begin(); itr != fp.end(); ++itr )
	{
		switch( tolower(*itr) )
		{

			case 'n': //NOOP
				tcpOptions_.push_back( TCPOption::NO_OPERATION );
				break;

			case 'e': //EOL
				tcpOptions_.push_back( TCPOption::END_OF_LIST );
				//TODO: might want to check if we are really at the end of list?
				break;

			case 's': //SACKOK
				tcpOptions_.push_back( TCPOption::SACK_PERMITTED );
				break;

			case 't': //TIMESTAMP
				tcpOptions_.push_back( TCPOption::TIME_STAMP_OPTION );
				if( *(itr + 1) != '0' )
					zeroStamp_ = false;
				break;

			case 'w': //window Scale
				tcpOptions_.push_back( TCPOption::WINDOW_SCALE );
				if( *(itr + 1) == '*' ) //Wildcard
				{
					wsc_ = 1;
					wscMod_ = MOD_CONST;
				}
				else if ( *(itr + 1) == '%' )
				{
					wscMod_ = MOD_CONST;
					wsc_ = ss_atoi<uint32_t>( fp.substr( itr+2 - fp.begin() ) );
				}
				else
				{
					wsc_ = ss_atoi<uint32_t>( fp.substr( itr+2 - fp.begin() ) );
				}
				break;

			case 'm': //Max Segment Size
				tcpOptions_.push_back( TCPOption::MAXIMUM_SEGMENT_SIZE );
				if( *(itr + 1) == '*' ) //Wildcard
				{
					mss_ = 1;
					mssMod_ = MOD_CONST;
				}
				else if ( *(itr + 1) == '%' )
				{
					mssMod_ = MOD_CONST;
					mss_ = ss_atoi<uint32_t>( fp.substr( itr+2 - fp.begin() ) );
				}
				else
				{
					mss_ = ss_atoi<uint32_t>( fp.substr( itr+2 - fp.begin() ) );
				}
				break;

			case '?': //Unknown (not really just not one of the ones we look at
				tcpOptions_.push_back( static_cast<uint8_t>( ss_atoi<uint16_t>( fp.substr( itr+1 - fp.begin() ) ) ) );
						break;
		
			default:
				throw std::runtime_error( "Unknown TCP option in config" );
		};
	}
}

void Signature::setQuirksSignature( std::string fp )
{
	quirks_ = 0;
	/*
	 * Quirks section is usually an empty list ('.') of oddities or bugs of this 
	 * particular stack. List items are not separated in any way. Possible values:
	 *
	 * P     - options past EOL,
	 * Z - zero IP ID,
	 * I - IP options specified,
	 * U - urg pointer non-zero,
	 * X     - unused (x2) field non-zero,
	 * A - ACK number non-zero,
	 * T     - non-zero second timestamp,
	 * F     - unusual flags (PUSH, URG, etc),
	 * D     - data payload,
	 * !     - broken options segment.
	 */

	std::string::iterator itr;
	for( itr = fp.begin(); itr != fp.end(); ++itr )
	{
		switch( tolower(*itr) )
		{
			case 'p': quirks_ |= QUIRK_PAST;
								break;
			case 'z': quirks_ |= QUIRK_ZEROID;
								break;
			case 'i': quirks_ |= QUIRK_IPOPT;
								break;
			case 'u': quirks_ |= QUIRK_URG;
								break;
			case 'x': quirks_ |= QUIRK_X2;
								break;
			case 'a': quirks_ |= QUIRK_ACK;
								break;
			case 't': quirks_ |= QUIRK_T2;
								break;
			case 'f': quirks_ |= QUIRK_FLAGS;
								break;
			case 'd': quirks_ |= QUIRK_DATA;
								break;
			case '!': quirks_ |= QUIRK_BROKEN;
								break;
			case 'k': quirks_ |= QUIRK_RSTACK;
								break;
			case 'q': quirks_ |= QUIRK_SEQEQ;
								break;
			case '0': quirks_ |= QUIRK_SEQ0;
								break;
		}
	}
}

void Signature::setOSGenreSignature( std::string fp )
{
	noDetail_ = false;
	generic_ = false;
	userland_ = false;
	/*  from the p0f.fp finger print file...
	 *
	 * If OS genre starts with '*', p0f will not show distance, link type
	 * and timestamp data. It is useful for userland TCP/IP stacks of
	 * network scanners and so on, where many settings are randomized or
	 * bogus.
	 *
	 * If OS genre starts with @, it denotes an approximate hit for a group
	 * of operating systems (signature reporting still enabled in this case). 
	 * Use this feature at the end of this file to catch cases for which
	 * you don't have a precise match, but can tell it's Windows or FreeBSD
	 * or whatnot by looking at, say, flag layout alone.
	 *
	 * If OS genre starts with - (which can prefix @ or *), the entry is
	 * not considered to be a real operating system (but userland stack
	 * instead). It is important to mark all scanners and so on with -,
	 * so that they are not used for masquerade detection (also add this
	 * prefix for signatures of application-induced behavior, such as
	 * increased window size with Opera browser).
	 */

	switch( fp.at(0) )
  { 
		case '*': 
			noDetail_ = true;
			fp = fp.substr( 1 ); //everything after '*'
			break;
		case '@':
			generic_ = true;
			fp = fp.substr( 1 ); //everything else
			break;
		case '-':
			userland_ = true;
			fp = fp.substr( 1 ); //everything else
	}

	os_ = fp;
}

void Signature::setDetailsSignature( std::string fp )
{
	desc_ = fp;
}

bool Signature::operator== ( const Signature &packetSignature ) const
{
  if( dontFragment_ == packetSignature.dontFragment_ &&
			ttl_ == packetSignature.ttl_ &&
			quirks_ == packetSignature.quirks_ &&
			optCount_ == packetSignature.optCount_ )
	{
		if( windowSizeMatch( packetSignature ) &&
				tcpOptionMatch( packetSignature ) )
			return true;
	}
	return false;
}

bool Signature::windowSizeMatch( const Signature &packetSignature ) const 
{
	if( wscMod_ == MOD_CONST )
	{
		if( packetSignature.wsc_ % wsc_ == 0 )
			return true;
	}
	else if( wscMod_ == MOD_MSS )
	{
		if( packetSignature.wsc_ % packetSignature.mss_ == 0 )
		{
			if( packetSignature.wsc_ / packetSignature.mss_ == wsc_ )
				return true;
		}
	}
	else if( wscMod_ == MOD_MTU )
	{
		int segmentSize = 1460; //Maximum MSS for Ethernet V2 (Most Common)
		if( packetSignature.mss_ > 0 )
			segmentSize = packetSignature.mss_;
		int mtu = segmentSize + 40; 
		if( packetSignature.wsc_ % mtu == 0 )
		{
			if( packetSignature.wsc_ / mtu == wsc_ )
				return true;
		}
	}
	else if ( wscMod_ == MOD_NULL )
	{
		return wsc_ == packetSignature.wsc_;
	}
	return false;
}

bool Signature::tcpOptionMatch( const Signature &packetSignature ) const
{
	if( tcpOptions_.size() != packetSignature.tcpOptions_.size() )
		return false;

	for( int i = 0; i < tcpOptions_.size(); ++i )
	{
		if( tcpOptions_[i] != packetSignature.tcpOptions_[i] )
			return false;
	}

	return true;
}
