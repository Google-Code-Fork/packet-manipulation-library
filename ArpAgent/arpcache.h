#ifndef ARPCACHE_H
#define ARPCACHE_H

#include "../common/threads.h"
#include "../Packet/packet.h"
#include "../Packet/Link/mac.h"
#include <map>

class ArpCache
{
public:
  explicit ArpCache();
  virtual ~ArpCache();

  void addEntry( const std::string &ip, const MACAddress &mac );
  MACAddress lookup( const std::string &ip ) const;
  int size() const;
  void setTimeout( const uint &seconds );
  uint timeout() const;

private:
  Mutex cacheMutex_;
  std::map< std::string, MACAddress > cache_;
  std::map< std::string, time_t > timeCache_; //How old are the entries
  uint timeout_;
};

#endif // ARPCACHE_H
