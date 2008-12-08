/* *
 * * device.cpp
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


#include "device.h"


DevicesLookup Device::devicesLookup;
Device::Device()
{
}

Device::Device(std::string dev, int isDev)
{
  Device::setDevice(dev, isDev);
}

void Device::setDevice(std::string dev, int isDev)
{
	this->dev = dev;
	this->isDev = isDev;
}

std::string Device::getDevice()
{
	return this->dev;
}

int Device::isDevice()
{
	return this->isDev;
}

int Device::isValid()
{
        return devicesLookup.isValid(this->getDevice());
}

Device::~Device()
{
}
