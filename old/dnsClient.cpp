#include "dnsClient.h"

void* dnsWorkerThread( void *data )
{
}

DNSClient::DNSClient( int numThreads, int timeout ) : timeout_( timeout )
{
  for( int i = 0; i < numThreads; ++i )
  {
    workerThreads_.push_back( new Thread( &dnsWorkerThread ) );
    workerThreads_[i]->start();
  }
}

DNSClient::~DNSClient()
{
}

DNSClient::DNSClient( const DNSClient& n )
{
  timeout_ = n.timeout_;
  dnsCache_ = n.dnsCache_;
  queries_ = n.queries_;
  workerThreads_ = n.workerThreads_;
}

void DNSClient::setTimeout( int timeout )
{
  timeoutLock_.writeLock();
  timeout_=timeout;
  timeoutLock_.writeUnlock();
}

int DNSClient::getTimeout( )
{
  timeoutLock_.readLock();
  int tmp = timeout_;
  timeoutLock_.readUnlock();
  return tmp;
}

std::string DNSClient::lookup( std::string name, bool isBlocking )
{
  std::string answer = checkCache( name );
  if( answer.size() > 0 )
  {
    return answer;
  }
  Mutex* mutex = NULL;
  if( isBlocking )
  {
    mutex = new Mutex; 
    mutex.lock();
  }

  DNSQuery dnsQuery;
  dnsQuery.waiting = mutex;
  dnsQuery.name = name;
  queriesLock_.lock();
  queries_.push_back( dnsQuery );
  queriesLock_.unlock();

  if( isBlocking )
  {
    mutex.lock();
  }


  return checkCache( name );

}
