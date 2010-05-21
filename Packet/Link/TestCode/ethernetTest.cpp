#include "ethernetTest.h"

EthernetTest::EthernetTest( std::ostream &out, int verboseLevel ) : qunit( out, verboseLevel)
{
}

int EthernetTest::run()
{
	testIsEthernet();
	testType();
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

void EthernetTest::testPacketCreation()
{
	//14 bytes ethernet header taken from a wireshark dump 
	uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
		0xf9, 0xfc, 0x6e, 0x08, 0x00 };

	//construct a ethernet header from bytes above
	Ethernet ethernet1( bits, 14 );

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
	ethernet1.setType( 0xDEAD );
	QUNIT_IS_EQUAL( ethernet1.type(), 0xDEAD );

	//Pulling out source Mac Addresses from headers
	MACAddress source1 = ethernet1.sourceMAC();
	MACAddress source2 = ethernet2.sourceMAC();

	//Both headers should be the same
	QUNIT_IS_TRUE( source1 == source2 );

	//Correct value for the source MAC Address
	uint8_t rightSourceMac[] = { 0xa4, 0xba, 0xdb, 0xf9, 0xfc, 0x6e };

	//Store the sourceMac from created header for comparison
	uint8_t sourceMac[6];
	source1.getMAC( sourceMac );

	//Compare all byte in arrays
	for( int i = 0; i < 6; ++i )
	{
		//casting for more readable output
		QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac[i]), static_cast<uint16_t>(rightSourceMac[i]) );
	}

	//Pulling out source Mac Addresses from headers
	MACAddress destination1 = ethernet1.destinationMAC();
	MACAddress destination2 = ethernet2.destinationMAC();

	//Both headers should be the same
	QUNIT_IS_TRUE( destination1 == destination2 );

	//Correct value for the source MAC Address
	uint8_t rightDestinationMac[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f };

	//Store the sourceMac from created header for comparison
	uint8_t destinationMac[6];
	destination1.getMAC( destinationMac );

	//Compare all byte in arrays
	for( int i = 0; i < 6; ++i )
	{
		QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac[i]), static_cast<uint16_t>(rightDestinationMac[i]) );
	}

}


#ifndef GLOBAL_SCOPE
int main()
{
	return EthernetTest( std::cerr ).run();
}
#endif

