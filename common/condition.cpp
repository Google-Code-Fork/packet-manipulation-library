/**
 * * PacMan - Packet Manipulation Library
 * * Copyright (C) 2011 Jeff Scaparra
 * *
 * * This file is a part of PacMan.
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

#include "threads.h"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

Condition::Condition( )
{
  cond_attr_ = new pthread_condattr_t;
  pthread_condattr_init(cond_attr_);

  cond_ = new pthread_cond_t;
  int err = pthread_cond_init( cond_, cond_attr_);
  if( err )
    throw std::runtime_error( "Can not init cond" );
}

Condition::~Condition( )
{
  int err = pthread_cond_destroy( cond_ );
  if( err == EINVAL )
  {
    std::cerr << "Condition dtor(): cond argument is invalid" << std::endl;
    std::abort();
  }

  if( err == EBUSY )
  {
    std::cerr << "Condition dtor(): some threads are currently waiting on cond" << std::endl;
    std::abort();
  }

  pthread_condattr_destroy( cond_attr_ );
  delete cond_;
  delete cond_attr_;
}

void Condition::signal()
{
  int err = pthread_cond_signal( cond_ );
  if( err == EINVAL )
    throw std::runtime_error( "cond argument is invalid" );
}

void Condition::broadcast()
{
  int err = pthread_cond_broadcast( cond_ );
  if( err == EINVAL )
    throw std::runtime_error( "cond argument is invalid" );
}

void Condition::wait(Mutex &mutex)
{
  int err = pthread_cond_wait( cond_, mutex.mutex_ );
  if( err == EINVAL )
    throw std::runtime_error( "cond argument is invalid" );
  if( err == ENOMEM )
    throw std::runtime_error( "There was not enough memory to allocate teh statically initialised condition variable." );
}

bool Condition::timeWait(Mutex &mutex, const timespec &waitTime)
{
  int err = pthread_cond_timedwait( cond_, mutex.mutex_, &waitTime );
  if( err == EINVAL )
    throw std::runtime_error( "invalid cond argument" );
  if( err == ENOMEM )
    throw std::runtime_error( "There was not enough memory to allocate teh statically initialised condition variable." );
  if( err == ETIMEDOUT )
    return false;
  return true;
}


