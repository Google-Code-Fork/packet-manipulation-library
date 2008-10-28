#include "inputPlugin.hpp"

class PcapSniffer : public InputPlugin 
{
  public :

    DataClassifications typesOfDataToReport();
    std::string getConfig();
    std::string setConfig( std::string config );
    void* inputThread( void *data );

};

extern "C" PcapSniffer* create();
extern "C" void destroy( PcapSniffer* p );
