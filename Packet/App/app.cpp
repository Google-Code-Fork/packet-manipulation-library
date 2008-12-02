#include "app.h"

template<> bool App::is<Raw>( )
{
  return header_->isRaw();
}



