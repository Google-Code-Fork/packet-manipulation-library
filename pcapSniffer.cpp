#include "pcapSniffer.hpp"
#include <sstream>


DataClassifications PcapSniffer::typesOfDataToReport()
{
  DataClassifications dataClassification;
  dataClassification.ipv4 = true;
  return dataClassification;
}

std::string PcapSniffer::getConfig()
{
  std::stringstream dataStream; 
  dataStream << "<Config>" << std::endl;
  dataStream << "<RefreshTime>" <<
    clientCommData->getRefreshTime() << "</RefreshTime>" <<
    std::endl;
  dataStream << "<EdgeLife>" <<
    clientCommData->graphData->getEdgeLife() <<
    "</EdgeLife>" << std::endl;
  dataStream << "</Config>" << std::endl;

  return dataStream.str();
}

std::string PcapSniffer::setConfig( std::string config );

void* PcapSniffer::inputThread( void *data );


extern "C" PcapSniffer* create() 
{
  return new InputPlugin;
}

extern "C" void destroy( PcapSniffer* p )
{
  delete p;
}
