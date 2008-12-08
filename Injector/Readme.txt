Packet Injector
---------------

The packet injector is used to inject packets into the network through a selected device. It is implemented in the Injector class written in injector.h and injector.cpp.


Injecting A Packet
------------------

Assuming device “wmaster0” exists, the example below shows how to use the Injector class and how to inject a packet into the network. First, an array of characters is declared and initialized. Next, the injector object is created. Finally, the injecting is ready to be performed.

char someArray[] = "some array";
PacketBuffer::PacketBuffer packetBuffer((uint8_t*) someArray, 10);
Injector::Injector injector("wmaster0", packetBuffer);
injector.inject();


Make
----

Type "make" in command prompt to make the executable.
Type "./test" to run it.