#include "macTest.h"

MacTest::MacTest( std::ostream &out, int verboseLevel ) : qunit( out, verboseLevel)
{
}

int MacTest::run()
{
	testConstruction();
	return qunit.errors();
}

void MacTest::testConstruction()
{
	MACAddress mac1;
	std::vector< uint8_t > addressbytes;
	addressbytes.push_back( 0xDE );
	addressbytes.push_back( 0xAD );
	addressbytes.push_back( 0xBE );
	addressbytes.push_back( 0xEF );
	addressbytes.push_back( 0x20 );
	addressbytes.push_back( 0x10 );
	mac1.setMACAddress( addressbytes );
	MACAddress mac2( addressbytes );
	MACAddress mac3( mac2 );
	uint8_t addressByteArray[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x20, 0x10 };
	MACAddress mac4( addressByteArray );

	QUNIT_IS_TRUE( mac1 == mac2 );
	QUNIT_IS_TRUE( mac1 == mac3 );
	QUNIT_IS_TRUE( mac1 == mac4 );

	uint8_t macaddress[6];
	mac1.getMAC( macaddress );
	for( int i = 0; i < 6; ++i )
	{
		QUNIT_IS_TRUE( macaddress[i] == addressByteArray[i]);
	}
}

#ifndef GLOBAL_SCOPE
int main()
{
	return MacTest( std::cerr ).run();
}
#endif
