/* 

Name: Spencer Owens
Class: 23F CS-311 Data Structures and Algorithms
Assignment: Linked Lists (Assignment 6)
Created: 2023-Nov-06
Updated: 2023-Nov-06
File Name: da6.hpp
Current Version: 1
File Function: 
  Write a template
  referencing Linked List nodes via unique_ptr, creating nodes using make_unique, or functions push_front in llnode2.hpp
  No using new or delete, you may use anything from C++ STL

  Excersise A: Write an efficient reversing function for a linked list.
  Excersise B: Write a class template that uses a linked list to hold an associative data set making use of smart-pointers, while signaling errors using exceptions.
    Store data using key-value pairs, this is called associative dataset
    Call the class "slowMap" as such slowMap<string, int> with only 1 data member = unique_ptr<LLNode2<KVTYPE>>
    KVTYPE is a struct or pair


Version History:
- v1:

*/

#ifndef FILE_DA6_HPP_INCLUDED
#define FILE_DA6_HPP_INCLUDED

#include "llnode2.hpp"
#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::copy, std::move, std::move_backward, std::fill
#include <memory>
// For std::unique_ptr, std::make_unique
#include <stdexcept>
// For std::out_of_range
#include <cassert>
// For assert

// Excercise A
template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> & head){
  // Given a unique pointer, an empty unique pointer if the list is empty, and reverses it and points to the new list by reference
  // Performs no value type operations, all in-place, runs linear time
  std::unique_ptr<LLNode2<ValType>> prev = nullptr;
  std::unique_ptr<LLNode2<ValType>> next = nullptr;

  LLNode2<ValType>* curr = head.get();

  while (curr){
    next = std::move(curr->_next); // 
    curr->_next = std::move(prev);
    prev = std::move(head);
    head = std::move(next);
    curr = head.get();
  }

  head = std::move(prev);
}

// Excercise B
template<typename KeyType, typename DataType>
class SlowMap {
public:
  //Define the key-value pair structure
  struct KVPair {
    KeyType key;
    DataType data;
    KVPair(KeyType k, DataType d) : key(std::move(k)), data(std::move(d)) {}
  };

  // Default Constructor
  SlowMap() : _head(nullptr) {}

  // Deconstructor
  ~SlowMap() = default;

  // Size Function
  size_t size() const {
    size_t size_temp = 0;
    auto curr = _head.get();
    while (curr != nullptr) {
      size_temp++;
    }
    return size_temp;
  }

  // Empty function
  bool empty() const {
    if (_head == nullptr) return true;
    else return false;
  }

  // Present function: Return value is true is a key equal to that given lies in the stored dataset
  bool present(const KeyType & key) const {
    auto curr = _head.get();
    while (curr != nullptr) {
      if (curr->kv.key == key) {
        // Found the key, return a reference to the associated value
        return true;
      }
    }
    return false;
  }

  // Get function: If an equal key lies in the stored data set, return the associated value
  // otherwise std::out_of_range is thrown with the what member set to some appropriate human-readable string
  DataType & get(const KeyType & key) {
    auto curr = _head.get();
    while (curr != nullptr) {
      if (curr->kv.key == key) {
        // Found the key, return a reference to the associated value
        return curr->kv.data;
      }
      curr = curr->next.get();
    }
    // Key not found, throw exception
    std::string errorMsg = "Key not found in SlowMap";
    throw std::out_of_range(errorMsg);
  }

  // Const Get function
  const DataType & get(const KeyType & key) const {
    auto curr = _head.get();
    while (curr != nullptr) {
      if (curr->kv.key == key) {
        // Found the key, return a reference to the associated value
        return curr->kv.data;
      }
      curr = curr->next.get();
    }
    // Key not found, throw exception
    std::string errorMsg = "Key not found in SlowMap";
    throw std::out_of_range(errorMsg);
  }

  // If an equal key does not lie in the dataset, then the key-value pair is inserted, if it does exist, then the existing pair is replaced with that given
  void set(const KeyType & key, const DataType & data) {
    for (auto curr = _head.get(); curr != nullptr; curr = curr->next.get()) {
      if (curr->kv.key == key) {
        // Key found, update data
        curr->kv.data = data;
        return;
      }

      // Key not found, need to add new pair
      _head = std::make_unique<LLNode>(key, data, std::move(_head));
    }
  }

  // If a key is matched, remove the pair
  void erase(const KeyType & key) {
    // Removing head, or empty list.
    if (!_head || _head->kv.key == key) {
      _head = std::move(_head->next);
      return;
    }

    // General case: traverse the list to find the node to remove
    for (auto curr = _head.get(); curr->next; curr = curr->next.get()){
      if (curr->next->kv.key == key) {
        // Remove the node
        curr->next = std::move(curr->next->next);
        return;
      }
    }
  }

  // Passed function is expected to take two parameters, and is called on every pair in the dataset
  template<typename Func>
  void traverse(Func f) {
    for (auto curr = _head.get(); curr != nullptr; curr = curr->next.get()) {
      f(curr->kv.key, curr->kv.data);
    }
    return;
  }

  // Delete Copy Ctor, Move Ctor, Copy assignment, Move assignment
  SlowMap(const SlowMap & other) = delete;
  SlowMap & operator=(const SlowMap & other) = delete;
  SlowMap(SlowMap && other) = delete;
  SlowMap & operator=(SlowMap && other) = delete;

private:
  // One and only one data member which is of type unique_ptr<LLNode2<KVTYPE>>, where KVTYPE is a type that can hold a single key-value pair (e.g., an appropriate std::pair or struct)
  struct LLNode {
    KVPair kv;
    std::unique_ptr<LLNode> next;
    LLNode(KeyType k, DataType d, std::unique_ptr<LLNode> n = nullptr)
      : kv(std::move(k), std::move(d)), next(std::move(n)) {}
  };

  std::unique_ptr<LLNode> _head; // Pointer to the head
};

#endif // #ifndef FILE_DA6_HPP_INCLUDED