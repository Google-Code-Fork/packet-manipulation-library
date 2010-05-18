#include "../../../Test/QUnit.hpp"
#include "../raw.h"
#include <iostream>
#include <netinet/in.h>

class RawTest
{
	public:
		RawTest( std::ostream &out, int verboseLevel = QUnit::verbose ) : qunit(
				out, verboseLevel)
		{
		}

		int run()
		{
			testIsRaw();
			testConstruction();
			return qunit.errors();
		}

	private:
		QUnit::UnitTest qunit;

		void testIsRaw()
		{
			Raw raw;
			QUNIT_IS_TRUE( raw.isRaw() );
		}

		void testConstruction()
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

			//create a vector to test alternate constructor
//			std::vector< uint8_t > bytes;
//			for (int i = 0; i < 25; ++i )
//			{
//				bytes.push_back( bits[i] );
//			}
			//construct raw vector of bytes
//			Raw raw3();
//			raw3.setData( std::vector< bytes > data );
		}
};

int main()
{
	return RawTest ( std::cerr ).run();
}
