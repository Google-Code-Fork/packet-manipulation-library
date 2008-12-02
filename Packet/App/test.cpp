//This is file is to ensure that all instances of an object work 
//This is to find problems with templates and abstract pure functions and
//classes.
#include "raw.h"
#include <vector>
#include "app.h"
#include <iostream>

int main()
{
  Raw raw;
  AppData* aptr = &raw;
  std::cout << "Is RAW? " << ( aptr->isRaw() ? "Yes" : "No" ) << std::endl;
  std::vector< App > data;
  data.push_back( raw );
  std::cout << "Is Raw? " << ( data.at( 0 ).is<Raw>() ? "YES!" : "NO" ) << std::endl;
  std::cout << "Is vector<int>? " << ( data.at( 0 ).is< std::vector<int> >() ? "YES" : "NO" ) << std::endl;

  raw = data.at( 0 ).get<Raw>();


  return 0;
}
