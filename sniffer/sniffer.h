

#include "snifferData.h"
#include "filterData.h"

void my_callback( uint8_t *args, const struct pcap_pkthdr* pkthdr, const uint8_t* packetCapture );
void* run_sniffer(void* data);

class sniffer : public Thread
{
	private:
		Mutex coutMutex;
		Mutex logMutex;
		std::string outPcapFile_;
		std::string inPcapFile_;
		std::string filter_;
		FilterData *filterData;
		SnifferData snifferData;
		static const std::string logFile;
		static std::ofstream log_stream;

	public:
		sniffer();
		void *packetSniffer();
		void setDevice( std::string device );
		std::string getDevice();
		void setFilter(std::string filter);
		void setOutPcapFile(std::string);
		std::string getOutputPcapFile( );
		void setInputPcapFile(std::string);
		std::string getInputPcapFile();
		Packet popPacket();
		void log( std::string );
		void start( );
		void printDevices();
		std::string iptos(u_long in);
		~sniffer(){ delete filterData; }
};

