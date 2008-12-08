Device
------

To inject a packet into the network, a device has to be open first. For that, Device class is available. The Device class also uses DevicesLookup class that can perform look-up of all devices and store their basic information, such as the names of the devices and their descriptions, and provides a functionality whether a given device exists in the system or not.


Declaring A Device and A Handle
-------------------------------

Here is an example on how to create an instance of Device.

std::string deviceName;
char errbuf[PCAP_ERRBUF_SIZE];     // errbuf is used to store error information when a pcap operation fails
Device::Device dev;

dev.setDevice(deviceName, 1);     // naming the device and giving it a name and a flag that it is a device instead of a Pcap file, in which the flag would be 0
pcap_t *handle = pcap_open_live(dev.getDevice().c_str(), BUFSIZ, 1, 1000, errbuf);


Checking Device Validity
------------------------

Here is an example on how to check whether a device exists. IsValid() returns 1 if device exists in the system, or it returns 0 if it does not.

If (dev.isValid() == 1)
	std::cout << "Device exists in the system." << std::endl;
else
	std::cout << "Device does not exist in the system." << std::endl;

Here is an example on how to check whether the device object holds device data or a Pcap file data. .isDevice() returns 1 if the device object contains a device, or it returns 0 if it contains a Pcap file.

If (dev.isDevice() == 1)
	std::cout << "It is a device." << std::endl;
else
	std::cout << "It is a Pcap file." << std::endl;

Make
----

Type "make" in command prompt to make the executable.
Type "./test" to run it.
