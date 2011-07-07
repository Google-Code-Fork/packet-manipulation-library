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
  arpAgent.setArpTimeout(250); //250ms
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

  std::string mac = parser( argc, argv, "--sourceMAC" );
  if( mac.size() == 0 )
    mac = deviceLookup.macAddress(device);
  arpAgent.setMacAddress(MACAddress(mac));

  std::string scan = parse( argc, argv, "--scan" );

  MACAddress mac = arpAgent.arp( scan );

  std::coud << scan << " : " << mac.macString() << std::endl;

  return 0;
}

void printHelp()
{
}
