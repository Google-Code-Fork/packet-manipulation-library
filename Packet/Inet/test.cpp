#include "ipv4.h"
//This is file is to ensure that all instances of an object work 
//This is to find problems with templates and abstract pure functions and
//classes.
#include <vector>
#include "inet.h"
#include <iostream>

int main()
{
  IPv4 ip;
  InetData* iptr = &ip;
  std::cout << "Is IP? " << ( iptr->isIPv4() ? "Yes" : "No" ) << std::endl;
  std::vector< Inet > data;
  data.push_back( ip );
  std::cout << "Is IP? " << ( data.at( 0 ).is<IPv4>() ? "YES!" : "NO" ) << std::endl;
  std::cout << "Is vector<int>? " << ( data.at( 0 ).is< std::vector<int> >() ? "YES" : "NO" ) << std::endl;

  ip = data.at( 0 ).get<IPv4>();


  return 0;
}
