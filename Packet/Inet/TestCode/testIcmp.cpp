#include "../../../Test/QUnit.hpp"
#include "../icmp.h"
#include <iostream>
#include <netinet/in.h>

class IcmpTest
{
	public:
		IcmpTest( std::ostream &out, int verboseLevel = QUnit::verbose ) : qunit(
				out, verboseLevel)
	{
	}

		int run()
		{
			testIsIcmp();
			return qunit.errors();
		}

	private:
		QUnit::UnitTest qunit;

		void testIsIcmp()
		{
			ICMP icmp;
			QUNIT_IS_TRUE( icmp.isICMP() );
		}
}

int main()
{ 
	return IcmpTest( std::cerr ).run();
}
