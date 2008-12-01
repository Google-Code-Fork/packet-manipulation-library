This is the packet parser and generator portion of the project.

We have modeled the packets after the TCP/IP model.

APPLICATION LAYER - DNS HTTP SMTP ... 
TRANSPORT LAYER - UDP TCP ICMP IGMP ...
INTERNET LAYER - IPv4 IPv5 IPv6 ...
LINK LAYER - ETHERNET 802.11 Token Ring...

To use the Packet libary 
Packet< Ethernet >( vector< uint8_t > data ); //will parse a packet from a capture

Packet<>(); //will create a packet that can then be added to like:

Ethernet e;
IPv4 ip;
Tcp tcp;
Raw data;
Packet<> p;
p.pushBackLink( e );
p.pushBackInet( ip );
p.pushBackTrans( tcp );
p.pushBackApp( data );

*** If we wanted to encapsulated this in an ipv6 packet

Ethernet e2;
IPv6 ip6;
Packet<> p2;
p2.pushBackLink( e2 );
p2.pushBackInet( ip6 );
p2.pushBackInet( p );

Because different queues are used for each of the layers only the order that
things get pushed on in each layer matters. The order of the layers does not.
