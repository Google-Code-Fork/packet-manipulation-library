#include "arpcache.h"

void* startCleanUpThread( void *data )
{
  ArpCache *cache = reinterpret_cast< ArpCache* >( data );
  cache->cleanUpThread();

  return NULL;
}

ArpCache::ArpCache()
{
  cacheTimeoutThread_.setStartRoutine( startCleanUpThread );
  cacheTimeoutThread_.start( this );
}

ArpCache::~ArpCache()
{
  cacheTimeoutThread_.stop();
}

void ArpCache::addEntry(const std::string &ip, const MACAddress &mac)
{
  MutexLocker lock( cacheMutex_ );
  time_t currentTime = time( NULL );
  cache_[ ip ] = mac;
  timeCache_[ ip ] = currentTime;
}

MACAddress ArpCache::lookup(const std::string &ip) const
{
  MutexLocker lock( cacheMutex_ );
  std::map< std::string, MACAddress >::const_iterator itr = cache_.lower_bound(ip);

  if( itr != cache_.end() && !(cache_.key_comp()(ip, itr->first) ) )
  { //exist
    return itr->second;
  }
  return MACAddress();
}

int ArpCache::size() const
{
  MutexLocker lock( cacheMutex_ );
  return cache_.size();
}

void ArpCache::setTimeout(const uint &seconds)
{
  MutexLocker lock( cacheMutex_ );
  timeout_ = seconds;
}

uint ArpCache::timeout() const
{
  MutexLocker lock( cacheMutex_ );
  return timeout_;
}

void ArpCache::cleanUpThread()
{
  std::vector< std::string > entriesToRemove;
  struct timespec sleeptime;
  sleeptime.tv_nsec = 0;
  sleeptime.tv_sec = 0;
  time_t current = time( NULL );
  while( true )
  {
    time_t shortestTimeLeft = timeout_;
    std::map< std::string, time_t >::iterator itr;
    MutexLocker lock( cacheMutex_ );
    for( itr = timeCache_.begin(); itr != timeCache_.end(); ++itr )
    {
      time_t timeLeft = timeout_ - (current - itr->second);
      if( timeLeft <= 0 )
        entriesToRemove.push_back( itr->first );
      if( shortestTimeLeft > timeLeft )
        shortestTimeLeft = timeLeft;
    }

    for( uint i = 0; i < entriesToRemove.size(); ++i )
    {
      cache_.erase(entriesToRemove[i]);
      timeCache_.erase( entriesToRemove[i]);
    }
    lock.unlock();
    sleeptime.tv_sec  = shortestTimeLeft;
    nanosleep( &sleeptime, NULL );
  }
}
