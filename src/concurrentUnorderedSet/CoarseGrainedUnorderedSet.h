#pragma once

#include <mutex>
#include <unordered_set>

#include "ConcurrentUnorderedSet.h"

template <typename T>
class CoarseGrainedUnorderedSet : public ConcurrentUnorderedSet<T> {
 public:
  void insert(T);

  void erase(T);

  bool contains(T);

  void lock();

  void unlock();

 private:
  std::recursive_mutex recursive_mutex_;
  std::unordered_set<T> set_;
};

#include "CoarseGrainedUnorderedSet.tpp"