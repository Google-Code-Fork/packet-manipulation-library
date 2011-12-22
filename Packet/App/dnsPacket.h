/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra
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


#ifndef DNSPACKET_H
#define DNSPACKET_H

#include <string>
#include <vector>
#include <deque>
#include <map>
//#include "threads.h" 
#include <stdint.h>
#include "../packetBuffer.h"
#include "staticBuffer.h"
#include "appData.h"

typedef struct my_dns {
  uint16_t identification;
  uint16_t flags;
  #define QR 0x8000 //0-query 1-response;
  #define OPCODE 0x7800 //see opcodes;
  #define AA 0x0400 //authoritative answer
  #define TC 0x0200 //truncated
  #define RD 0x0100 //Recursion Desired
  #define RA 0x0080 //Recursion Available
  #define ZERO 0x0070 //must be zero
  #define RCODE 0x000F //return code
  uint16_t numberQuestions;
  uint16_t numberAnswers;
  uint16_t numberAuthority;
  uint16_t numberAdditional;
} DNSHeader;

namespace dnsopcode
{
  const uint16_t query = 0; 
  const uint16_t iquery = 1;
  const uint16_t serverStatus = 2; 
}

namespace dnstype
{
//information taken from: http://www.bind9.net/dns-parameters
//types
const uint8_t A = 0x01; //IP Address : RFC 1035
const uint8_t NS = 0x02; // Name Server : RFC 1035
const uint8_t MD = 0x03; // A mail destination (obsolete - use MX) : RFC 1035
const uint8_t MF = 0x04; // A Mail forwarder (obsolete - use MX) : RFC 1035
const uint8_t CNAME = 0x05; // Canonical Name : RFC 1035
const uint8_t SOA = 0x06; //Marks the start of a zone of authority : RFC 1035
const uint8_t MB = 0x07; //A Mailbox domain name (Experimental) : RFC 1035
const uint8_t MG = 0x08; //A Mail Group Member (Experimental) : RFC 1035
const uint8_t MR = 0x09; //A Mail Rename Domain Name (Experimental) : RFC 1035
const uint8_t NULLRR = 0x0A; // A null RR (Experimental) : RFC 1035
const uint8_t WKS = 0x0B; //A well known service description : RFC 1035
const uint8_t PTR = 0x0C; //Pointer Record : RFC 1035
const uint8_t HINFO = 0x0D; //Host Information : RFC 1035
const uint8_t MX = 0x0F; //Mail Exchange Record : RFC 1035
const uint8_t TXT = 0x10; //text strings : RFC 1035
const uint8_t RP = 0x11; //for a responsible person : RFC 1183
const uint8_t AFSDB = 0x12; //for AFS Data Base location : RFC 1183
const uint8_t X25 =           19;// for X.25 PSDN address                       [RFC 1183]
const uint8_t  ISDN =          20;// for ISDN address                            [RFC 1183]
const uint8_t  RT =            21;// for Route Through                           [RFC 1183]
const uint8_t  NSAP =          22;// for NSAP address, NSAP style A record       [RFC 1706]
const uint8_t  NSAPPTR = 23;// for domain name pointer, NSAP style         [RFC 1348] 
const uint8_t  SIG =           24;// for security signature                      [RFC 4034][RFC 3755][RFC 2535]
const uint8_t  KEY =           25;// for security key                            [RFC 4034][RFC 3755][RFC 2535]
const uint8_t  PX =            26;// X.400 mail mapping information              [RFC 2163]
const uint8_t  GPOS =          27;// Geographical Position                       [RFC 1712]
const uint8_t  AAAA =          28;// IP6 Address                                 [RFC 3596]
const uint8_t  LOC =           29;// Location Information                        [RFC 1876]
const uint8_t  NXT =           30;// Next Domain - OBSOLETE                      [RFC 3755][RFC 2535]
const uint8_t  EID =           31;// Endpoint Identifier                         [Patton]
const uint8_t  NIMLOC =        32;// Nimrod Locator                              [Patton]
const uint8_t  SRV =           33;// Server Selection                            [RFC 2782]
const uint8_t  ATMA =          34;// ATM Address                                 [ATMDOC]
const uint8_t  NAPTR =         35;// Naming Authority Pointer                    [RFC 2915][RFC 2168]
const uint8_t  KX =            36;// Key Exchanger                               [RFC 2230]
const uint8_t  CERT =          37;// CERT                                        [RFC 2538]
const uint8_t  A6 =            38;// A6 (Experimental)                           [RFC 3226][RFC 2874]
const uint8_t  DNAME =         39;// DNAME                                       [RFC 2672]
const uint8_t  SINK =          40;// SINK                                        [Eastlake]
const uint8_t  OPT =           41;// OPT                                         [RFC 2671]
const uint8_t  APL =           42;// APL                                         [RFC 3123]
const uint8_t  DS =            43;// Delegation Signer                           [RFC 3658]
const uint8_t  SSHFP =         44;// SSH Key Fingerprint                         [RFC 4255]
const uint8_t  IPSECKEY =      45;// IPSECKEY                                    [RFC 4025]
const uint8_t  RRSIG =         46;//  RRSIG                                      [RFC 4034][RFC 3755]
const uint8_t  NSEC =          47;// NSEC                                        [RFC 4034][RFC 3755]
const uint8_t  DNSKEY =        48;// DNSKEY                                      [RFC 4034][RFC 3755]
const uint8_t  DHCID =         49;// DHCID                                       [RFC 4701]
const uint8_t  NSEC3 =         50;// NSEC3                                       [RFC 5155]
const uint8_t  NSEC3PARAM =    51;// NSEC3PARAM                                  [RFC 5155]
const uint8_t  Unassigned =    52;//-54
const uint8_t  HIP =           55;// Host Identity Protocol                      [RFC 5205]
const uint8_t  NINFO =    56;//[REID]
const uint8_t  RKEY = 57; //[REID]
const uint8_t  TALINK = 58; // [Wijngaards]
const uint8_t  SPF =           99;//                                             [RFC 4408]
const uint8_t  UINFO =         100;//                                            [IANA-Reserved]
const uint8_t  UID =           101;//                                            [IANA-Reserved]
const uint8_t  GID =           102;//                                            [IANA-Reserved]
const uint8_t  UNSPEC =        103;//                                            [IANA-Reserved]
const uint8_t  Unassigned3 =    104;//-248
const uint8_t  TKEY =          249;// Transaction Key                            [RFC 2930]
const uint8_t  TSIG =          250;// Transaction Signature                      [RFC 2845]
const uint8_t  IXFR =          251;// incremental transfer                       [RFC 1995]
const uint8_t AXFR = 0xFC; //Request for Zone Transfer : RFC 1035
const uint8_t MAILB = 253; //mailbox-related RRs MB, MG, or MR) RFC1035
const uint8_t MAILA = 254; //mail agent RRs (Obsolete - see MX) RFC1035
const uint8_t ANY = 0xFF; //Request for All Records : RFC 1035
const uint16_t TA = 32768; //DNSSEC Trust Authorities [Weiler]
const uint16_t DLV = 32769; //DNSSEC Lookaside Validation [RFC4431]
//Unassigned 32770-65279
//Private Use 65280-65534
//Reserved 65535
}

namespace dnsclass{
const uint16_t reserved = 0; //i     [IANA]
const uint16_t internet = 1; //IN    [RFC 1035]
const uint16_t unassigned = 2; //    [IANA]
const uint16_t chaos = 3; //CH       [RFC 1035]
const uint16_t hesiod = 4; //HS      [RFC 1035]
// 5-253 are unassigned              [IANA]
const uint16_t none = 254; //        [RFC 2136]
const uint16_t any = 255; // [QClass][RFC 1035]
// 256 - 65534 unassigned            [IANA]
const uint16_t reservered=65535;//Reservered for private use [IANA]
}

namespace dnsrcode
{
const int16_t NoError = 0; //     No Error                             [RFC 1035]
const int16_t FormErr = 1; //     Format Error                         [RFC 1035]
const int16_t ServFail = 2; //    Server Failure                       [RFC 1035]
const int16_t NXDomain = 3; //    Non-Existent Domain                  [RFC 1035]
const int16_t NotImp = 4; //      Not Implemented                      [RFC 1035]
const int16_t Refused = 5; //     Query Refused                        [RFC 1035]
const int16_t YXDomain = 6; //    Name Exists when it should not       [RFC 2136]
const int16_t YXRRSet = 7; //     RR Set Exists when it should not     [RFC 2136]
const int16_t NXRRSet = 8; //     RR Set that should exist does not    [RFC 2136]
const int16_t NotAuth = 9; //     Server Not Authoritative for zone    [RFC 2136]
const int16_t NotZone = 10; //     Name not contained in zone           [RFC 2136]
//15 - 11       Unassigned  
const int16_t BADVERS = 16; //     Bad OPT Version                      [RFC 2671]
//const int16_t BADSIG = 16; //      TSIG Signature Failure               [RFC 2845]
const int16_t BADKEY = 17; //      Key not recognized                   [RFC 2845]
const int16_t BADTIME = 18; //     Signature out of time window         [RFC 2845]
const int16_t BADMODE = 19; //     Bad TKEY Mode                        [RFC 2930]
const int16_t BADNAME = 20; //     Duplicate key name                   [RFC 2930]
const int16_t BADALG = 21; //      Algorithm not supported              [RFC 2930]
const int16_t BADTRUNC = 22; //    Bad Truncation                       [RFC 4635]
//3840 - 23     Unassigned
//4095 - 3841   Reserved (Private Use)
//65535 - 4096  Unassigned

}

class DNSRecord
{
	public:
		DNSRecord();
		virtual ~DNSRecord();
		DNSRecord( const DNSRecord &n );
		DNSRecord& operator=( const DNSRecord &n );

		std::string domainName() const;
		void setDomainName( const std::string &domainName );

		uint16_t type() const;
		void setType( const uint16_t &type );

		uint16_t dnsClass() const;
		void setDnsClass( const uint16_t &dnsClass );

		uint32_t timeToLive() const;
		void setTimeToLive( const uint32_t &ttl );

		virtual uint16_t dataLength() const;

		virtual std::vector< uint8_t > data() const;
		virtual void setData( const std::vector< uint8_t > &data );
		//virtual void pushDataBack( const uint8_t &data );

		//virtual void clearData();
		uint64_t memorySize() const;

	private:
  //std::string domainName_;
	StaticBuffer domainName_;
  uint16_t dnsType_;
  uint16_t dnsClass_;
  uint32_t timeToLive_;
  //std::vector<uint8_t> data_;
	StaticBuffer data_;
};


class DNSQuestion
{
	public:
		DNSQuestion();
		DNSQuestion( const std::string &query, uint16_t type = dnstype::A, uint16_t dnsClass = dnsclass::internet );
		virtual ~DNSQuestion();
		DNSQuestion( const DNSQuestion &n );
		DNSQuestion& operator=( const DNSQuestion &n );

		std::string queryName() const;
		void setQueryName( const std::string &name );

		uint16_t type() const;
		void setType( const uint16_t &type );

		uint16_t dnsClass() const;
		void setDnsClass( const uint16_t &dnsClass );

	private:
  std::string queryName_;
  uint16_t dnsType_;
  uint16_t dnsClass_;
};


class DNSPacket : public AppData
{
  public:
    DNSPacket( );
		DNSPacket( const uint8_t *data, int size );
    DNSPacket( const std::vector<uint8_t> &packet );
    DNSPacket( const DNSPacket &n );
    DNSPacket& operator=( const DNSPacket &n );
		DNSPacket( const PacketBuffer &packet );
    virtual ~DNSPacket( );

    uint16_t identificationNumber() const;
    void setIdentificationNumber( const uint16_t &id );
//    void setRandomIdentificationNumber( );

    void setQRFlag( const bool &isResponse ); //true if response;
    bool qrFlag() const;
		bool isQuery() const { return qrFlag() ? false : true; }
		bool isResponse() const { return qrFlag() ? true : false; }
    void setOpcodeFlag( const uint8_t &code ); //see codes above...
    uint8_t opcodeFlag() const;
    void setAAFlag( const bool &aa );
    bool aaFlag( ) const;
    void setTCFlag( const bool &tc );
    bool tcFlag( ) const;
    void setRDFlag( const bool &rd );
    bool rdFlag( ) const;
    void setRAFlag( const bool &ra );
    bool raFlag( ) const;
    void setZeroFlag( const uint8_t &zero );
    uint8_t zeroFlag( ) const;
    void setRcodeFlag( uint8_t rcode );
    uint8_t rcodeFlag( ) const;

    //Don't remember what this was for... :-/
//   void setAutoGenerateNumbers( bool on ); //Should we automagically calculate
                                            //the numbers of questions
					    //answers... (defaults to on)
//    bool getAutoGenerateNumbers( ); 

    //These values are for the header
    uint16_t numberOfQuestions() const;
    uint16_t numberOfAnswers() const;
    uint16_t numberOfAuthority() const;
    uint16_t numberOfAdditional() const;


    std::vector< DNSRecord > answers() const;
		DNSRecord answer( const int &index ) const;
    void setAnswers( std::vector< DNSRecord > );
		void pushBackAnswer( const DNSRecord &answer );
		void clearAnswers();

    std::vector< DNSRecord > authorities() const;
		DNSRecord authority( const int &index ) const;
    void setAuthorities( std::vector< DNSRecord > );
		void pushBackAuthority( const DNSRecord &authority );
		void clearAuthorities();

    std::vector< DNSRecord > additionals() const;
		DNSRecord additional( const int &index ) const;
    void setAdditionals( std::vector< DNSRecord > );
		void pushBackAdditional( const DNSRecord &additional );
		void clearAdditionals();

    std::vector< DNSQuestion>	questions( ) const;
		DNSQuestion question( const int &index ) const;
    void setQuestions( std::vector< DNSQuestion > );
		void pushBackQuestion( const DNSQuestion &question );
		void clearQuestions();

    std::vector<uint8_t> data( ) const;
		PacketBuffer makePacket() const;
    int size() const { return makePacket().size(); }
    //std::vector< uint8_t > generateSafePacket( ) const;
		
		bool isDNS() const {return true;}

  private:
    void init( std::vector<uint8_t> packet );
    DNSRecord dnsResponseParser( std::vector<uint8_t>, uint16_t& );
    std::string domainParser( std::vector<uint8_t>, uint16_t& );
    std::vector<uint8_t> generateEncodedDomainName( const std::string &domainName );
    std::vector<uint8_t> encodeDNSRecord( const std::vector< DNSRecord > &responses );

		void formatQuestion( std::vector< uint8_t > &packet, const DNSQuestion &question ) const;
    //void formatRecord( std::vector< uint8_t > &packet, const DNSRecord &record ) const;
		void formatURL( std::vector< uint8_t > &packet, const std::string &url ) const;

  private:
    DNSHeader header_;
    std::vector< DNSQuestion > questions_;
    std::vector< DNSRecord > answers_;
    std::vector< DNSRecord > authorities_;
    std::vector< DNSRecord > additionals_;

};

typedef DNSPacket DNS;
#endif
