#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "CoarseGrainedUnorderedSet.h"

void add(CoarseGrainedUnorderedSet<int> &s, int l, int r) {
  for (int i = l; i < r; i++) s.insert(i);
}

int main() {
  CoarseGrainedUnorderedSet<int> s;
  std::vector<std::thread> threads;
  for (size_t i = 0; i < 10; i++) {
    threads.emplace_back(add, std::ref(s), i * 10000, (i + 1) * 10000);
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::cout << "number of elems added is: " << s.size() << std::endl;

  return 0;
}
