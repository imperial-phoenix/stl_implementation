/**
 * @brief   Implementation of std::vector in C++
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>

#include "Iterators.h"
#include "iterator" // for std::distance

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

   using iterator = LegacyRandomAccessIterator<T>;             // Iterator that points to a specific element of type T
   using const_iterator = LegacyRandomAccessIterator<const T>; // Const Itetator

   /****** Constructors && Destructor ******/

   /**
    * @brief   Default constructor
    */
   Vector()
      : data_{nullptr}, size_{0}, capacity_{0} {   }


   /**
    * @brief       Constructs the container with Count default-inserted instances of T.
    * @param[in]   Count   The number of elements in the Vector.
    */
   explicit
   Vector(uint64_t count)
      : data_{new T[count]}, size_{count}, capacity_{count} {   }


   /**
    * @brief       Constructs the Vector with the contents of the initializer list ilist.
    * @param[in]   ilist   initializer list
    */
   Vector(const std::initializer_list<T>& ilist)
      : data_{new T[ilist.size()]}, size_{ilist.size()}, capacity_{ilist.size()}
   {
      for (uint64_t i = 0; i < this->size_; ++i)
         this->data_[i] = *(ilist.begin() + i);
   }


   /**
    * @brief       Constructs the Vector with the contents of the range [first; last).
    * @param[in]   first, last   The range to copy the elements from.
    */
   template <typename InputIt>
   Vector(InputIt first, InputIt last)
   {
      this->size_ = this->capacity_ = std::distance(first, last);
      this->data_ = new T[this->size_];

      for (uint64_t i = 0; i < this->size_; ++i)
         this->data_[i] = *first++;
   }


   /**
    * @brief   Copy constructor
    */
   Vector(const Vector& other)
      : data_{new T[other.size_]}, size_{other.size_}, capacity_{other.capacity_}
   {
      for (uint64_t i = 0; i < this->size_; ++i)
         this->data_[i] = other.data_[i];
   }


   /**
    * @brief Destructs the Vector
    */
   ~Vector() { delete[] this->data_; }


   /****** Operators ******/

   /**
    * @brief   Copy assigment operator
    */
   Vector& operator=(const Vector& other)
   {
      delete[] this->data_;

      this->size_ = other.size_;
      this->capacity_ = other.capacity_;
      this->data_ = new T[this->capacity_];

      for (uint64_t i = 0; i < this->size_; ++i)
         this->data_[i] = other.data_[i];

      return *this;
   }

   /**
    * @brief   Replaces the contents with those idenified by initializer list ilist.
    */
   Vector& operator=(const std::initializer_list<T>& ilist)
   {
      delete[] this->data_;

      this->capacity_ = this->size_ = ilist.size();
      this->data_ = new T[this->size_];

      for (uint64_t i = 0; i < this->size_; ++i)
         this->data_[i] = *(ilist.begin() + i);

      return *this;
   }

   /****** const methods ******/

   /**
    * @brief   Returns true if the Vector contains no element, and false otherwise.
    */
   bool is_empty() const { return 0 == this->size_; }


   /**
    * @brief    Returns the number of elements in the Vector.
    */
   uint64_t size() const { return this->size_; }


   /**
    * @brief   Return the capacity ot the Vector.
    */
   uint64_t capacity() const { return this->capacity_; }


   const T& operator[](uint64_t index) const { return this->data_[index]; }


   const T& at(uint64_t index) const
   {
      if (index < 0 || index >= this->size_)
         throw std::out_of_range("index " + std::to_string(index));

      return this->data_[index];
   }


   /****** modifiers ******/

   /**
    * @brief Remove all elements from the Vector.
    */
   void clear() { this->size_ = 0; }


   /**
    * @brief   Adds Value to the end of the Vector.
    */
   void push_back(const T& Value)
   {
      if (this->size_ >= this->capacity_)
         this->reserve(this->capacity_ * 2);

      this->data_[this->size_++] = Value;
   }


   /**
    * @brief   Removes the element at the end of the Vector.
    */
   void pop_back() { --this->size_; }


   /**
    * @brief   Removes the element at the front of the Vector.
    */
   void pop_front()
   {
      for (uint64_t i = 0; i < this->size_ - 1; ++i)
         this->data_[i] = this->data_[i + 1];

      --this->size_;
   }


   /**
    * @brief   Increases the storage capacity of the Vector to a new_capacity.
    */
   void reserve(uint64_t new_capacity)
   {
      if (this->capacity_ < new_capacity)
         return;

      this->capacity_ = new_capacity;

      T* new_data = new T[this->capacity_];

      for (uint64_t i = 0; i < this->size_; ++i)
         new_data[i] = this->data_[i];

      delete[] this->data_;
      this->data_ = new_data;
   }


   /**
    * @brief   Requests the removal of unused capacity.
    */
   void shrink_to_fit()
   {
      this->capacity_ = this->size_;
      T* new_data = new T[this->capacity_];

      for (uint64_t i = 0; i < this->size_; ++i)
         new_data[i] = this->data_[i];

      delete[] this->data_;
      this->data_ = new_data;
   }


   T& operator[](uint64_t index) { return this->data_[index]; }


   T& at(uint64_t index)
   {
      if (index < 0 || index >= this->size_)
         throw std::out_of_range("index " + std::to_string(index));

      return this->data_[index];
   }


   /****** Iterators ******/

   /**
    * @brief    Returns an iterator pointing to the first element in the Vector.
    */
   iterator begin()
   {
      iterator it(this->data_);
      return it;
   }


   /**
    * @brief    Returns an iterator pointing to the following the last element of the Vector.
    */
   iterator end()
   {
      iterator it(this->data_ + this->size_);
      return it;
   }


   /**
    * @brief Returns a const iterator pointing to the first element in the Vector.
    */
   const_iterator cbegin() const
   {
      const_iterator it(this->data_);
      return it;
   }


   /**
    * @brief Returns a const iterator pointing to the following the last element of the Vector.
    */
   const_iterator cend() const
   {
      const_iterator it(this->data_ + this->size_);
      return it;
   }

private:
   T* data_;           // array that actually stores the elements of the Vector
   uint64_t size_;     // actual size of the Vector (amount of elements stored)
   uint64_t capacity_; // available amount of elements that can be stored with current allocation
};

} // namespace Stl

#endif // VECTOR_H