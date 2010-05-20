#include "../../../Test/QUnit.hpp"
#include "../mac.h"
#include <iostream>
#include <netinet/in.h>

class MacTest 
{
public:
	MacTest( std::ostream &out, int verboseLevel = QUnit::verbose ); 

	int run();

private:
	QUnit::UnitTest qunit;

	void testConstruction();
};

