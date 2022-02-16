/**
 * @brief   Implementation of std::vector in C++
 */

#ifndef VECTOR_H
#define VECTOR_H

// #include <cstdint>

#include "Iterator.h"

/********************************************************
*                      Declaration                      *
********************************************************/

namespace Stl
{

/**
 * @brief        Vector data structure
 * @details      A simple implementation of a vector data structure
 * @tparam   T   Type of data stored in vector
 */
template <typename T>
class Vector
{
public:
   typedef Iterator<T> iterator;
   typedef Iterator<const T> const_iterator;

   /****** Constructors && Destructor ******/

   /**
    * @brief   Default constructor
    */
   Vector();


   /**
    * @brief       Constructs the container with Count default-inserted instances of T.
    * @param[in]   Count   The number of elements in the Vector.
    */
   explicit Vector(size_t Count);


   /**
    * @brief Destructs the Vector
    */
   ~Vector();


   /**
    * @brief   Returns true if the Vector contains no element, and false otherwise.
    */
   bool is_empty() const;


   /**
    * @brief    Returns the number of elements in the Vector.
    */
   size_t size() const;


   /**
    * @brief   Adds Value to the end of the Vector.
    */
   void push_back(const T& Value);


   /**
    * @brief   Returns the object at the index Index in the Vector, with no bounds-checking.
    */
   T& operator[](size_t Index);


   /**
    * @brief    Returns an iterator pointing to the first element in the Vector.
    * @return   iterator
    */
   iterator begin()
   {
      iterator it(this->data_);
      return it;
   }


   /**
    * @brief    Returns an iterator pointing to the following the last element of the Vector.
    * @return   iterator
    */
   iterator end()
   {
      iterator it(this->data_ + this->size_);
      return it;
   }

private:
   /**
    * @brief   Перераспределение памяти под массив
    */
   void add_memory();


   T* data_;         // array that actually stores the elements of the Vector
   size_t size_;     // actual size of the Vector (amount of elements stired)
   size_t capacity_; // available amount of elements that can be stored with current allocation
};

} // namespace Stl



/********************************************************
*                    Implementation                     *
********************************************************/

namespace Stl
{

/****** Constructors && Destructor ******/

template <typename T>
Vector<T>::Vector()
   : data_{nullptr}, size_{0}, capacity_{0} {   }


template <typename T>
Vector<T>::Vector(size_t Count)
   : data_{new T[Count]}, size_{Count}, capacity_{Count} {   }


template <typename T>
Vector<T>::~Vector()
{
   delete[] this->data_;
}


template <typename T>
size_t Vector<T>::size() const
{
   return this->size_;
}


template <typename T>
bool Vector<T>::is_empty() const
{
   return 0 == this->size_;
}


template <typename T>
void Vector<T>::add_memory()
{
   this->capacity_ *= 2;

   T* tmp = this->data_;
   this->data_ = new T[this->capacity_];
   for (size_t i = 0; i < this->size_; ++i)
      this->data_[i] = tmp[i];

   delete[] tmp;
}


template <typename T>
void Vector<T>::push_back(const T& Value)
{
   if (this->size_ >= this->capacity_)
      this->add_memory();

   this->data_[this->size_++] = Value;
}


template <typename T>
T& Vector<T>::operator[](size_t Index)
{
   return this->data_[Index];
}

} // namespace MyStl

#endif // VECTOR_H