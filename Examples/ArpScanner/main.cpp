#include <iostream>
#include "commandLineParser.h"
#include <string>
#include <vector>
#include <ArpAgent/arpagent.h>
#include <Device/devicesLookup.h>
#include <common/stringUtils.h>
#include <common/helper.h>

void printHelp();

std::vector< IPv4Address > arpAddresses( const std::string &scanString );

int main(int argc, char *argv[])
{

  DevicesLookup deviceLookup;
  ArpAgent arpAgent;
  arpAgent.setArpRetryLimit(2);
  arpAgent.setArpTimeout(1500); //1000ms
  arpAgent.setCacheTimeout(600); //10 min
  std::string device = parser(argc, argv, "-d" );
  if( device.size() == 0 )
  {
    printHelp();
    exit(1);
  }
  arpAgent.setDeviceName( device );

  std::string ip = parser( argc, argv, "--sourceIP" );
  if( ip.size() == 0 )
    ip = deviceLookup.address(device);
  arpAgent.setIPv4Address( ip );

  std::string gateway = parser( argc, argv, "--gateway" );
  if( gateway.size() == 0 )
    gateway = deviceLookup.gateway();
  arpAgent.setIPv4Gateway( gateway );

  std::string netmask = parser( argc, argv, "--netmask" );
  if( netmask.size() == 0 )
    netmask = deviceLookup.netmask(device);
  arpAgent.setNetmask(netmask);

  std::string macString = parser( argc, argv, "--sourceMAC" );
  if( macString.size() == 0 )
    macString = deviceLookup.macAddress(device);
  arpAgent.setMacAddress(MACAddress(macString));

  std::string scan = parser( argc, argv, "--scan" );
  std::vector< IPv4Address > scanIps = arpAddresses( scan );

  arpAgent.startAgent();

  for( int i = 0; i < scanIps.size(); ++i )
  {
    MACAddress mac = arpAgent.arp( scanIps[i] );
    if( false && mac.makePacket().vector() == std::vector< uint8_t >( 6, 0 ) )
    { //empty; i.e. no reply
    }
    else
    {
      std::cout << scanIps[i].toString() << " : " << mac.toString() << std::endl;
    }
  }
  arpAgent.stopAgent();
  return 0;
}

std::vector< IPv4Address > arpAddresses(const std::string &scanString)
{
  std::vector< IPv4Address > results;
  std::vector< std::string > tmp = split( scanString, '/' );
  if( tmp.size() == 1 )
  { //not a netblock
    results.push_back( IPv4Address( tmp[0] ) );
  }
  else if ( tmp.size() == 2 )
  {
    uint32_t netmask = 0;
    uint32_t bits = ss_atoi<uint32_t>( tmp[1] );
    static const uint32_t max = 0xFFFFFFFF;
    for( int i = 0; i < bits; ++i )
    {
      netmask <<= 1;
      netmask |= 0x00000001;
    }
    IPv4Address specifiedNetwork( tmp[0] );
    uint32_t network = specifiedNetwork.inAddr() & netmask;

    for( int i = 0; i < (2 << (32-bits)) ; ++i )
    {
      results.push_back( IPv4Address( network | (i << bits) ) );
    }
  }
  else
  {
    printHelp();
    exit(1);
  }
  return results;
}

void printHelp()
{
  std::cout << "INVALID ARGS" << std::endl;
}
