//This is file is to ensure that all instances of an object work 
//This is to find problems with templates and abstract pure functions and
//classes.

#include "tcp.h"
#include "udp.h"
#include <vector>
#include "trans.h"
#include <iostream>

int main()
{
  TCP tcp;
  UDP udp;

  TransData* tptr;
  tptr = &tcp;
  std::cout << "TCP:" << std::endl;
  std::cout << "Is TCP? " << ( tptr->isTCP() ? "Yes" : "No" ) << std::endl;
  std::cout << "Is UDP? " << ( tptr->isUDP() ? "Yes" : "No" ) << std::endl;
  std::cout << "Is ICMP? " << ( tptr->isICMP() ? "Yes" : "No" ) << std::endl;
  tptr = &udp;
  std::cout << "UDP: " << std::endl;
  std::cout << "Is TCP? " << ( tptr->isTCP() ? "Yes" : "No" ) << std::endl;
  std::cout << "Is UDP? " << ( tptr->isUDP() ? "Yes" : "No" ) << std::endl;
  std::cout << "Is ICMP? " << ( tptr->isICMP() ? "Yes" : "No" ) << std::endl;
  
  std::vector< Trans > data;
  data.push_back( tcp );
  data.push_back( udp );
  std::cout << "TCP: " << std::endl;
  std::cout << "Is TCP? " << ( data.at( 0 ).is<TCP>() ? "YES!" : "NO" ) << std::endl;
  std::cout << "Is UDP? " << ( data.at( 0 ).is<UDP>() ? "YES!" : "NO" ) << std::endl;
  std::cout << "UDP: " << std::endl;
  std::cout << "Is TCP? " << ( data.at( 1 ).is<TCP>() ? "YES!" : "NO" ) << std::endl;
  std::cout << "Is UDP? " << ( data.at( 1 ).is<UDP>() ? "YES!" : "NO" ) << std::endl;


  tcp = data.at( 0 ).get<TCP>();
  udp = data.at( 1 ).get<UDP>();

  return 0;
}
