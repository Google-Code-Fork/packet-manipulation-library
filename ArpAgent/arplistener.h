#ifndef ARPLISTENER_H
#define ARPLISTENER_H

#include "../Sniffer/sniffer.h"
#include "../Packet/packet.h"
#include "arpcache.h"
#include "../common/threads.h"
#include <string>

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

private:
    void listenerThread();

private:
    Mutex runningMutex_;
    bool running_;
    Thread listenerThread_;
    ArpCache *cache_;
    Sniffer sniffer_;
    std::string arpFilter_;
    std::string device_;
    static const std::string k_arp_filter;

    friend void* run_listener( void* data );
};

#endif // ARPLISTENER_H
