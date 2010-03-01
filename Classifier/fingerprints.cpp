#include "fingerprints.h"


const uint32_t FingerPrint::QUIRK_PAST = 0x00000001; //P
const uint32_t FingerPrint::QUIRK_ZEROID = 0x00000002; //Z
const uint32_t FingerPrint::QUIRK_IPOPT = 0x00000004; //I
const uint32_t FingerPrint::QUIRK_URG = 0x00000008; //U
const uint32_t FingerPrint::QUIRK_X2 = 0x00000010; //X
const uint32_t FingerPrint::QUIRK_ACK = 0x00000020; //A
const uint32_t FingerPrint::QUIRK_T2 = 0x00000040; //T
const uint32_t FingerPrint::QUIRK_FLAGS = 0x00000080; //F
const uint32_t FingerPrint::QUIRK_DATA = 0x00000100; //D
const uint32_t FingerPrint::QUIRK_BROKEN = 0x00000200; //!
const uint32_t FingerPrint::QUIRK_RSTACK = 0x00000400; //K
const uint32_t FingerPrint::QUIRK_SEQEQ = 0x00000800; //!
const uint32_t FingerPrint::QUIRK_SEQ0 = 0x00001000; //0


FingerPrint::FingerPrint( const std::string &fingerPrint ):
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
	setFromFingerPrint( fingerPrint );
}

FingerPrint::FingerPrint():
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

FingerPrint::FingerPrint( const FingerPrint &n )
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

FingerPrint::~FingerPrint()
{
}

void FingerPrint::setFromFingerPrint( const std::string &fingerPrint )
{
	std::string windowFingerPrint;
	std::string ttlFingerPrint;
	std::string dontFragmentFingerPrint;
	std::string synPacketSizeFingerPrint;
	std::string optionsFingerPrint;
	std::string quirksFingerPrint;
	std::string osGenreFingerPrint;
	std::string detailsFingerPrint;


	int start = 0;
	
	//Window Size
	int pos = fingerPrint.find( ':' );
	if( pos != std::string::npos )
	{
		windowFingerPrint = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//TTL
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		ttlFingerPrint = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//Don't Fragment
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		dontFragmentFingerPrint = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//Syn Packet size
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		synPacketSizeFingerPrint = fingerPrint.substr( start , pos - start );
		start = pos + 1;
	}

	//Options
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		optionsFingerPrint = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//Quirks
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		quirksFingerPrint = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}

	//OS Genre
	pos = fingerPrint.find( ':', start );
	if( pos != std::string::npos )
	{
		osGenreFingerPrint = fingerPrint.substr( start, pos - start );
		start = pos + 1;
	}	
	//Details
	detailsFingerPrint = fingerPrint.substr( start );

	setWindowFingerPrint( windowFingerPrint );
	setTTLFingerPrint( ttlFingerPrint );
	setDontFragmentFingerPrint( dontFragmentFingerPrint );
	setSynSizeFingerPrint( synPacketSizeFingerPrint );
	setOptionsFingerPrint( optionsFingerPrint );
	setQuirksFingerPrint( quirksFingerPrint );
	setOSGenreFingerPrint( osGenreFingerPrint );
	setDetailsFingerPrint( detailsFingerPrint );
}

void FingerPrint::setWindowFingerPrint( std::string fp )
{
}

void FingerPrint::setTTLFingerPrint( std::string fp )
{
}

void FingerPrint::setDontFragmentFingerPrint( std::string fp )
{
}

void FingerPrint::setSynSizeFingerPrint( std::string fp )
{
}

void FingerPrint::setOptionsFingerPrint( std::string fp )
{
	zeroStamp_ = true;
	//tcp options - . denotes no options
	if( fp == "." )
		tcpOptions_.clear();
	else
		tcpOptions_ = fp;
}

void FingerPrint::setQuirksFingerPrint( std::string fp )
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
		switch( *itr )
		{
			case 'p':
			case 'P': quirks_ |= QUIRK_PAST;
								break;
			case 'z':
			case 'Z': quirks_ |= QUIRK_ZEROID;
								break;
			case 'i':
			case 'I': quirks_ |= QUIRK_IPOPT;
								break;
			case 'u':
			case 'U': quirks_ |= QUIRK_URG;
								break;
			case 'x':
			case 'X': quirks_ |= QUIRK_X2;
								break;
			case 'a':
			case 'A': quirks_ |= QUIRK_ACK;
								break;
			case 't':
			case 'T': quirks_ |= QUIRK_T2;
								break;
			case 'f':
			case 'F': quirks_ |= QUIRK_FLAGS;
								break;
			case 'd':
			case 'D': quirks_ |= QUIRK_DATA;
								break;
			case '!': quirks_ |= QUIRK_BROKEN;
								break;
			case 'k':
			case 'K': quirks_ |= QUIRK_RSTACK;
								break;
			case 'q':
			case 'Q': quirks_ |= QUIRK_SEQEQ;
								break;
			case '0': quirks_ |= QUIRK_SEQ0;
								break;
		}
	}
}

void FingerPrint::setOSGenreFingerPrint( std::string fp )
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
		case '-':
			userland_ = true;
			fp = fp.substr( 1 ); //everything else
	}

	os_ = fp;
}

void FingerPrint::setDetailsFingerPrint( std::string fp )
{
	desc_ = fp;
}
