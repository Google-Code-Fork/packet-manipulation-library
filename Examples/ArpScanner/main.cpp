#include <iostream>
#include "commandLineParser.h"
#include <string>
#include <ArpAgent/arpagent.h>
#include <Device/devicesLookup.h>

void printHelp();

int main(int argc, char *argv[])
{
  DevicesLookup deviceLookup;
  ArpAgent arpAgent;
  arpAgent.setArpRetryLimit(2);
  arpAgent.setArpTimeout(1000); //1000ms
  arpAgent.setCacheTimeout(3600); //1hr
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

  arpAgent.startAgent();
  MACAddress mac = arpAgent.arp( scan );

  std::cout << scan << " : " << mac.toString() << std::endl;
  arpAgent.stopAgent();
  return 0;
}

void printHelp()
{
  std::cout << "INVALID ARGS" << std::endl;
}
