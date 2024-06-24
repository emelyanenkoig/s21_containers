#ifndef __S21_SET_H__
#define __S21_SET_H__

#define DEF 0

#include "tree/s21_tree.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, int>::iterator;
  using const_iterator = typename BinaryTree<Key, int>::const_iterator;
  using size_type = size_t;

  set() = default;
  set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }
  set(set& s) {
    // std::pair<int, int> pair;
    for (auto it = s.begin(); it != s.end(); ++it) {
      insert(*it);
    }
  }
  set(set&& s) : tree(std::move(s.tree)) {}
  ~set() = default;

  set& operator=(set& s) {
    if (this != &s) {
      for (auto it = s.begin(); it != s.end(); ++it) {
        insert(*it);
      }
    }
    return *this;
  }

  set& operator=(set&& s) {
    if (this != &s) {
      tree = std::move(s.tree);
    }
    return *this;
  }

  Key& operator*(iterator it) const { return std::ref(it.current->key); }

  // Iterators
  iterator begin() { return tree.begin(); }
  iterator end() { return tree.end(); }

  // Capacity
  bool empty() { return tree.empty(); }
  size_type size() { return tree.size(); }
  size_type max_size() { return tree.max_size(); }

  // Modifiers
  void clear() { tree.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = tree.insert(value, DEF);
    return std::make_pair(iterator(result.first), result.second);
  }

  void erase(iterator pos) {
    if (pos == tree.end()) {
      throw std::out_of_range("set::erase()");
    }
    tree.erase(pos);
  }

  void swap(set& other) { tree.swap(other.tree); }

  void merge(set& other) {
    for (auto&& item : other) {
      insert(std::move(item));
    }
  }

  // Lookup
  iterator find(const Key& key) { return tree.find(key); }
  bool contains(const Key& key) { return tree.find(key) != tree.end(); }

 private:
  BinaryTree<Key, int> tree;
};

}  // namespace s21

#endif  // __S21_SET_H__