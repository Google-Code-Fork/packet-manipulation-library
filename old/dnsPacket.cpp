#include "dnsPacket.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
DNSPacket::DNSPacket()
{
}

DNSPacket::DNSPacket( const std::vector<uint8_t> packet )
{
  init( packet );
}

DNSPacket::DNSPacket( const DNSPacket &n )
{
  answers_ = n.answers_;
  authorites_ = n.authorites_;
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
  tmp = packet.at(0);
  tmp <<=8;
  tmp |= packet.at(1);
  header_.identification = tmp;

  //flags
  tmp = packet.at(2);
  tmp <<= 8;
  tmp |= packet.at(3);// & 0x00FF;
  header_.flags = tmp;
  std::cerr<< "packet[2]: 0x" << std::hex << (uint16_t)( packet.at(2) ) << std::dec << std::endl;
  std::cerr<< "flags: 0x" << std::hex << header_.flags << std::endl << std::dec;

  //numberOfQuestions
  tmp = packet.at(4);
  tmp <<= 8;
  tmp |= packet.at(5);
  header_.numberQuestions = tmp; 

  //numberOFAnswers
  tmp = packet.at(6);
  tmp <<=8;
  tmp |= packet.at(7);
  header_.numberAnswers = tmp;

  //numberOfAuthority
  tmp = packet.at(8);
  tmp <<= 8;
  tmp |= packet.at(9);
  header_.numberAuthority = tmp;

  //number of additional
  tmp = packet.at(10);
  tmp <<= 8;
  tmp |= packet.at(11);
  header_.numberAdditional = tmp;
  
  std::cerr << "Parsed Header" << std::endl;

  uint16_t index = 12;
  for( int i = 0; i < header_.numberQuestions; ++i )
  {
    DNSQuestion question;
    question.queryName = domainParser( packet, index );
    
    //query type
    tmp = packet.at(index);
    tmp <<=8;
    tmp |= packet.at(++index);
    question.dnsType = tmp;

    //query class
    tmp = packet.at( ++index );
    tmp <<= 8;
    tmp |= packet.at( ++index );
    question.dnsClass = tmp;

    questions_.push_back( question );
    ++index;
  }

  std::cerr << "Parsed Questions" << std::endl;

  for( int i = 0; i < header_.numberAnswers; ++i )
  {
    std::cerr << "index: " << index << std::endl;
    std::cerr << "packet[index]" << std::hex << static_cast<int>(packet[index]) << std::dec << std::endl;
    answers_.push_back( dnsResponseParser(packet, index) );
    std::cerr << "Iteration" << std::endl;
  }

  std::cerr << "Parsed Answers" << std::endl;

  for( int i = 0; i < header_.numberAuthority; ++i )
  {
    authorites_.push_back( dnsResponseParser( packet, index ) );
  }

  std::cerr << "Parsed Authority" << std::endl;

  for( int i = 0; i < header_.numberAdditional; ++i )
  {
    additionals_.push_back( dnsResponseParser( packet, index ) );
  }

  std::cerr << "Parsed whole thing" << std::endl;
}

DNSResponse DNSPacket::dnsResponseParser( std::vector<uint8_t> packet, uint16_t &index )
{
  uint16_t tmp;
  DNSResponse response;
  response.domainName = domainParser( packet, index );

  //std::cerr << "domain name: " << response.domainName << std::endl;
  //dns type
  tmp = packet.at(index);
  tmp <<= 8;
  tmp |= packet.at( ++index );
  response.dnsType = tmp;

  //dnsClass
  tmp = packet.at( ++index );
  tmp <<= 8;
  tmp |= packet.at( ++index );
  response.dnsClass = tmp;

  //timeToLive 4 bytes
  tmp = packet.at( ++index );
  tmp <<= 8;
  tmp |= packet.at( ++index );
  tmp <<= 8;
  tmp |= packet.at( ++index );
  tmp <<= 8;
  tmp |= packet.at( ++index );
  response.timeToLive = tmp;

  //resource data length

  tmp = packet.at( ++index );
  tmp <<= 8;
  tmp |= packet.at( ++index );
  response.dataLength = tmp;

  //std::cerr << "dataLength: " << response.dataLength << std::endl;

  //data storage
  for( int k = 0; k < response.dataLength; ++k )
  {
    response.data.push_back( packet.at( ++index ));
  }
  index++;

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
  while( packet.at(index) != 0 )
  {
    int size = packet[index]; //safe because we used at above
    //check for compression
    if( size & 0xC0 ) //compression used b/c two high bits on.
    {
      uint16_t offset = size & 0x3F;
      offset <<= 8;
      offset |= packet.at( ++index );
      domain += domainParser( packet, offset );
      ++index;
      return domain;
    }
    for( int k = 0; k < size; ++k )
    {
      index++;
      domain.push_back( packet.at( index ) );
    }
    index++;
    if( packet.at(index) != 0 )
      domain.push_back( '.' );
  }
  index++;

  return domain;
}

std::vector<uint8_t> DNSPacket::generatePacket( )
{
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
  std::vector< DNSQuestion >::iterator qitr;
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
  //packet += encodeDNSResponses( authorites_ );
  tmp = encodeDNSResponses( authorites_ );
  std::copy( tmp.begin(), tmp.end(), std::back_inserter( packet ) );

  //additionals
  //packet += encodeDNSResponses( additionals_ );
  tmp = encodeDNSResponses( additionals_ );
  std::copy( tmp.begin(), tmp.end(), std::back_inserter( packet ) );

  return packet;

}

std::vector<uint8_t> DNSPacket::encodeDNSResponses( std::vector< DNSResponse > responses )
{
  std::vector<uint8_t> tmp;
  std::vector<uint8_t> packet;
  std::vector< DNSResponse >::iterator ritr;
  for( ritr = responses.begin(); ritr != responses.end(); ++ritr )
  {
    //domain name
    //packet += generateEncodedDomainName( ritr->domainName );
    tmp = generateEncodedDomainName( ritr->domainName );
    std::copy( tmp.begin(), tmp.end(), std::back_inserter(packet) );
    //dnsType
    packet.push_back( static_cast< uint8_t >( ritr->dnsType >> 8 ) );
    packet.push_back( static_cast< uint8_t >( ritr->dnsType & 0x00FF ) );
    //dnsClass
    packet.push_back( static_cast< uint8_t >( ritr->dnsClass >> 8 ) );
    packet.push_back( static_cast< uint8_t >( ritr->dnsClass & 0x00FF ) );
    //timeToLive
    packet.push_back( static_cast< uint8_t >( ritr->timeToLive >> 24 ) );
    packet.push_back( static_cast< uint8_t >( ( ritr->timeToLive >> 16 ) & 0x000000FF ) );
    packet.push_back( static_cast< uint8_t >( ( ritr->timeToLive >> 8 ) & 0x000000FF ) );
    packet.push_back( static_cast< uint8_t >( ritr->timeToLive & 0x00000FF ) );
    //data length
    packet.push_back( static_cast< uint8_t >( ritr->dataLength >> 8 ) );
    packet.push_back( static_cast< uint8_t >( ritr->dataLength & 0x00FF ) );
    //data
    std::vector< uint8_t >::iterator ditr;
    for( ditr = ritr->data.begin(); ditr != ritr->data.end(); ++ditr )
    {
      packet.push_back( *ditr );
    }
  }

  return packet;
}

std::vector<uint8_t> DNSPacket::generateEncodedDomainName( std::string domainName )
{

  //TODO: Add a compressions scheme for greater efficiency in this function.
  std::vector< std::string > domainParts;
  std::string tmp;
  std::string::iterator itr;
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

uint16_t DNSPacket::getIdentificationNumber( )
{
  return header_.identification;
}

void DNSPacket::setIdentificationNumber( uint16_t id )
{
  header_.identification = id;
}

void DNSPacket::setFlagsQR( bool isResponse )
{
  header_.flags &= ( 0xFFFF ^ QR ); //clear the QR bit
  if( isResponse )
    header_.flags |= QR;
}

bool DNSPacket::getFlagsQR( )
{
  return ( header_.flags & QR );
}

void DNSPacket::setFlagsOpcode( uint8_t opcode )
{
  uint16_t tmp = opcode & 0x0F; //opcodes are only 4 bits
  tmp <<= 11; //move into the opcode field of the 16 flags
  header_.flags &= ( 0xFFFF ^ OPCODE); //clear the opcode bits
  header_.flags |= tmp;
}

uint8_t DNSPacket::getFlagsOpcode( )
{
  uint8_t tmp = (header_.flags >> 11);
  tmp &= 0x0F; // only the lower bits are the opcode;
  return tmp;
}

void DNSPacket::setFlagsAA( bool aa )
{
  header_.flags &= ( 0xFFFF ^ AA ); //clear the AA bit
  if( aa )
    header_.flags |= AA; 
}

bool DNSPacket::getFlagsAA( )
{
  return (header_.flags & AA);
}

void DNSPacket::setFlagsTC( bool tc )
{
  header_.flags &= ( 0xFFFF ^ TC ); //clear TC
  if( tc )
    header_.flags |= TC;
}

bool DNSPacket::getFlagsTC( )
{
  return (header_.flags & TC );
}

void DNSPacket::setFlagsRD( bool rd )
{
  header_.flags &= ( 0xFFFF ^ RD ); //clear RD
  if( rd )
    header_.flags |= RD;
}

bool DNSPacket::getFlagsRD( )
{
  return (header_.flags & RD );
}

void DNSPacket::setFlagsRA( bool ra )
{
  header_.flags &= ( 0xFFFF ^ RA ); //clear RA
  if( ra )
    header_.flags |= RA; 
}

bool DNSPacket::getFlagsRA( )
{
  return (header_.flags & RA );
}

void DNSPacket::setFlagsZero( uint8_t zero )
{
  header_.flags &= ( 0xFFFF ^ ZERO ); //clear zero bits
  uint16_t tmp = zero & 0x07; //only 3 zero bits
  tmp <<= 4; //shift into the right postition
  header_.flags |= tmp;
}

uint8_t DNSPacket::getFlagsZero()
{
  uint8_t tmp = static_cast<uint8_t>( header_.flags & 0x00FF );
  tmp >>= 4;
  tmp &= 0x07;
  return tmp;
}

void DNSPacket::setFlagsRCode( uint8_t rcode )
{
  header_.flags &= ( 0xFFFF ^ RCODE ); //zero the rcode bits
  rcode &= 0x000F; //only 4 bits
  header_.flags |= rcode;
}

uint8_t DNSPacket::getFlagsRCode()
{
  return (header_.flags & RCODE );
}

uint16_t DNSPacket::getNumberOfQuestions()
{
  return header_.numberQuestions;
}

void DNSPacket::setNumberOfQuestions( uint16_t numQ )
{
  header_.numberQuestions = numQ; 
}

uint16_t DNSPacket::getNumberOfAnswers( )
{
  return header_.numberAnswers;
}

void DNSPacket::setNumberOfAnswers( uint16_t numA )
{
  header_.numberAnswers = numA;
}

uint16_t DNSPacket::getNumberOfAuthority( )
{
  return header_.numberAuthority;
}

void DNSPacket::setNumberOfAuthority( uint16_t numA )
{
  header_.numberAuthority = numA;
}

uint16_t DNSPacket::getNumberOfAdditional( )
{
  return header_.numberAdditional;
}

void DNSPacket::setNumberOfAdditional( uint16_t numA )
{
  header_.numberAdditional = numA;
}

std::vector< DNSResponse > DNSPacket::getAnswers()
{
  return answers_;
}

void DNSPacket::setAnswers( std::vector< DNSResponse > answers )
{
  answers_ = answers;
}

std::vector< DNSResponse > DNSPacket::getAuthority()
{
  return authorites_;
}

void DNSPacket::setAuthority( std::vector< DNSResponse > auth )
{
  authorites_ = auth;
}

std::vector< DNSResponse > DNSPacket::getAdditional()
{
  return additionals_;
}

void DNSPacket::setAdditional( std::vector< DNSResponse > add )
{
  additionals_ = add;
}

std::vector< DNSQuestion > DNSPacket::getQuestions( )
{
  return questions_;
}

void DNSPacket::setQuestions( std::vector<DNSQuestion> questions )
{
  questions_ = questions;
}
