#include "link.h"

template<> bool Link::is<Ethernet>( ) const
{
	if( header_ )
		return header_->isEthernet();
	return false;
}

