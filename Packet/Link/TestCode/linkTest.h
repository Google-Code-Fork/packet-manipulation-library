#include "../../../Test/QUnit.hpp"
#include "../ethernet.h"
#include "../link.h"
#include <iostream>
#include <netinet/in.h>

class LinkTest 
{
public:
	LinkTest( std::ostream &out, int verboseLevel = QUnit::verbose );

	int run();

private:
	QUnit::UnitTest qunit;

	void testEthernet();
};

