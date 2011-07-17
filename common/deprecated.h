#ifndef DEPRECATED_H
#define DEPRECATED_H

#ifdef __GNUC__
#define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif

//Example Usage: don't use me any more
//DEPRECATED(void OldFunc(int a, float b));

#endif // DEPRECATED_H
