#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>


// namespace {
// //code wouldn't work with this for some reason so I commented it

// // // Internal method to test if a positive number is prime.
// bool IsPrime(size_t n) {
//   if( n == 2 || n == 3 )
//     return true;
  
//   if( n == 1 || n % 2 == 0 )
//     return false;
  
//   for( int i = 3; i * i <= n; i += 2 )
//     if( n % i == 0 )
//       return false;
  
//   return true;
// }


// // Internal method to return a prime number at least as large as n.
// int NextPrime(size_t n) {
//   if (n % 2 == 0)
//     ++n;  
//   while (!IsPrime(n)) n += 2;  
//   return n;
// }

// }  // namespace


// Linear probing implementation.
template <typename HashedObj>

class HashTableLinear {
 public:

  size_t currentSize() const
  {
    return current_size_;
  }

  int totalElements() 
  {
    elementCount = 0;
    for(int i = 0; i < current_size_; i++)
    {
      if(IsActive(i)) 
        elementCount++;
    }

    return elementCount;
  }

  int totalProbes(HashedObj& h)
  {
    FindPos(h);
    return probes;
  }

  int totalCollisions() const
  {
    return collisionsCount;
  }
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }
  
  //removed Const here because findPos() is no longer const
  bool Contains(const HashedObj & x) {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
     if (IsActive(current_pos))
    {
       collisionsCount++;
       return false;
    }
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    elementCount++;
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
    {
       collisionsCount++;
       return false;
    }
     
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;
    elementCount++;
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }


 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
//   Q1: The total number of elements in the table (N), the size of the table (T), the load factor (N/T), the
// total number of collisions (C), and the average number of collisions (C/N).

  int elementCount;

  int probes;
  int collisionsCount;
  
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  //used to be a const function, now it's not
  size_t FindPos(const HashedObj & x)  {
    //reset # of probes so it keeps accurate track of probes per entry.
    // One entry's probes are independent from another entry's. 
    probes = 0;
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      probes++;
      current_pos += offset;  // Compute ith probe. For linear offset is always 1.
      //offset += 2; Offset does not change.
      if (current_pos >= array_.size())
	    current_pos -= array_.size();
    }
    
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // LINEAR_PROBING_H
