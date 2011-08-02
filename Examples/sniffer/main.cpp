#include "../common/commandLineParser.h"
#include <common/helper.h>
#include <stdint.h>
#include <Sniffer/sniffer.h>
#include <iostream>

void printPacketInfo( const Packet &p );
void printHelp();

int main(int argc, char *argv[])
{
  uint32_t numberOfPackets = ss_atoi<uint32_t>( parser(argc, argv, "-n") );
  std::string interface = parser( argc, argv, "-i" );
  if( parser( argc, argv, "--help" ).size()` > 0 || parser( argc, argv, "-h" ).size() > 0 )
  {
    printHelp();
    return 0;
  }
  Sniffer sniffer;

  sniffer.setInputDevice(interface);
  sniffer.start();

  uint count = 0;
  while( count < numberOfPackets )
  {
    Packet p = sniffer.popPacket();
    printPacketInfo( p );
    ++count;
  }

  sniffer.stop();


  return 0;
}

void printPacketInfo(const Packet &p)
{
  if( p.inetSize() > 0 )
    if( p.inetIs<IPv4>() )
    {
      IPv4 ipHeader = p.getInet< IPv4 >();
      std::cout << ipHeader.sourceAddress().toString() << " -> " << ipHeader.destinationAddress().toString() << std::endl;
      return;
    }
  std::cout << "Non IPv4 Packet" << std::endl;
}

void printHelp()
{
  std::cout << "Sniffer Example (C) 2011 Jeff Scaparra" << std::endl;
  std::cout << "sniffer -i -n | --help" << std::endl;
  std::cout << "-i <interface>" << std::endl;
  std::cout << "-n <number of packets to sniff" << std::endl;
}
