#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

//Taken from Item 6 of Effective C++
//By private inheritance of this class, classes will no longer be copyable.
//Additionally, any errors will be found at compile time.

class Uncopyable
{
  protected:
  Uncopyable() {}
  ~Uncopyable() {}

  private:
  Uncopyable( const Uncopyable& );
  Uncopyable& operator=( const Uncopyable& );
};


#endif // UNCOPYABLE_H
