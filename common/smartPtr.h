#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>
#include <stdexcept>

class SmartPtrNULL;

/*! ***************************************************************
	\class SmartPtr
	\brief A class for handling dynamically allocated pointers to data

	This class works similarly to that of the auto pointer stuff in the STL with
	some important differences. The first is that mulitple instances of SmartPtr can
	represent the same data so long as the data is always handled from within the
	SmartPtr Object or the data is used while a SmartPtr object containing the data
	is still in scope.

	Example Use:
    SmartPtr< data* > dataPtr( new Data() );
    SmartPtr< data* > dataPtr2( dataPtr ); //we now have two SmartPtr that manipulate the SAME data.

    //dataPtr3 below refers to a seperate instance of the data
    SmartPtr< data* > dataPtr3( dataPtr.copy() );

    //changing the data in dataPtr changes the data in dataPtr2, however dataPtr3 doesn't effect
    //dataPtr or dataPtr2.

 NULL Pointers :
  NULL pointers can be created with the default constructor.
  NULL Pointer Examples:

    SmartPtr<int> intptr; //Null pointer

  This null pointer can be given a value in one of two ways.

    intptr = new int(0);

  or by assigning another smartPtr<int>

    smartPtr<int> intptr2( new int(1) );
    intptr = intptr2;

  Null pointers can't be used by any of the accessor functions (operator*, operator->,
  or the casting operator). If there is an attempt to use these functions on the
  SmartPtr SmartPtrNULL exception is thrown.
 *******************************************************************/


template <class T > class SmartPtr
{
	public:

    //! default constructor (CREATES NULL PTR)
    /*! This constructor is to be used by the SmartPtr class and by user code only to create NULL Ptr.
     This is used in the copy function to quickly generate a new SmartPtr. This is not how the user
      should create a SmartPtr with data, however a null SmartPtr can turn into a SmartPtr that has
      data by using the assignment operator (operator=).
     */
    SmartPtr()
    {
      count_ = new int(1);
      //countMutex_ = new QMutex();
      ptr_ = NULL;
    }

    //! SmartPtr Constructor
    /*!
      \param ptr a pointer to data of type T.
    */
    inline SmartPtr( T* ptr ):ptr_(ptr), count_( new int(1) )//, countMutex_( new QMutex() )
    {
    }

		//! SmartPtr Copy Constructor
		/*!
			Copies a SmartPtr. The new smart pointer manipulates the SAME data as the previous
			instance of the smart point. Additionally if the previous smart pointer is still in
			scope when this pointer goes out of scope it will be able to still modify the data.
		 */
		inline SmartPtr( const SmartPtr& n )
		{
      //QMutexLocker lock( n.countMutex_ );
      //countMutex_ = n.countMutex_;
			count_ = n.count_;
			(*count_) ++;
			ptr_ = n.ptr_;
		}

		//! SmartPtr Destructor
		/*!
			Destroies the SmartPtr. If this is the last smartptr pointing to the object then the smartptr
			deletes all the data. If not it decrements the count.
		 */
		virtual inline ~SmartPtr()
		{
      //QMutexLocker lock( countMutex_ );
			if( *count_ <= 1 )
			{ //last remaining copy delete everything
        //lock.unlock();
        //delete countMutex_;
				delete count_;
				delete ptr_;
			}
			else
			{
				(*count_) -- ;
			}
		}

    //! SmartPtr equals operator
    /*!
      Cleans up current smartPtr before pointing to new data.
    */
    virtual SmartPtr& operator=( const SmartPtr &sp )
    {
      if( sp.ptr_ == ptr_ )
        return *this;
      //QMutexLocker lock( countMutex_ );
      if( *count_ <= 1 )
      {
        //lock.unlock();
        //delete countMutex_;
        delete count_;
        if( ptr_ != NULL )
          delete ptr_;
      }
      else
      {
        (*count_)--;
        //lock.unlock();
      }
      count_ = sp.count_;
      //countMutex_ = sp.countMutex_;
      ptr_ = sp.ptr_;
      //QMutexLocker lock2( countMutex_ );
      (*count_)++;
      return *this;
    }

    //! Returns true if NULL pointer
    /*!
      Allows the user to check if the pointer is NULL. If a NULL pointer is accessed via an
      accessor function the SmartPtrNULL exception will be thrown.
    */
    inline bool isNull() const
    {

      return ( ptr_ == NULL );
    }


		//! copies the smartpointers data to a new SmartPtr.
		/*!
			By copy we get a new data using the data's copy constructor. This data is independent of
			the data held by "this" SmartPtr.
		 */
		inline SmartPtr<T> copy() const
		{
      if( ptr_ == NULL )
        return SmartPtr<T>();

			SmartPtr< T > newPtr;
			newPtr.ptr_ = new T( *ptr_ );
			return newPtr;
		}

		//! Dereference operator
    /*!
      \throws SmartPtrNULL if NULL pointer
    */
    inline T& operator*() const
		{
      checkNULL();
			return *const_cast<T*>( ptr_ );
		}

    //! Dereference accessor operator
    /*!
      \throws SmartPtrNULL if NULL pointer
    */
		inline T* operator->() const
		{
      checkNULL();
			return const_cast<T*>(ptr_);
		}

		//! Cast operator
		/*!
			Implements pointer semantics. Because of this function you can pass a SmartPtr<T> to a function where  T* is required. 
      \throws SmartPtrNULL if NULL pointer
    */
		inline operator T*() const
		{
      checkNULL();
			return  const_cast<T*>( ptr_ );
		}

		//! Data Retrevial Function
		/*!
			Gives the user access to the data.
      \throws SmartPtrNULL if NULL pointer
		 */
		inline T* data() const
		{
      checkNULL();
			return const_cast<T*>( ptr_ );
		}

	private:
		//! private pointer to data
		T* ptr_;
		//! private count of SmartPtr's pointing to ptr_
		int* count_;
		//! private mutex protecting the count in multithreaded applications
    //QMutex* countMutex_;

    //private functions
    //! If Null throws exception
    void checkNULL() const
    {
      if( ptr_ == NULL )
        throw SmartPtrNULL();
    }

};

/*!
  \class SmartPtrNULL
  \brief exception class for accessor use of NULL ptr in smart point class

  If a NULL pointer object accesses a accessor function the SmartPtr class throws
  this object.

  Uses std::runtime_error as base class. Doesn't reimplement any functions or add any new
  functionality. Simply adds a new name so that code is more readable.
*/
class SmartPtrNULL : public std::runtime_error
{
  public:
    SmartPtrNULL( const std::string &what = "NULL SmartPtr" ) : runtime_error( what )
    {
    }
};

#endif // SMARTPTR_H
