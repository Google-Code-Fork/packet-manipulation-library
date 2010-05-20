#include "../../../Test/QUnit.hpp"
#include "../raw.h"
#include <iostream>
#include <netinet/in.h>

class RawTest
{
	public:
		RawTest( std::ostream &out, int verboseLevel = QUnit::verbose );

		int run();

	private:
		QUnit::UnitTest qunit;

		void testIsRaw();

		void testConstruction();
};

