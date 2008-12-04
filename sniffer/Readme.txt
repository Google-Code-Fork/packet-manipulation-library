Packet Sniffer:
This is used for performing follownig tasks:
1. Sniffing packets from any given device (ethernet, wireless)
2. Reading packets from a pcap file as input
3. Dumping packets to a doubly-ended-queue
4. Dumping packets to a pcap file 
5. Filter incoming packets

---- Sniffer class ----
NAME
	sniffer - Packet sniffer module of PacMan

SYNOPSIS
		#include <sniffer.h>
		
		Member Variables:
        static const std::string logFile
        bool DEBUG
        static std::ofstream log_stream
        Mutex coutMutex
        Mutex logMutex
        std::string outPcapFile_
        std::string inPcapFile_
        std::string filter_
        FilterData *filterData
        SnifferData snifferData
        
		Member Routines:
        void setDevice( std::string device );
        std::string getDevice();
		void *packetSniffer();
        Packet popPacket();
        void setOutPcapFile(std::string);
        std::string getOutputPcapFile( );
        void setInputPcapFile(std::string);
        std::string getInputPcapFile();
        void setFilter(std::string filter);
        void log( std::string );
        void printDevices();
        std::string iptos(u_long in);

DESCRIPTION
	This is Packet sniffer module used for sniffing packets and dumping packets

ROUTINES
	setDevice() is used to set a pcap device for capturing packets. snifferData instance of SnifferData is used to set a member variable 'device_'.
	getDevice() is used to return pcap device name which is currently being used for sniffing.  snifferData instance of SnifferData is used to return device name using member function 'getDevice()'.
	packetSniffer() is used to perform all the sniffing and packet dumping operations. It reads the variable 'inPcapFile_' to find out whether input packets should be sniffed from pcap device or pcap file. 'filter_' variable is used to verify whether incoming packets should be filtered or not. 'outPcapFile_' is used to find whether packets should be dumped in a doubly-ended-queue or a pcap file.
	popPacket() is used to pop out recently sniffed packet from the doubly-ended-queue.
	setOutPcapFile() is used to set 'outPcapFile_' in order to dump packets into a pcap file
	getOutputPcapFile() is used to return 'outPcapFile_' in order to find out pcap file name being currently used for dumping packets.
	setInputPcapFile() is used to set 'inPcapFile_' in order to sniff packets from a pcap file stored in 'inPcapFile_'
	getInputPcapFile() is used to return 'inPcapFile_' in order to find out pcap file name being currently used for sniffing packets.
	setFilter() is used to set the variable 'filter_', in order to identify incoming packet filtering logic.
    log() is used to log/write status updates in the log file.
	printDevices() is used to list all the devices available for sniffing in the system.
    iptos() is used to convert any given ip represented in decimal format to its human-readable string equivalent

