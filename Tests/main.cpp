
#include <iostream>
#include "../Packet/App/TestCode/testRaw.h"
#include "../Packet/Trans/TestCode/testTcp.h"
#include "../Packet/Trans/TestCode/testUdp.h"
#include "../Packet/Inet/TestCode/testIPv4.h"
#include "../Packet/Inet/TestCode/testIcmp.h"
#include "../Packet/Link/TestCode/macTest.h"
#include "../Packet/Link/TestCode/ethernetTest.h"

int main()
{
	int returnVal = 0;
	returnVal += MacTest( std::cerr ).run();
	returnVal += EthernetTest( std::cerr ).run();
	returnVal += IPv4Test( std::cerr ).run();
	returnVal += IcmpTest( std::cerr ).run();
	returnVal += TcpTest( std::cerr ).run();
	returnVal += UdpTest( std::cerr ).run();
	returnVal += RawTest( std::cerr ).run();

	return returnVal;
}
