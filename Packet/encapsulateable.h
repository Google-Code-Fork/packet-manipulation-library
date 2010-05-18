/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2008  Jeff Scaparra, Gaurav Yadav, Andrie Tanusetiawan
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

/** \file encapsulateable.h
 * This is the declaration for the class Encapsulateable
 */

/** \class Encapsulateable 
 * This class is used in conjunction with Packet library
 * This is a interface for the different Packet objects
 */

#ifndef ENCAPSULATEABLE_H
#define ENCAPSULATEABLE_H

#include <vector>
#include "packetBuffer.h"

class Encapsulateable
{
  public:
    //!Forces derived classes to be able to produce PacketBuffers
    virtual PacketBuffer makePacket() const = 0; 
    //!Forces Derived classes to be able to return their size.
    virtual int size() const = 0;

  private:
};


#endif
