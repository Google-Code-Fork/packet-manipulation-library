/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra SPAWAR Atlantic
 *
 * This file is a part of PacMan.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*****************************************************************
Last Edited:
Apr 6, 2011  --- Jeff Scaparra



*****************************************************************/


/** \file device.cpp
 * This is the definition for the class Packet 
 */

#include "device.h"


Device::Device()
{
}

Device::Device( const std::string &dev, const bool &isDev )
{
        Device::setDevice(dev, isDev);
}

void Device::setDevice( const std::string &dev, const bool &isDev )
{
	this->dev = dev;
	this->isDev = isDev;
}

std::string Device::device() const
{
	return this->dev;
}

bool Device::isDevice() const
{
	return this->isDev;
}

bool Device::isValid() const
{
        DevicesLookup::DevicesLookup deviceslookup;
        return deviceslookup.isValid(this->device());
}

bool Device::isLoopback() const
{
	DevicesLookup lookup;

}

std::string Device::address() const
{

}

std::string Device::addressFamily() const
{

}

std::string Device::netmask() const
{

}

Device::~Device()
{
}


