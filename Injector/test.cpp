
#include "injector.h"


int main( int argc, char **argv )
{
	char sameArray[] = "sameArrayssssss";
	PacketBuffer::PacketBuffer packetBuffer((uint8_t*) sameArray, 15);
	Injector::Injector injector("wmaster0", packetBuffer);
	injector.inject();
	char aVar[] = "aVar";
	PacketBuffer::PacketBuffer aPacketBuffer((uint8_t*) aVar, 4);
	Injector::Injector anInjector("wmaster0", aPacketBuffer);
	anInjector.inject();
	DevicesLookup::DevicesLookup devs; // = new Devices::Devices();
	pcap_t *handle;
	char errbuf[PCAP_ERRBUF_SIZE];


	devs.printAllDevices();
	for (int i = 0; i < 6; i++)
		if (devs[i] != NULL)
			std::cout << "Name of device " << i << ": "<< devs[i]->name << std::endl;
		else	/* if (devs[i] == NULL) */
			std::cout << "Device " << i << " doesn't exist or is not active" << std::endl;

	std::cout << "Device with name is " << devs["eth0"]->name << std::endl;

	handle = pcap_open_live(devs[1]->name, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		std::cout << "Couldn't open device " << devs[0] << std::endl;
		return(2);
	}

	// delete devs;

	std::cout << sameArray << std::endl;
	pcap_inject(handle, sameArray, 15);
	pcap_close(handle);

//	delete handle;
//	delete[] errbuf;
//	delete[] someArray;

	return 0;
}
