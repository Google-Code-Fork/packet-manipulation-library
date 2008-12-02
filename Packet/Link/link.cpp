#include "link.h"

template<> bool Link::is<Ethernet>( )
{
  return header_->isEthernet();
}

