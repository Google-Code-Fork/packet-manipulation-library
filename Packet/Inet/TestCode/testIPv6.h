#include "../../../Test/QUnit.hpp"
#include "../ipv6.h"
#include <iostream>
#include <netinet/in.h>
#include "../ipv6Address.h"

//IPv6 packet used for test:
//version - 6
//Traffic Class - 0
//Flow Label - 0
//Payload Length - 24 (0x0018)
//Hext Header - 6 (0x06)
//Hop Limit - 64 (0x40)
//src IP - 
//dst IP - 

class IPv6Test
{
  public:
		IPv6Test( std::ostream &out, int verboseLevel = QUnit::verbose );

    int run();

  private:
    QUnit::UnitTest qunit;

//    void testIsIpv6();

		void testPacketCreation();
};

                    
