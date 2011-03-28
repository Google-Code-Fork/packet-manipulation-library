#include "testArp.h"

ARPTest::ARPTest( std::ostream &out, int verboseLevel ) : qunit(
		out, verboseLevel)
{
}

int ARPTest::run()
{
	testIsARP();
	testConstruction();
	return qunit.errors();
}

void ARPTest::testIsARP()
{
	Arp arp;
	QUNIT_IS_TRUE( arp.isArp() );
	QUNIT_IS_FALSE( arp.isRaw() );
}

void ARPTest::testConstruction()
{
	uint8_t bits[] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x25, 0x00, 0x4b, 0x5a, 0x7d, 0xc0, 0xa8, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa8, 0x01, 0xdf };
	std::vector< uint8_t > senderMacAddress;
	senderMacAddress.push_back( 0x00 );
	senderMacAddress.push_back( 0x25 );
	senderMacAddress.push_back( 0x00 );
	senderMacAddress.push_back( 0x4b );
	senderMacAddress.push_back( 0x5a );
	senderMacAddress.push_back( 0x7d );
	std::vector< uint8_t > senderIPAddress;
	senderIPAddress.push_back( 0xc0 ); //192.168.1.88
	senderIPAddress.push_back( 0xa8 );
	senderIPAddress.push_back( 0x01 );
	senderIPAddress.push_back( 0x88 );

	std::vector< uint8_t > targetMacAddress;
	targetMacAddress.push_back( 0x00 );
	targetMacAddress.push_back( 0x00 );
	targetMacAddress.push_back( 0x00 );
	targetMacAddress.push_back( 0x00 );
	targetMacAddress.push_back( 0x00 );
	targetMacAddress.push_back( 0x00 );

	std::vector< uint8_t > targetIPAddress;
	targetIPAddress.push_back( 0xc0 ); //192.168.1.223;
	targetIPAddress.push_back( 0xa8 );
	targetIPAddress.push_back( 0x01 );
	targetIPAddress.push_back( 0xdf );

	//construct raw header from bytes above
	Arp arp1( bits, 28 );

	//copy constructor
	Arp arp2( arp1 );

	//check to size of raw contents in bytes
	QUNIT_IS_EQUAL( arp1.size(), arp2.size() );
	QUNIT_IS_TRUE( arp1.size() == 28 );

	//check to see if arp 
	QUNIT_IS_TRUE( arp1.isArp() );
	QUNIT_IS_TRUE( arp2.isArp() );

	//check to see if the hardware values are correct
	QUNIT_IS_TRUE( arp1.hardwareType() == hardwaretype::ETHERNET );
	QUNIT_IS_TRUE( arp2.hardwareType() == hardwaretype::ETHERNET );

	//check protocol
	QUNIT_IS_TRUE( arp1.protocolType() == protocoltype::IP );
	QUNIT_IS_TRUE( arp2.protocolType() == protocoltype::IP );

	//check hardware size
	QUNIT_IS_TRUE( arp1.hardwareSize() == hardwaresize::ETHERNET);
	QUNIT_IS_TRUE( arp2.hardwareSize() == hardwaresize::ETHERNET);

	//check protocol size
	QUNIT_IS_TRUE( arp1.protocolSize() == protocolsize::IP );
	QUNIT_IS_TRUE( arp2.protocolSize() == protocolsize::IP );

	//check opcode
	QUNIT_IS_TRUE( arp1.opcode() == arpopcode::request );
	QUNIT_IS_TRUE( arp2.opcode() == arpopcode::request );

	//check Sender MAC
	QUNIT_IS_TRUE( arp1.senderMacAddress().vector() == senderMacAddress )
	QUNIT_IS_TRUE( arp2.senderMacAddress().vector() == senderMacAddress )

	//check Sender IP
	QUNIT_IS_TRUE( arp1.senderIPAddress().vector() == senderIPAddress )
	QUNIT_IS_TRUE( arp2.senderIPAddress().vector() == senderIPAddress )

	//check target MAC
	QUNIT_IS_TRUE( arp1.targetMacAddress().vector() == targetMacAddress )
	QUNIT_IS_TRUE( arp2.targetMacAddress().vector() == targetMacAddress )
	
	//check target IP
	QUNIT_IS_TRUE( arp1.targetIPAddress().vector() == targetIPAddress )
	QUNIT_IS_TRUE( arp2.targetIPAddress().vector() == targetIPAddress )

//	std::vector <uint8_t > ip = arp1.targetIPAddress().vector();
//	std::cout << static_cast<uint32_t>(ip[0]) << "." << static_cast<uint32_t>(ip[1]) << "." 
//		<< static_cast<uint32_t>(ip[2]) << "." << static_cast<uint32_t>( ip[3] ) << std::endl;
	

}

#ifndef GLOBAL_SCOPE
int main()
{
	return ARPTest ( std::cerr ).run();
}
#endif
