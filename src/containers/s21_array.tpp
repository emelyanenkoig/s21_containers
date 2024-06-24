#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP

namespace s21 {

template <typename T, size_t S>
Array<T, S>::Array() {
  if (S == 0) {
    array = nullptr;
  } else {
    array = new value_type[S]{};
  }
}

template <typename T, size_t S>
Array<T, S>::Array(const Array &a) {
  array = new value_type[a.size()];
  for (size_type i = 0; i < S; ++i) {
    array[i] = a.array[i];
  }
}

template <typename T, size_t S>
Array<T, S>::Array(Array &&a) {
  array = a.array;
  a.array = nullptr;
}
template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::operator[](
    size_type pos) const {
  return array[pos];
}

template <typename T, size_t S>
typename Array<T, S>::reference Array<T, S>::operator[](size_type pos) {
  return array[pos];
}

template <typename T, size_t S>
typename Array<T, S>::size_type Array<T, S>::size() const noexcept {
  return S;
}

template <typename T, std::size_t S>
Array<T, S>::Array(const std::initializer_list<value_type> &items)
    : array(new value_type[S]) {
  std::copy(items.begin(), items.end(), array);
}

template <typename T, size_t S>
Array<T, S> &Array<T, S>::operator=(const Array &a) {
  if (this != &a) {
    std::copy(a.array, a.array + S, array);
  }
  return *this;
}
template <typename T, size_t S>
bool Array<T, S>::operator==(const Array &other) const {
  bool flag = false;
  for (size_type i = 0; i < S; ++i) {
    if (array[i] != other.array[i]) {
      return flag;
    }
  }
  return flag = true;
}

template <typename T, size_t S>
Array<T, S> &Array<T, S>::operator=(const Array &&a) noexcept {
  for (size_t i = 0; i < S; ++i) {
    array[i] = std::move(a.array[i]);
  }
  return *this;
}

template <typename T, size_t S>
typename Array<T, S>::reference Array<T, S>::at(size_type pos) {
  if (pos >= S) {
    throw std::invalid_argument("Error");
  } else
    return array[pos];
}

template <typename T, size_t S>
typename Array<T, S>::iterator Array<T, S>::data() {
  return array;
}

template <typename T, size_t S>
typename Array<T, S>::iterator Array<T, S>::begin() {
  return array[0];
}

template <typename T, size_t S>
typename Array<T, S>::iterator Array<T, S>::end() {
  return array + S;
}

template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::front() const {
  return array[0];
}

template <typename T, size_t S>
typename Array<T, S>::const_reference Array<T, S>::back() const {
  return array[S - 1];
}

template <typename T, size_t S>
bool Array<T, S>::empty() {
  bool flag = true;
  if (S == 0) {
    return flag;
  } else
    return flag = false;
}

template <typename T, size_t S>
void Array<T, S>::swap(Array<T, S> &a) {
  for (size_type i = 0; i < S; ++i) {
    std::swap(array[i], a.array[i]);
  }
}
template <typename T, size_t S>
typename Array<T, S>::size_type Array<T, S>::max_size() const noexcept {
  return S;
}

template <typename T, size_t S>
void Array<T, S>::fill(const_reference value) {
  for (size_type i = 0; i < size(); ++i) {
    array[i] = value;
  }
}

template <typename T, size_t S>
Array<T, S>::~Array() {
  delete[] array;
}

}  // namespace s21
#endif  // S21_ARRAY_CPP
