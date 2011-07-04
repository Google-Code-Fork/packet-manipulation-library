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
    void start();
    void stop();
    void setCache( ArpCache *cache );

private:
    Thread listenerThread_;
    ArpCache *cache_;
    Sniffer sniffer_;
    static const std::string k_arp_filter;
};

#endif // ARPLISTENER_H
