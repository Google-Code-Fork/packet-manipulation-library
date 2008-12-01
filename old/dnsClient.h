#ifndef DNSCLIENT_H
#define DNSCLIENT_H

#include <string>
#include <deque>
#include <map>
#include "threads.h" 

typedef struct DNSQuery
{
  std::string name;
  Mutex* waiting; //a if the lookup is blocking it will wait on this mutex
} DNSQuery;

typedef struct WorkerThreadData
{
  std::map< std::string > *dnsCache;
  ReaderWriterLock *dnsCacheLock;
  Mutex* queriesLock;
  Semaphore *queryCount;
  std::deque< DNSQuery > queries;
}WorkerThreadData;

class DNSClient 
{
  public:
    DNSClient( int numThreads=5, int timeout=2 );
    virtual ~DNSClient( );
    DNSClient( const DNSClient& n );
    void setTimeout( int timeout );
    int getTimeout( );

    std::string lookup( std::string name, bool isBlocking=true );
    void flushDNSCache();


  private:
    
    ReaderWriterLock timeoutLock_;
    int timeout_;
    Mutex queriesLock_;
    Semaphore queryCount_;
    std::deque< DNSQuery > queries_;
    ReaderWriterLock dnsCacheLock_;
    std::map< std::string > dnsCache_;
    std::vector< Threads* > workerThreads_;

};

#endif
