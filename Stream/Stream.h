/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011 Jeff Scaparra
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


#ifndef STREAM_H
#define STREAM_H

#include <string>
#include "../Packet/packet.h"
#include <time.h>

class Stream
{
	public:
  Stream() {};
  virtual ~Stream() {};
  virtual std::string name( ) const;
  virtual void processPacket( const Packet &p );
  virtual time_t lastAccess() const;
};

#endif
