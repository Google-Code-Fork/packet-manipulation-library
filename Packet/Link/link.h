#ifndef LINK_H
#define LINK_H

#include "linkData.h"
#include "ethernet.h"

namespace LinkTypes
{
  const uint16_t Ethernet = 1;
  const uint16_t 802_11 = 2;
  const uint16_t Arp = 3;
  const uint16_t Packet = 4;
}

class Link 
{
  public:
    Link( Ethernet e );
    Link~();

    bool isEthernet( );
    //Should I make the below a reference?
    Ethernet getEthernet( ); //throws exception if not ethernet
    void setEthernet( Ethernet e );//throws exception if not ethernet;



  private:
    LinkData* header_;
    uint16_t linkType;

}

#endif
