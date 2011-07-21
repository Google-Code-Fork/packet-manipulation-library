
#include <Packet/Link/oui.h>
#include <Device/devicesLookup.h>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  DevicesLookup devicesLookup;
  std::vector< MACAddress > macAddresses;
  std::vector< std::string > interfaceNames = devicesLookup.devicesAvailable();
  for( uint32_t i = 0; i < interfaceNames.size(); ++i )
  {
    macAddresses.push_back( devicesLookup.macAddress( interfaceNames[i] ) );
  }

  OUILookup oui( "oui.txt" );
  for( uint32_t i = 0; i < interfaceNames.size(); ++i )
  {
    if( ! devicesLookup.isLoopback( interfaceNames[i] ) )
    {
      std::cout << "Interface: " << interfaceNames[i] << std::endl;
      std::cout << "Mac Address: " << macAddresses[i].toString() << std::endl;
      std::cout << "Company: " << oui.company( macAddresses[i] ) << std::endl;
      std::cout << "Address: " << oui.address( macAddresses[i] ) << std::endl;
      std::cout << "Country: " << oui.country( macAddresses[i] ) << std::endl;
    }
  }

    return 0;
}
