#pragma once

template <typename T>
class ConcurrentUnorderedSet {
 public:
  virtual void insert(T) = 0;
  virtual void erase(T) = 0;
  virtual bool contains(T) = 0;
};
