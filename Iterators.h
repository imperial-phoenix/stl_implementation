#ifndef ITERATOR_H
#define ITERATOR_H

// #include <cstddef>

template <typename T>
class LegacyIterator
{
public:

   // Common iterator interface
   using value_type = T;                   // Value type the iterator points to
   using pointer = T*;                     // Pointer to the iterator type
   using reference = T&;                   // Reference to the value type
   using difference_type = std::ptrdiff_t; // Difference type used calculated distance between iterators


   /**
    * @brief Construct a new Legacy Iterator object
    * @param[in] p_data
    */
   LegacyIterator(pointer p_data = nullptr) : p_data_{p_data} {   }


   /**
    * @brief    Returns iterator to the next location and returns itself before the increment.
    * @return   LegacyIterator& 
    */
   LegacyIterator& operator++() // ++it
   {
      ++this->p_data_;
      return *this;
   }


   /**
    * @brief    Advances iterator to the next location and returns itself before the increment.
    * @return   LegacyIterator
    */
   LegacyIterator operator++(int) // it++
   {
      LegacyIterator tmp(this->p_data_);
      ++this->p_data_;
      return tmp;
   }


   /**
    * @brief 
    * @return T& 
    */
   reference operator*() const
   {
      return *this->p_data_;
   }

protected:
   pointer p_data_;
};


template <typename T>
class LegacyInputIterator : public LegacyIterator<T>
{
public:

   // Common iterator interface
   using value_type = T;                              // Value type the iterator points to
   using pointer = T*;                                // Pointer to the iterator type
   using reference = T&;                              // Reference to the value type
   using difference_type = std::ptrdiff_t;            // Difference type used calculated distance between iterators
   using iterator_category = std::input_iterator_tag; // Iterator category

   LegacyInputIterator(pointer p_data = nullptr) : LegacyIterator<T>(p_data) {   }

   pointer operator->() const
   {
      return this->p_data_;
   }

   bool operator==(const LegacyInputIterator& other) const
   {
      return (this->p_data_ - other.p_data_) == 0;
   }

   bool operator!=(const LegacyInputIterator& other) const
   {
      return !this->operator==(other);
   }


};


template <typename T>
class LegacyForwardIterator : public LegacyInputIterator<T>
{
public:
   using iterator_category = std::forward_iterator_tag;

   LegacyForwardIterator(T* data) : LegacyInputIterator<T>(data) {   }
};


template <typename T>
class LegacyBidirectionalIterator : public LegacyForwardIterator<T>
{
public:

   // Common iterator interface
   using value_type = T;                              // Value type the iterator points to
   using pointer = T*;                                // Pointer to the iterator type
   using reference = T&;                              // Reference to the value type
   using difference_type = std::ptrdiff_t;            // Difference type used calculated distance between iterators
   using iterator_category = std::bidirectional_iterator_tag;


   LegacyBidirectionalIterator(pointer data = nullptr) : LegacyForwardIterator<T>(data) {   }

   LegacyBidirectionalIterator& operator--()
   {
      --this->p_data_;
      return *this;
   }

   LegacyBidirectionalIterator operator--(int)
   {
      LegacyBidirectionalIterator tmp(*this);
      --this->p_data_;
      return tmp;
   }
};


template <typename T>
class LegacyRandomAccessIterator : public LegacyBidirectionalIterator<T>
{
public:

   // Common iterator interface
   using value_type = T;                              // Value type the iterator points to
   using pointer = T*;                                // Pointer to the iterator type
   using reference = T&;                              // Reference to the value type
   using difference_type = std::ptrdiff_t;            // Difference type used calculated distance between iterators
   using iterator_category = std::random_access_iterator_tag;

   LegacyRandomAccessIterator(pointer data= nullptr) : LegacyBidirectionalIterator<T>(data) {   }

   LegacyRandomAccessIterator& operator+=(difference_type n)
   {
      difference_type m = n;
      if (m >= 0)
      {
         while (m--)
            ++*this;
      }
      else
      {
         while (m++)
            --*this;
      }

      return *this;
   }

   LegacyRandomAccessIterator& operator-=(difference_type n)
   {
      return this->operator+=(-n);
   }

   LegacyRandomAccessIterator operator-(difference_type n) const
   {
      LegacyRandomAccessIterator tmp = *this;
      return tmp -= n;
   }

   friend LegacyRandomAccessIterator operator+(LegacyRandomAccessIterator& Lhs, difference_type n)
   {
      Lhs.p_data_ += n;
      return Lhs;
   }

   friend LegacyRandomAccessIterator operator+(difference_type n, LegacyRandomAccessIterator& Rhs)
   {
      return Rhs + n;
   }

   difference_type operator-(const LegacyRandomAccessIterator& other) const
   {
      return this->p_data_ - other.p_data_;
   }

   bool operator<(const LegacyRandomAccessIterator& other) const
   {
      return other - *this > 0;
   }

   bool operator>(const LegacyRandomAccessIterator& other) const
   {
      return other < *this;
   }

   bool operator>=(const LegacyRandomAccessIterator& other) const
   {
      return !(*this < other);
   }

   bool operator<=(const LegacyRandomAccessIterator& other) const
   {
      return !(*this > other);
   }

   T& operator[](difference_type index)
   {
      return *(this + index);
   }

};

#endif // ITERATOR_H