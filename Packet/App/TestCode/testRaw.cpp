#include "testRaw.h"

RawTest::RawTest( std::ostream &out, int verboseLevel ) : qunit(
		out, verboseLevel)
{
}

int RawTest::run()
{
	testIsRaw();
	testConstruction();
	return qunit.errors();
}

void RawTest::testIsRaw()
{
	Raw raw;
	QUNIT_IS_TRUE( raw.isRaw() );
}

void RawTest::testConstruction()
{
	//25 bytes raw data taken from wireshark
	uint8_t bits[] = { 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x32, 0x00, 0x5c,
		0x4d, 0x41, 0x49, 0x4c, 0x53, 0x4c, 0x4f, 0x54, 0x5c, 0x42, 0x52, 0x4f, 0x57, 0x53,
		0x45, 0x00 };

	//construct raw header from bytes above
	Raw raw1( bits, 25 );

	//copy constructor
	Raw raw2( raw1 );

	//check to size of raw contents in bytes
	QUNIT_IS_EQUAL( raw1.size(), raw2.size() );
	QUNIT_IS_TRUE( raw1.size() == 25 );

	//check to see if raw
	QUNIT_IS_TRUE( raw1.isRaw() );

}

#ifndef GLOBAL_SCOPE
int main()
{
	return RawTest ( std::cerr ).run();
}
#endif
