/* *
 * * injector.cpp
 * *    Pcap Project
 * *
 * * This program is free software: you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation, either version 3 of the License, or
 * * (at your option) any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */


#include "injector.h"


Injector::Injector(std::string deviceName, Packet::Packet packet)
{
	dev.setDevice(deviceName, 1);
	handle = pcap_open_live(dev.getDevice().c_str(), BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL)
	{
		std::cout << "Couldn't open device " << dev.getDevice() << std::endl;
		exit(2);
	}
	this->packet = packet;
	this->packetBuffer = packet.makePacket();
}


int Injector::inject()
{
	return pcap_inject(handle, packetBuffer.getBuffer(), packetBuffer.size());
}


Injector::~Injector()
{
	pcap_close(handle);
}
