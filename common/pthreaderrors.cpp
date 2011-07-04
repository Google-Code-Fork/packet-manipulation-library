#include "pthreaderrors.h"

void pthread::checkConditionError(const int &err)
{
  if( err == 0 )
    return;
  if( err == EINVAL )
  {
    std::runtime_error( "The value condition does not refer to an initialized condition variable." );
  }
}

void pthread::checkMutexError(const int &err)
{
  if ( err == 0 )
    return;
  if ( err == EBUSY)
    throw std::runtime_error( "Can not destroy mutex: Locked by other thread");
  if ( err == EINVAL )
    throw std::runtime_error( "Mutex has invalid value and cannot be destroyed" );
  if ( err == EPERM )
    throw std::runtime_error( "The calling thread does not own mutex" );
  if ( err == EAGAIN )
    throw std::runtime_error( "The mutex could not be acquired because the maximum number of recursive locks for mutex has been exceeded." );
  if ( err == EDEADLK )
    throw std::runtime_error( "The current thread already owns the mutex" );
  if( err )
    throw std::runtime_error( "Can not destroy mutex" );
}
