#include "dnsPacket.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <arpa/inet.h>
#include "../../common/stringUtils.h"

DNSPacket::DNSPacket()
{
}

DNSPacket::DNSPacket( const uint8_t *data, int size )
{
	std::vector< uint8_t > packet;
	for( int i = 0; i < size; ++i )
	{
		packet.push_back( data[i] );
	}
	init( packet );
}

DNSPacket::DNSPacket( const std::vector<uint8_t> packet )
{
  init( packet );
}

DNSPacket::DNSPacket( const PacketBuffer &packet )
{
	init( packet.vector() );
}

DNSPacket::DNSPacket( const DNSPacket &n )
{
  answers_ = n.answers_;
  authorities_ = n.authorities_;
  additionals_ = n.additionals_;
  questions_ = n.questions_;
  header_ = n.header_;
}

DNSPacket::~DNSPacket()
{
  //nothing created on the heap...
}

void DNSPacket::init( std::vector<uint8_t> packet )
{
  //Because we have no way to easily test to see the correct length of the
  //packet we use .at() instead of [] notation because it has bounds checking.
  //Malformed packets will throw exceptions;

  uint16_t tmp = 0;
  //identification
	if( packet.size() > 2 )
	{
		tmp = packet.at(0);
		tmp <<=8;
		tmp |= packet.at(1);
		header_.identification = tmp;
	}
	else
		return;

  //flags
	if( packet.size() > 4 )
	{
		tmp = packet.at(2);
		tmp <<= 8;
		tmp |= packet.at(3);// & 0x00FF;
		header_.flags = tmp;
	}
	else
		return;

  //numberOfQuestions
	if( packet.size() > 12 )
	{
		tmp = packet.at(4);
		tmp <<= 8;
		tmp |= packet.at(5);
		header_.numberQuestions = tmp; 
	}
	else
		return;

  //numberOFAnswers
	if( packet.size() > 8 )
	{
		tmp = packet.at(6);
		tmp <<=8;
		tmp |= packet.at(7);
		header_.numberAnswers = tmp;
	}
	else
		return;

  //numberOfAuthority
	if( packet.size() > 10 )
	{
		tmp = packet.at(8);
		tmp <<= 8;
		tmp |= packet.at(9);
		header_.numberAuthority = tmp;
	}
	else
		return;

  //number of additional
	if( packet.size() > 12 )
	{
		tmp = packet.at(10);
		tmp <<= 8;
		tmp |= packet.at(11);
		header_.numberAdditional = tmp;
	}
	else
		return;
  

  uint16_t index = 12;
  for( int i = 0; i < header_.numberQuestions; ++i )
  {
		DNSQuestion question;
		if( index < packet.size() )
		{
			question.setQueryName( domainParser( packet, index ));
		}
		else
			return;
			
    //query type
    if( static_cast<uint32_t>( index + 1 ) < packet.size() )
		{
			tmp = packet.at(index);
			tmp <<=8;
			tmp |= packet.at(++index);
			question.setType( tmp );
		}
		else 
			return;

    //query class
    if( static_cast<uint32_t>(index + 2) < packet.size() )
		{
			tmp = packet.at( ++index );
			tmp <<= 8;
			tmp |= packet.at( ++index );
			question.setDnsClass( tmp );
		}
		else
			return;

    questions_.push_back( question );
    if( static_cast<uint32_t>(index + 1) < packet.size() )
			++index;
		else
			return;
  }

  //std::cerr << "Parsed Questions" << std::endl;

  for( int i = 0; i < header_.numberAnswers; ++i )
  {
    //std::cerr << "index: " << index << std::endl;
    //std::cerr << "packet[index]" << std::hex << static_cast<int>(packet[index]) << std::dec << std::endl;
    answers_.push_back( dnsResponseParser(packet, index) );
    //std::cerr << "Iteration" << std::endl;
  }

  //std::cerr << "Parsed Answers" << std::endl;

  for( int i = 0; i < header_.numberAuthority; ++i )
  {
    authorities_.push_back( dnsResponseParser( packet, index ) );
  }

  //std::cerr << "Parsed Authority" << std::endl;

  for( int i = 0; i < header_.numberAdditional; ++i )
  {
    additionals_.push_back( dnsResponseParser( packet, index ) );
  }

  //std::cerr << "Parsed whole thing" << std::endl;
}

DNSRecord DNSPacket::dnsResponseParser( std::vector<uint8_t> packet, uint16_t &index )
{
	/***************************************************************************
	 * Checking of index size is needed in case of only partial packet captures
	 * *************************************************************************/
  uint16_t tmp;
  DNSRecord response;
  response.setDomainName( domainParser( packet, index ) );

  //std::cerr << "domain name: " << response.domainName << std::endl;
  //dns type
  if( static_cast<uint32_t>(index + 2) < packet.size() )
	{
		tmp = packet.at(index);
		tmp <<= 8;
		tmp |= packet.at( ++index );
		response.setType( tmp );
	}
	else
	{
		index = packet.size();
		return response;
	}

  //dnsClass
  if( static_cast<uint32_t>(index + 2) < packet.size() )
	{
		tmp = packet.at( ++index );
		tmp <<= 8;
		tmp |= packet.at( ++index );
		response.setDnsClass( tmp );
	}
	else
	{
		index = packet.size();
		return response;
	}

  //timeToLive 4 bytes
  if( static_cast<uint32_t>(index + 4) < packet.size() )
	{
		tmp = packet.at( ++index );
		tmp <<= 8;
		tmp |= packet.at( ++index );
		tmp <<= 8;
		tmp |= packet.at( ++index );
		tmp <<= 8;
		tmp |= packet.at( ++index );
		response.setTimeToLive( tmp );
	}
	else
	{
		index = packet.size();
		return response;
	}

  //resource data length

	uint16_t dataLength = 0;
  if( static_cast<uint32_t>(index + 2) < packet.size() )
	{
		tmp = packet.at( ++index );
		tmp <<= 8;
		tmp |= packet.at( ++index );
		dataLength = tmp;
	}
	else
	{
		index = packet.size();
		return response;
	}

  //std::cerr << "dataLength: " << response.dataLength << std::endl;

  //data storage
	if( index + dataLength < packet.size() )
	{
		std::vector< uint8_t > data;
		for( int k = 0; k < dataLength; ++k )
		{
			//response.pushDataBack( packet.at( ++index ));
			data.push_back( packet.at( ++index ) );
		}
		response.setData( data );
		index++;
	}
	else
	{
		index = packet.size();
		return response;
	}

  return response;
}

std::string DNSPacket::domainParser( std::vector<uint8_t> packet, uint16_t &index )
{
  //note about compression: (from TCP/IP Illustrated Vol. 1 pg. 197)
  //There can be many repetitions of domain names in a reply, so a compression
  //scheme is used... The compression scheme is simple. Anywhere the label
  //portion of a domain name can occur, the single count byte (which is between
  //0 - 63) has its two high-order bits turned on instead. This means it is a
  //16-bi pointer and not an 8 bit count byte. The 14 bits that follow in the
  //pointer specify an offset in the DNS message of a label to with. ( The
  //offset of the first byte in the identification field is 0.) We purposely
  //said that this pointer can occur whereever a label can occur, not just where
  //a complete domain name can occur, since it's possible for a pointer to form
  //either a complete domain name or just the ending portion of a name. 

  std::string domain;
	if( index >= packet.size() )
		return domain;
  while( packet.at(index) != 0 )
  {
    int size = packet[index]; //safe because we used at above
    //check for compression
    if( size & 0xC0 ) //compression used b/c two high bits on.
    {
      if( static_cast<uint32_t>( index + 2 ) < packet.size() )
			{
				uint16_t offset = size & 0x3F;
				offset <<= 8;
				offset |= packet.at( ++index );
				domain += domainParser( packet, offset );
				++index;
			}
      return domain;
    }

    if( static_cast<uint32_t>(index + size + 1) < packet.size() )
		{
			for( int k = 0; k < size; ++k )
			{
				index++;
				domain.push_back( packet.at( index ) );
			}
			index++;
		}
		else
		{
			index = packet.size();
			return domain;
		}


    if( packet.at(index) != 0 )
      domain.push_back( '.' );
		
    if( static_cast<uint32_t>(index + 1) >= packet.size() )
			return domain;
  }
  index++;

  return domain;
}

std::vector< uint8_t > DNSPacket::data() const
{
	//This must ***NOT*** be capable of generating malformed dns packets
	
	std::vector< uint8_t > packet;

  //header
  //identifacation 2 bytes
  packet.push_back( static_cast< uint8_t >( header_.identification >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.identification & 0x00FF ) );
  //flags 2 bytes
  packet.push_back( static_cast< uint8_t >( header_.flags >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.flags & 0x00FF ) );
  //numberOfQuestions
	uint16_t numQuestions = static_cast< uint16_t >( questions_.size() );
  packet.push_back( static_cast< uint8_t >( numQuestions >> 8 ) );
  packet.push_back( static_cast< uint8_t >( numQuestions & 0x00FF ) );
  //numberAnswers
	uint16_t numAnswers = static_cast< uint16_t >( answers_.size() );
  packet.push_back( static_cast< uint8_t >( numAnswers >> 8 ) );
  packet.push_back( static_cast< uint8_t >( numAnswers & 0x00FF ) );
  //numberAuthority
	uint16_t numAuthority = static_cast< uint16_t >( authorities_.size() );
  packet.push_back( static_cast< uint8_t >( numAuthority >> 8 ) );
  packet.push_back( static_cast< uint8_t >( numAuthority & 0x00FF ) );
  //numberAdditional
	uint16_t numAdditional = static_cast< uint16_t >( additionals_.size() );
  packet.push_back( static_cast< uint8_t >( numAdditional >> 8 ) );
  packet.push_back( static_cast< uint8_t >( numAdditional & 0x00FF ) );
	
	for( int i = 0; i < numQuestions; ++i )
	{
		formatQuestion( packet, questions_[i] );
	}

	for( int i = 0; i < numAnswers; ++i )
	{
//		formatRecord( packet, answers_[i] );
	}

	for( int i = 0; i < numAuthority; ++i )
	{
  //	formatRecord( packet, authorities_[i] );
	}

	for( int i = 0; i < numAdditional; ++i )
	{
    //formatRecord( packet, additionals_[i] );
	}

	return packet;
}


/*void DNSPacket::formatRecord( std::vector< uint8_t > &packet, const DNSRecord &record ) const
{


}*/

void DNSPacket::formatQuestion( std::vector< uint8_t > &packet, const DNSQuestion &question ) const
{
	formatURL( packet, question.queryName() );

  packet.push_back( static_cast< uint8_t >( question.type() >> 8 ) );
  packet.push_back( static_cast< uint8_t >( question.type() & 0x00FF ) );
  
	packet.push_back( static_cast< uint8_t >( question.dnsClass() >> 8 ) );
  packet.push_back( static_cast< uint8_t >( question.dnsClass() & 0x00FF ) );

}

void DNSPacket::formatURL( std::vector< uint8_t > &packet, const std::string &url ) const
{
	std::vector< std::string > stringList = split( url, '.' );
	for( uint32_t i = 0; i < stringList.size(); ++i )
	{
		std::string component = stringList[i];
		packet.push_back( static_cast<uint8_t>( component.size() ) );
		for( uint32_t k = 0; k < component.size(); ++k )
		{
			packet.push_back( component[k] );
		}
	}
	packet.push_back( 0x00 );
}

PacketBuffer DNSPacket::makePacket() const
{
	return PacketBuffer( data() );
}

/*
std::vector<uint8_t> DNSPacket::generatePacket( ) 
{
	// THIS ***CAN**** generate malformed DNS packets.
	
  //In our scheme we will not use compression. This can be added later for
  //higher efficiency.
  
  //Additionally it is possible to create malformed dns packets with this code
  //and this is intensional. 
  //This is possible because the user sets all the feilds and there is no
  //corelation between the headers number of feilds and the actual questions
  //answers, etc...
  
  std::vector<uint8_t> packet;
 
  //header
  //identifacation 2 bytes
  packet.push_back( static_cast< uint8_t >( header_.identification >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.identification & 0x00FF ) );
  //flags 2 bytes
  packet.push_back( static_cast< uint8_t >( header_.flags >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.flags & 0x00FF ) );
  //numberOfQuestions
  packet.push_back( static_cast< uint8_t >( header_.numberQuestions >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.numberQuestions & 0x00FF ) );
  //numberAnswers
  packet.push_back( static_cast< uint8_t >( header_.numberAnswers >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.numberAnswers & 0x00FF ) );
  //numberAuthority
  packet.push_back( static_cast< uint8_t >( header_.numberAuthority >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.numberAuthority & 0x00FF ) );
  //numberAdditional
  packet.push_back( static_cast< uint8_t >( header_.numberAdditional >> 8 ) );
  packet.push_back( static_cast< uint8_t >( header_.numberAdditional & 0x00FF ) );

  std::vector<uint8_t> tmp;
  //questions...
  std::vector< DNSQuestion >::const_iterator qitr;
  for( qitr = questions_.begin(); qitr != questions_.end(); ++qitr )
  {
    //queryName
    tmp = generateEncodedDomainName( qitr->queryName );
    std::copy( tmp.begin(), tmp.end(), std::back_inserter( packet ) );
    //packet += generateEncodedDomainName( qitr->queryName );
    //dnsType
    packet.push_back( static_cast< uint8_t >( qitr->dnsType >> 8 ) );
    packet.push_back( static_cast< uint8_t >( qitr->dnsType & 0x00FF ) );
    //dnsClass
    packet.push_back( static_cast< uint8_t >( qitr->dnsClass >> 8 ) );
    packet.push_back( static_cast< uint8_t >( qitr->dnsClass & 0x00FF ) );
  }

  //answers...
  tmp = encodeDNSResponses( answers_ );
  std::copy( tmp.begin(), tmp.end(), std::back_inserter( packet ) );

  //authority
  //packet += encodeDNSResponses( authorities_ );
  tmp = encodeDNSResponses( authorities_ );
  std::copy( tmp.begin(), tmp.end(), std::back_inserter( packet ) );

  //additionals
  //packet += encodeDNSResponses( additionals_ );
  tmp = encodeDNSResponses( additionals_ );
  std::copy( tmp.begin(), tmp.end(), std::back_inserter( packet ) );

  return packet;

}
*/

std::vector<uint8_t> DNSPacket::encodeDNSRecord( const std::vector< DNSRecord > &responses )
{
  std::vector<uint8_t> tmp;
  std::vector<uint8_t> packet;
  std::vector< DNSRecord >::const_iterator ritr;
  for( ritr = responses.begin(); ritr != responses.end(); ++ritr )
  {
    //domain name
    //packet += generateEncodedDomainName( ritr->domainName );
    tmp = generateEncodedDomainName( ritr->domainName() );
    std::copy( tmp.begin(), tmp.end(), std::back_inserter(packet) );
    //dnsType
    packet.push_back( static_cast< uint8_t >( ritr->type() >> 8 ) );
    packet.push_back( static_cast< uint8_t >( ritr->type() & 0x00FF ) );
    //dnsClass
    packet.push_back( static_cast< uint8_t >( ritr->dnsClass() >> 8 ) );
    packet.push_back( static_cast< uint8_t >( ritr->dnsClass() & 0x00FF ) );
    //timeToLive
    packet.push_back( static_cast< uint8_t >( ritr->timeToLive() >> 24 ) );
    packet.push_back( static_cast< uint8_t >( ( ritr->timeToLive() >> 16 ) & 0x000000FF ) );
    packet.push_back( static_cast< uint8_t >( ( ritr->timeToLive() >> 8 ) & 0x000000FF ) );
    packet.push_back( static_cast< uint8_t >( ritr->timeToLive() & 0x00000FF ) );
    //data length
    packet.push_back( static_cast< uint8_t >( ritr->dataLength() >> 8 ) );
    packet.push_back( static_cast< uint8_t >( ritr->dataLength() & 0x00FF ) );
    //data
    std::vector< uint8_t >::const_iterator ditr;
    for( ditr = ritr->data().begin(); ditr != ritr->data().end(); ++ditr )
    {
      packet.push_back( *ditr );
    }
  }

  return packet;
}

std::vector<uint8_t> DNSPacket::generateEncodedDomainName( const std::string &domainName )
{

  //TODO: Add a compressions scheme for greater efficiency in this function.
  std::vector< std::string > domainParts;
  std::string tmp;
  std::string::const_iterator itr;
  for( itr = domainName.begin(); itr != domainName.end(); ++itr )
  {
    if( *itr != '.' )
    {
      tmp.push_back( *itr );
    }
    else
    {
      domainParts.push_back( tmp );
      tmp.clear();
    }
  }
  domainParts.push_back( tmp );
  tmp.clear();

  std::vector<uint8_t> answer;

  std::vector< std::string >::iterator ditr;
  for( ditr = domainParts.begin(); ditr != domainParts.end(); ++ditr )
  {
    uint8_t  domainPartSize = static_cast< uint8_t >( ditr->size() );
    if( domainPartSize > 63 )
      throw std::runtime_error( "Invalid Domain: section larger than 63" ); //max size before setting compression bits
    answer.push_back( domainPartSize );
    for( itr = ditr->begin(); itr != ditr->end(); ++itr )
      answer.push_back( static_cast<uint8_t>( *itr ) );
  }
  answer.push_back( 0 );

  return answer;
}

uint16_t DNSPacket::identificationNumber( ) const
{
  return header_.identification;
}

void DNSPacket::setIdentificationNumber( const uint16_t &id )
{
  header_.identification = id;
}

void DNSPacket::setQRFlag( const bool &isResponse ) 
{
  header_.flags &= ( 0xFFFF ^ QR ); //clear the QR bit
  if( isResponse )
    header_.flags |= QR;
}

bool DNSPacket::qrFlag( )const
{
  return ( header_.flags & QR );
}

void DNSPacket::setOpcodeFlag( const uint8_t &opcode )
{
  uint16_t tmp = opcode & 0x0F; //opcodes are only 4 bits
  tmp <<= 11; //move into the opcode field of the 16 flags
  header_.flags &= ( 0xFFFF ^ OPCODE); //clear the opcode bits
  header_.flags |= tmp;
}

uint8_t DNSPacket::opcodeFlag( ) const
{
  uint8_t tmp = (header_.flags >> 11);
  tmp &= 0x0F; // only the lower bits are the opcode;
  return tmp;
}

void DNSPacket::setAAFlag( const bool &aa )
{
  header_.flags &= ( 0xFFFF ^ AA ); //clear the AA bit
  if( aa )
    header_.flags |= AA; 
}

bool DNSPacket::aaFlag( ) const
{
  return (header_.flags & AA);
}

void DNSPacket::setTCFlag( const bool &tc )
{
  header_.flags &= ( 0xFFFF ^ TC ); //clear TC
  if( tc )
    header_.flags |= TC;
}

bool DNSPacket::tcFlag( ) const
{
  return (header_.flags & TC );
}

void DNSPacket::setRDFlag( const bool &rd )
{
  header_.flags &= ( 0xFFFF ^ RD ); //clear RD
  if( rd )
    header_.flags |= RD;
}

bool DNSPacket::rdFlag( ) const
{
  return (header_.flags & RD );
}

void DNSPacket::setRAFlag( const bool &ra )
{
  header_.flags &= ( 0xFFFF ^ RA ); //clear RA
  if( ra )
    header_.flags |= RA; 
}

bool DNSPacket::raFlag( ) const
{
  return (header_.flags & RA );
}

void DNSPacket::setZeroFlag( const uint8_t &zero )
{
  header_.flags &= ( 0xFFFF ^ ZERO ); //clear zero bits
  uint16_t tmp = zero & 0x07; //only 3 zero bits
  tmp <<= 4; //shift into the right postition
  header_.flags |= tmp;
}

uint8_t DNSPacket::zeroFlag() const
{
  uint8_t tmp = static_cast<uint8_t>( header_.flags & 0x00FF );
  tmp >>= 4;
  tmp &= 0x07;
  return tmp;
}

void DNSPacket::setRcodeFlag( uint8_t rcode )
{
  header_.flags &= ( 0xFFFF ^ RCODE ); //zero the rcode bits
  rcode &= 0x000F; //only 4 bits
  header_.flags |= rcode;
}

uint8_t DNSPacket::rcodeFlag() const
{
  return (header_.flags & RCODE );
}

uint16_t DNSPacket::numberOfQuestions() const
{
  return static_cast< uint16_t >( questions_.size() );
}

uint16_t DNSPacket::numberOfAnswers( ) const
{
  return static_cast< uint16_t >( answers_.size() );
}

uint16_t DNSPacket::numberOfAuthority( ) const
{
  return static_cast< uint16_t >( authorities_.size() );
}

uint16_t DNSPacket::numberOfAdditional( ) const
{
  return static_cast< uint16_t >( additionals_.size() );
}

std::vector< DNSRecord > DNSPacket::answers() const
{
  return answers_;
}

DNSRecord DNSPacket::answer( const int &index ) const
{
	return answers_.at( index );
}

void DNSPacket::setAnswers( std::vector< DNSRecord > answers )
{
  answers_ = answers;
}

void DNSPacket::pushBackAnswer( const DNSRecord &answer ) 
{
	answers_.push_back( answer );
}

std::vector< DNSRecord > DNSPacket::authorities() const
{
  return authorities_;
}

DNSRecord DNSPacket::authority( const int &index ) const
{
	return authorities_.at( index );
}

void DNSPacket::setAuthorities( std::vector< DNSRecord > auth )
{
  authorities_ = auth;
}

void DNSPacket::pushBackAuthority( const DNSRecord &authority )
{
	authorities_.push_back( authority );
}

std::vector< DNSRecord > DNSPacket::additionals() const
{
  return additionals_;
}

DNSRecord DNSPacket::additional( const int &index ) const
{
	return additionals_.at( index );
}

void DNSPacket::setAdditionals( std::vector< DNSRecord > add )
{
  additionals_ = add;
}

void DNSPacket::pushBackAdditional( const DNSRecord &additional ) 
{
	additionals_.push_back( additional );
}

std::vector< DNSQuestion > DNSPacket::questions( ) const
{
  return questions_;
}

DNSQuestion DNSPacket::question( const int &index ) const
{
	return questions_.at( index );
}

void DNSPacket::setQuestions( std::vector<DNSQuestion> questions )
{
  questions_ = questions;
}

void DNSPacket::pushBackQuestion( const DNSQuestion &question ) 
{
	questions_.push_back( question );
}

void DNSPacket::clearAnswers()
{
	answers_.clear();
}

void DNSPacket::clearAuthorities()
{
	authorities_.clear();
}

void DNSPacket::clearAdditionals()
{
	additionals_.clear();
}

void DNSPacket::clearQuestions()
{
	questions_.clear();
}
