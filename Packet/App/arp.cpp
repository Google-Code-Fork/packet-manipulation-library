#include "arp.h"

Arp::Arp() 
{
	header_.hardwareType = hardwaretype::ETHERNET;
	header_.protocolType = protocoltype::IP;
	header_.hardwareSize = hardwaresize::ETHERNET;
	header_.protocolSize = protocolsize::IP;
	header_.opcode = arpopcode::request;
	std::vector< uint8_t > mac;
	for( int i = 0; i < hardwaresize::ETHERNET; ++i )
		mac.push_back( 0x00 );
  senderMacAddress_ = PacketBuffer( mac );
	targetMacAddress_ = PacketBuffer( mac );
	std::vector< uint8_t > ip;
	for( int i = 0; i < protocolsize::IP; ++i )
		ip.push_back( 0x00 );
	senderIPAddress_ = PacketBuffer( ip );
	targetIPAddress_ = PacketBuffer( ip );
}

Arp::Arp( const uint8_t *data, int size )
{
	std::vector< uint8_t > datav;
	for( int i = 0; i < size; ++i )
	{
		datav.push_back( data[i] );
	}
	init( datav );
}

Arp::Arp( const std::vector< uint8_t > packet )
{
	init( packet );
}

Arp::Arp( const Arp &n )
{
	header_ = n.header_;
	senderMacAddress_ = n.senderMacAddress_;
	senderIPAddress_ = n.senderIPAddress_;
	targetMacAddress_ = n.targetMacAddress_;
	targetIPAddress_ = n.targetIPAddress_;
}

Arp& Arp::operator=( const Arp &n )
{
	header_ = n.header_;
	senderMacAddress_ = n.senderMacAddress_;
	senderIPAddress_ = n.senderIPAddress_;
	targetMacAddress_ = n.targetMacAddress_;
	targetIPAddress_ = n.targetIPAddress_;

	return *this;
}

Arp::Arp( const PacketBuffer &packet )
{
	init( packet.vector() );
}

void Arp::init( const std::vector< uint8_t > &packet )
{
	int index = 0;
	if( packet.size() - index > sizeof( header_.hardwareType ) )
	{
		header_.hardwareType = packet[index];
		header_.hardwareType <<= 8;
		header_.hardwareType |= packet[index + 1];
		index += 2;
	}
	else
		return;

	if( packet.size() - index > sizeof( header_.protocolType ) )
	{
		header_.protocolType = packet[index];
		header_.protocolType <<= 8;
		header_.protocolType |= packet[index + 1];
		index += 2;
	}
	else
		return;

	if( packet.size() - index > sizeof( header_.hardwareSize ) )
	{
		header_.hardwareSize = packet[index];
		index += 1;
	}
	else
		return;

	if( packet.size() - index > sizeof( header_.protocolSize ) )
	{
		header_.protocolSize = packet[index];
		index += 1;
	}
	else
		return;
	
	if( packet.size() - index > sizeof( header_.opcode ) )
	{
		header_.opcode = packet[index];
		header_.opcode <<= 8;
		header_.opcode |= packet[index + 1];
		index += 2;
	}
	else
		return;

	if( packet.size() - index > header_.hardwareSize )
	{
		std::vector< uint8_t > buff;
		for( int i = 0; i < header_.hardwareSize; ++i )
		{
			buff.push_back( packet[index + i] );
		}
		senderMacAddress_.setBuffer( buff );
		index += header_.hardwareSize;
	}

	if( packet.size() - index > header_.protocolSize )
	{
		std::vector< uint8_t > buff;
		for( int i = 0; i < header_.protocolSize; ++i )
		{
			buff.push_back( packet[index + i] );
		}
		senderIPAddress_.setBuffer( buff );
		index += header_.protocolSize;
	}
	
	if( packet.size() - index > header_.hardwareSize )
	{
		std::vector< uint8_t > buff;
		for( int i = 0; i < header_.hardwareSize; ++i )
		{
			buff.push_back( packet[index + i] );
		}
		targetMacAddress_.setBuffer( buff );
		index += header_.hardwareSize;
	}

	if( packet.size() - index >= header_.protocolSize )
	{
		std::vector< uint8_t > buff;
		for( int i = 0; i < header_.protocolSize; ++i )
		{
			buff.push_back( packet[index + i] );
		}
		targetIPAddress_.setBuffer( buff );
		index += header_.protocolSize;
	}
}

Arp::~Arp()
{
}

uint16_t Arp::hardwareType() const
{
	return header_.hardwareType;
}

void  Arp::setHardwareType( const uint16_t &hardwareType )
{
	header_.hardwareType = hardwareType;
}

uint16_t Arp::protocolType() const
{
	return header_.protocolType;
}

void Arp::setProtocolType( const uint16_t &protocolType )
{
	header_.protocolType = protocolType;
}

uint8_t Arp::hardwareSize( ) const
{
	return header_.hardwareSize;
}

void Arp::setHardwareSize( const uint8_t &size )
{
	header_.hardwareSize = size;
}

uint8_t Arp::protocolSize( ) const
{
	return header_.protocolSize;
}

void Arp::setProtocolSize( const uint8_t &size )
{
	header_.protocolSize = size;
}

uint16_t Arp::opcode( ) const
{
	return header_.opcode;
}

void Arp::setOpcode( const uint16_t &opcode )
{
	header_.opcode = opcode;
}

PacketBuffer Arp::senderMacAddress() const
{
	return senderMacAddress_;
}

void Arp::setSenderMacAddress( const PacketBuffer &pb )
{
	senderMacAddress_ = pb;
}

PacketBuffer Arp::senderIPAddress() const
{
	return senderIPAddress_;
}

void Arp::setSenderIPAddress( const PacketBuffer &pb )
{
	senderIPAddress_ = pb;
}

PacketBuffer Arp::targetMacAddress( ) const
{
	return targetMacAddress_;
}

void Arp::setTargetMacAddress( const PacketBuffer &pb )
{
	targetMacAddress_ = pb;
}

PacketBuffer Arp::targetIPAddress( ) const
{
	return targetIPAddress_;
}

void Arp::setTargetIPAddress( const PacketBuffer &pb )
{
	targetIPAddress_ = pb;
}

std::vector< uint8_t > Arp::data( ) const
{
	std::vector< uint8_t > data; 

	data.push_back( static_cast<uint8_t>(header_.hardwareType >> 8 ));
	data.push_back( static_cast<uint8_t>(header_.hardwareType & 0x00FF));
	data.push_back( static_cast<uint8_t>(header_.protocolType >> 8 ));
	data.push_back( static_cast<uint8_t>(header_.protocolType & 0x00FF ));
	data.push_back( header_.hardwareSize );
	data.push_back( header_.protocolSize );
	data.push_back( static_cast<uint8_t>( header_.opcode >> 8 ));
	data.push_back( static_cast<uint8_t>( header_.opcode & 0x00FF));

	std::vector< uint8_t > tmp = senderMacAddress_.vector();
  for( uint32_t i = 0; i < tmp.size(); ++i )
	{
		data.push_back( tmp[i] );
	}

	tmp = senderIPAddress_.vector();
  for( uint32_t i = 0; i < tmp.size(); ++i )
	{
		data.push_back( tmp[i] );
	}

	tmp = targetMacAddress_.vector();
  for( uint32_t i = 0; i < tmp.size(); ++i )
	{
		data.push_back( tmp[i] );
	}

	tmp = targetIPAddress_.vector();
  for( uint32_t i = 0; i < tmp.size(); ++i )
	{
		data.push_back( tmp[i] );
	}

	return data;

}

PacketBuffer Arp::makePacket() const
{
	return PacketBuffer( data() );
}

int Arp::size() const
{
	int size = 0;
	size += sizeof( header_ );
	size += senderMacAddress_.size();
	size += senderIPAddress_.size();
	size += targetMacAddress_.size();
	size += targetIPAddress_.size();
	return size;
}
