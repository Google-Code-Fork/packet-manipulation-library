#include "../../Test/QUnit.hpp"
#include "../Link/ethernet.h"
#include <iostream>
#include <netinet/in.h>

class PacketTest 
{
public:
	PacketTest( std::ostream &out, int verboseLevel = QUnit::verbose );

	int run();

private:
	QUnit::UnitTest qunit;

	void testConstruction();

	void testPacketCreations();
};

