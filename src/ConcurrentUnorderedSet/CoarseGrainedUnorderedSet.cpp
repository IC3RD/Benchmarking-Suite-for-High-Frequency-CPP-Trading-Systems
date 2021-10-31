template <typename T>
void CoarseGrainedUnorderedSet<T>::insert(T elem) {
  recursive_mutex_.lock();
  set_.insert(elem);
  recursive_mutex_.unlock();
}

template <typename T>
void CoarseGrainedUnorderedSet<T>::erase(T elem) {
  recursive_mutex_.lock();
  set_.erase(elem);
  recursive_mutex_.unlock();
}

template <typename T>
bool CoarseGrainedUnorderedSet<T>::contains(T elem) {
  recursive_mutex_.lock();
  bool found = set_.find(elem) != set_.end();
  recursive_mutex_.unlock();
  return found;
}

template <typename T>
void CoarseGrainedUnorderedSet<T>::lock() {
  recursive_mutex_.lock();
}

template <typename T>
void CoarseGrainedUnorderedSet<T>::unlock() {
  recursive_mutex_.unlock();
}
