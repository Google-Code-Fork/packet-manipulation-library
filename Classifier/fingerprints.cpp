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

void setFromFingerPrint( const std::string &fingerPrint )
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
	if( pos != std::string::nops )
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
}

void FingerPrint::setQuirksFingerPrint( std::string fp )
{
}

void FingerPrint::setOSGenreFingerPrint( std::string fp )
{
}

void FingerPrint::setDetailsFingerPrint( std::string fp )
{
	 
}
