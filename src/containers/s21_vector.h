#ifndef CPP2_S21_CONTAINERS_1_MASTER_VECTOR_H
#define CPP2_S21_CONTAINERS_1_MASTER_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iostream>  //std::endl
#include <limits>

#include "stdexcept"

namespace s21 {
template <typename T>
class Vector {
 public:
  /*  PUBLIC ATTRIBUTES */
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  /* VECTOR MEMBER FUNCTIONS */
  Vector() : vSize(0U), vCapacity(0U), vArr(nullptr) {}

  explicit Vector(size_type n)
      : vSize(n), vCapacity(n), vArr(n ? new value_type[n]() : nullptr) {}

  Vector(std::initializer_list<value_type> const &items)
      : vSize(items.size()), vCapacity(items.size()) {
    vArr = new value_type[items.size()]();
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
      at(i) = *it;
      ++i;
    }
  }

  Vector(const Vector &v)
      : vSize(v.vSize),
        vCapacity(v.vCapacity),
        vArr(new value_type[v.vSize]()) {
    CopyEntryVector(v);
  }

  Vector(Vector &&other) noexcept
      : vSize(other.vSize), vCapacity(other.vCapacity), vArr(other.vArr) {
    other.vSize = 0U;
    other.vCapacity = 0U;
    other.vArr = nullptr;
  }

  ~Vector() {
    CleanArr();
    vArr = nullptr;
    vSize = 0U;
    vCapacity = 0U;
  }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      clear();
      vSize = other.vSize;
      vCapacity = other.vCapacity;
      vArr = new value_type[vSize]();
      CopyEntryVector(other);
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    CleanArr();
    vSize = other.vSize;
    vCapacity = other.vCapacity;
    vArr = other.vArr;
    other.vArr = nullptr;
    other.vSize = 0U;
    other.vCapacity = 0U;
    return *this;
  }

  /* VECTOR ELEMENT ACCESS METHODS */

  reference front() noexcept { return vArr[0]; }
  const_reference front() const { return vArr[0]; }

  reference back() noexcept { return vArr[vSize - 1]; }
  const_reference back() const { return vArr[vSize - 1]; }

  reference operator[](size_type pos) { return vArr[pos]; }
  const_reference operator[](size_type pos) const { return vArr[pos]; }

  reference at(size_type pos) {
    if (pos >= vSize) throw std::out_of_range("Element is out of vector!");
    return vArr[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= vSize) throw std::out_of_range("Element is out of vector!");
    return vArr[pos];
  }

  /* VECTOR ELEMENT ITERATION METHODS */

  iterator data() { return vArr; }
  const_iterator data() const { return vArr; }

  iterator begin() noexcept { return vArr; }
  const_iterator begin() const { return vArr; }

  iterator end() noexcept { return vArr + vSize; }
  const_iterator end() const { return vArr + vSize; }

  /* VECTOR CAPACITY METHODS */

  bool empty() const noexcept { return begin() == end(); }

  size_type size() const noexcept { return vSize; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  size_type capacity() const noexcept { return vCapacity; }

  void reserve(size_type size) {
    if (size > vCapacity) {
      auto new_data = new value_type[size]();

      for (size_type i = 0; i < vSize; ++i) {
        new_data[i] = std::move(vArr[i]);
      }

      CleanArr();
      vArr = new_data;
      vCapacity = size;
    }
  }

  void shrink_to_fit() {
    if (vCapacity > vSize) {
      auto new_data = new value_type[vSize]();

      for (size_type i = 0; i < vSize; ++i) {
        new_data[i] = std::move(vArr[i]);
      }

      CleanArr();
      vArr = new_data;
      vCapacity = vSize;
    }
  }

  /* VECTOR MODIFIERS */

  void clear() noexcept {
    CleanArr();
    vArr = nullptr;
    vSize = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    size_type index = 0;
    if (vSize != 0) {
      index = pos - begin();  // when vSize = 0, begin() can be ub
    }

    if (vCapacity == vSize) {
      if (vCapacity == 0) {
        reserve(1);
      } else {
        reserve(vCapacity * 2);
      }
    }
    ++vSize;
    for (size_type i = vSize - 1; i > index; --i) {
      at(i) = std::move(at(i - 1));
    }
    at(index) = value;

    return begin() + index;
  }

  iterator erase(const_iterator pos) {
    size_type index = 0;
    if (vSize != 0) {
      index = pos - begin();  // when vSize = 0, begin() can be ub
    }
    for (size_type i = index; i < vSize - 1; ++i) {
      at(i) = std::move(at(i + 1));
    }
    --vSize;
    return begin() + index;
  }

  void push_back(const_reference value) {
    if (vCapacity == vSize) {
      if (vCapacity == 0) {
        reserve(1);
      } else {
        reserve(vCapacity * 2);
      }
    }
    ++vSize;
    at(vSize - 1) = value;
  }

  void pop_back() {
    if (vSize > 0) {
      vArr[vSize - 1].~value_type();
      --vSize;
    }
  }

  void swap(Vector &other) {
    std::swap(vArr, other.vArr);
    std::swap(vSize, other.vSize);
    std::swap(vCapacity, other.vCapacity);
  }

 private:
  /*  PRIVATE ATTRIBUTES */
  size_type vSize;
  size_type vCapacity;
  T *vArr;

  /* SUPPORT METHODS */
  void CopyEntryVector(const Vector<T> &entry_vector) {
    for (size_t i = 0; i < entry_vector.vSize; ++i) at(i) = entry_vector.at(i);
  }

  void CleanArr() { delete[] vArr; }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_MASTER_VECTOR_H