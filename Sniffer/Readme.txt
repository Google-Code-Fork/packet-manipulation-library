Packet Sniffer:
This is used for performing follownig tasks:
1. Sniffing packets from any given device (ethernet, wireless)
2. Reading packets from a pcap file as input
3. Dumping packets to a doubly-ended-queue
4. Dumping packets to a pcap file 
5. Filter incoming packets

Sniffer class is implemented as a thread. In order to start and stop sniffing, you just need to use 'start' and 'stop' member functions (like a thread).
Go through documentation of sniffer for detailed understanding of various other member functions and variables of sniffer class.

