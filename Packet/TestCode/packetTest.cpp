#include "ethernetTest.h"

EthernetTest::EthernetTest( std::ostream &out, int verboseLevel ) : qunit( out, verboseLevel)
{
}

int EthernetTest::run()
{
	testIsEthernet();
	testType();
	testConstruction();
	testPacketCreation();
	return qunit.errors();
}

void EthernetTest::testIsEthernet()
{
	Ethernet ethernet;
	QUNIT_IS_TRUE( ethernet.isEthernet() );
}

void EthernetTest::testType()
{
	Ethernet ethernet;
	QUNIT_IS_EQUAL( ethernet.type(), ethernetProtocol::ETH_P_IP );
	ethernet.setType( ethernetProtocol::ETH_P_ARP );
	QUNIT_IS_EQUAL( ethernet.type(), ethernetProtocol::ETH_P_ARP );
}

void EthernetTest::testConstruction()
{
	//14 bytes ethernet header taken from a wireshark dump 
	uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
		0xf9, 0xfc, 0x6e, 0x08, 0x00 };

	//construct a ethernet header from bytes above
	Ethernet ethernet1( bits, 14 );
  MACAddress destinationMac = ethernet1.destinationMAC();
  MACAddress sourceMac = ethernet1.sourceMAC();

	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[0]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[1]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[2]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[3]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[4]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[5]), 0x6e );

	QUNIT_IS_EQUAL( ethernet1.type(), 0x0800 );
  
	//Create a vector to test alternate constructor
	std::vector< uint8_t > bytes;
	for( int i = 0; i < 14; ++i )
	{
		bytes.push_back( bits[i] );
	}
	//Construct a ethernet header from vector of bytes representing ethernet
	//header capture from wireshark
	Ethernet ethernet2( bytes );
	//Test that the types of each header is correct
	QUNIT_IS_EQUAL( ethernet1.type(), ethernetProtocol::ETH_P_IP );
	QUNIT_IS_EQUAL( ethernet2.type(), ethernetProtocol::ETH_P_IP );

	//Pulling out source Mac Addresses from headers
	MACAddress source1 = ethernet1.sourceMAC();
	MACAddress source2 = ethernet2.sourceMAC();

	//Both headers should be the same
	QUNIT_IS_TRUE( source1 == source2 );

	//Pulling out source Mac Addresses from headers
	MACAddress destination1 = ethernet1.destinationMAC();
	MACAddress destination2 = ethernet2.destinationMAC();

	//Both headers should be the same
	QUNIT_IS_TRUE( destination1 == destination2 );

	destinationMac = ethernet2.destinationMAC();
	sourceMac = ethernet2.sourceMAC();

	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[0]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[1]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[2]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[3]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[4]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[5]), 0x6e );

	QUNIT_IS_EQUAL( ethernet2.type(), 0x0800 );

	Ethernet ethernet3(ethernet1);
	destinationMac = ethernet3.destinationMAC();
	sourceMac = ethernet3.sourceMAC();

	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[0]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[1]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[2]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[3]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[4]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[5]), 0x6e );

	QUNIT_IS_EQUAL( ethernet3.type(), 0x0800 );

	Ethernet ethernet4;
	ethernet4 = ethernet2;
	destinationMac = ethernet4.destinationMAC();
	sourceMac = ethernet4.sourceMAC();

	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[0]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[1]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[2]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[3]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[4]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[5]), 0x6e );

	QUNIT_IS_EQUAL( ethernet4.type(), 0x0800 );


}


void EthernetTest::testPacketCreation()
{
	//14 bytes ethernet header taken from a wireshark dump 
	uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
		0xf9, 0xfc, 0x6e, 0x08, 0x00 };

	//construct a ethernet header from bytes above
	Ethernet ethernet1( bits, 14 );

  std::vector< uint8_t > data = ethernet1.makePacket().vector();

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[6]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[7]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[8]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[9]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[10]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[11]), 0x6e );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[12]), 0x08 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[13]), 0x00 );
}
#ifndef GLOBAL_SCOPE
int main()
{
	return EthernetTest( std::cerr ).run();
}
#endif

