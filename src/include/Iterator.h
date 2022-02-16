/**
 * @brief   Implementation of iterator for Vector
 */

#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>

template <typename T>
class Iterator
{
public:

   // Common iterator interface
   typedef std::ptrdiff_t difference_type;                    // Difference type used calculated distance between iterators
   typedef T value_type;                                      // Value type the iterator points to
   typedef T* pointer;                                        // Pointer to the value type
   typedef T& reference;                                      // Reference to the value type
   typedef std::bidirectional_iterator_tag iterator_category; // Iterator category

   /**
    * @brief   Default constructor
    */
   Iterator()
      : current_{nullptr} {   }

   /**
    * @brief Construct a new Iterator object
    * @param[in]   Value   
    */
   Iterator(T* Value)
      : current_{Value} {   }

   Iterator& operator==(const Iterator& Other)
   {
      this->current_ = Other.current_;
      return *this;
   }

   /**
    * @brief 
    * @return pointer
    */
   T& operator*() const // typename Iterator::reference
   {
      return *this->current_;
   }

   bool operator!=(const Iterator& Other)
   {
      return this->current_ != Other.current_;
   }

   /**
    * @brief 
    * @return Iterator& 
    */
   Iterator& operator++() // ++it
   {
      ++this->current_;
      return *this;
   }

private:
   T* current_; // The painter to the vector data
};

#endif // ITERATOR_H