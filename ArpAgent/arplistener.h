#ifndef ARPLISTENER_H
#define ARPLISTENER_H

#include "../Sniffer/sniffer.h"
#include "../Packet/packet.h"
#include "arpcache.h"
#include "../common/threads.h"
#include <string>
#include <map>

void* run_listener( void* data );

class ArpListener
{
public:
    ArpListener();
    virtual ~ArpListener();
    void start();
    void stop();
    void setCache( ArpCache *cache );
    void setArpFilter( const std::string &filter );
    std::string arpFilter() const;
    void setDevice( const std::string &device );
    std::string device() const;
    bool isRunning() const;
    //!get notified if you see a certain ip arp ignores the request if an alert already exists
    void waitForResponse( const std::string &ip ); //does not timeout
    void waitForResponse( const std::string &ip, const timespec &timeout ); //has a timeout

private:
    void listenerThread();
    void removeAlert( const std::string &ip );
    void setAlert( const std::string &ip );
    void sendAlert( const std::string &ip ); //send alert and remove from alert queue

private:
    mutable Mutex runningMutex_;
    bool running_;
    Thread listenerThread_;
    ArpCache *cache_;
    Sniffer sniffer_;
    std::string arpFilter_;
    std::string device_;
    mutable Mutex alertMutex_;
    std::map< std::string, std::pair< Semaphore*, Condition* > > alerts_; //bool multiple requests? broadcast or signal

    static const std::string k_arp_filter;

    friend void* run_listener( void* data );
};

#endif // ARPLISTENER_H
