#include "trans.h"

template<> bool Trans::is<UDP>( )
{
  return header_->isUDP();
}

template<> bool Trans::is<TCP>( )
{
  return header_->isTCP();
}


