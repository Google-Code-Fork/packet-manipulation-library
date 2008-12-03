This is the packet parser and generator portion of the project.

We have modeled the packets after the TCP/IP model.

APPLICATION LAYER - DNS HTTP SMTP ... 
TRANSPORT LAYER - UDP TCP ICMP IGMP ...
INTERNET LAYER - IPv4 IPv5 IPv6 ...
LINK LAYER - ETHERNET 802.11 Token Ring...

Currently Supported Protocols include:
Ethernet
IPv4
TCP
UDP
Raw

*** Packet Creation ***

* Automatic Creation from a Buffer *

One way to build a packet is from a sniffer. Once the sniffer has received a
packet it will generate a PacketBuffer that can be use in conjunction with the
PacketBuilder class to generate a packet.

The PacketBuffer class is used to store byte buffers that represent packets so
that we can still use the old interfaces for pcap.

To generate a packet from a vector of bytes as given from a pcap session one can
use the PacketBuilder class:

  Example:
    
  PacketBuffer pbuff;
  //fill the PacketBuffer with data
  PacketBuilder pbuid;
  Packet packet = pbuild.buildPacket<Ethernet>( pbuff );

This example shows a packet being built from the Ethernet header up. If our
buffer had only captured the ip headers onward we could still generate a packet
without a link layer by calling buildPacket<IPv4> instead of
buildPacket<Ethernet>.

* Manual Creation of a Packet *

The second way a user can generate a packet is by creating the headers and
adding them to the Packet Manually. 

  Example:

  Ethernet e;
  e.setType( ethernetProtocol::ETH_P_IP );
  //set other ethernet feilds (addresses etc..) 
  IPv4 ip;
  ip.setProtocol( ipProtocols::IPPROTO_TCP );
  //set addresses and other options
  TCP tcp;
  //set TCP header feilds
  std:vector< uint8_t > data; //put payload of packet here
  Raw raw;
  raw.setData( data );

  Packet p;
  p.pushBackLink( e ); //sets e as the link layer
  p.pushBackInet( ip ); //sets ip as the internet layer
  p.pushBackTrans( tcp ); //set tcp as the transport layer
  p.pushBackApp( raw ); //sets the raw data as the application layer

*** Parsing a Packet **

Once a packet has been generated it might be useful to be able to examine the
different parts of the packet.

Because of encapsulation there could be many link layer headers. This will
become more and more apparent as this library grows and incorporates more
protocols. An example of this would be an arp packet. ARP is a link layer
protocol that is on top of ethernet. In this manner the linkLayer vector in
Packet would have a size of two. If a user tries to retreive data from the
Packet and uses the wrong type an exception will be thrown. Because of this a
test is needed to ensure that the data is what a user thinks that it is. Below
is an example of a test to see if the first header in the linklayer of the
packet is Ethernet.

Example: 



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
