#include "inet.h"

template<> bool Inet::is<IPv4>( )
{
  return header_->isIPv4();
}


