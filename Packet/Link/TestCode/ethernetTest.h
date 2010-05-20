#include "../../../Test/QUnit.hpp"
#include "../ethernet.h"
#include <iostream>
#include <netinet/in.h>

class EthernetTest 
{
public:
	EthernetTest( std::ostream &out, int verboseLevel = QUnit::verbose );

	int run();

private:
	QUnit::UnitTest qunit;

	void testIsEthernet();

	void testType();

	void testPacketCreation();
};

