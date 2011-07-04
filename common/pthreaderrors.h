#ifndef PTHREADERRORS_H
#define PTHREADERRORS_H

#include <pthread.h>
#include <errno.h>
#include <stdexcept>

namespace pthread
{

void checkConditionError( const int &err );

void checkMutexError( const int &err );

}
#endif // PTHREADERRORS_H
