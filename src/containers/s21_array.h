#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T, size_t S>
class Array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = const T*;
  using size_type = size_t;

  Array();
  Array(const Array& a);
  Array(Array&& a);
  ~Array();
  Array& operator=(const Array& a);
  Array(std::initializer_list<value_type> const& items);
  Array& operator=(const Array&& a) noexcept;
  const_reference operator[](size_type pos) const;
  reference operator[](size_type pos);
  size_type size() const noexcept;
  reference at(size_type pos);
  iterator data();
  iterator begin();
  iterator end();
  const_reference front() const;
  const_reference back() const;
  bool empty();
  void swap(Array& a);
  bool operator==(const Array& other) const;
  size_type max_size() const noexcept;
  void fill(const_reference value);

 private:
  value_type* array;
};
}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_ARRAY_H
