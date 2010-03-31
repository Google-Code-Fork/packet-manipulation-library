#include "link.h"

template<> bool Link::is<Ethernet>( ) const
{
  return header_->isEthernet();
}

