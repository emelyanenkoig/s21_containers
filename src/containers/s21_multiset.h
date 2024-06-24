#ifndef __S21_MULTISET_H__
#define __S21_MULTISET_H__

#define DEF 0

#include "tree/s21_tree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, int>::iterator;
  using const_iterator = typename BinaryTree<Key, int>::const_iterator;
  using size_type = size_t;

  multiset() = default;
  multiset(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& ms) {
    std::pair<Key, int> pair;
    for (auto it = ms.begin(); it != ms.end(); ++it) {
      pair = *it;
      insert(pair.first);
    }
  }
  multiset(multiset&& ms) : tree(std::move(ms.tree)) {}
  ~multiset() = default;

  multiset& operator=(multiset& s) {
    if (this != &s) {
      for (auto it = s.begin(); it != s.end(); ++it) {
        insert(*it);
      }
    }
    return *this;
  }

  multiset& operator=(multiset&& ms) {
    if (this != &ms) {
      tree = std::move(ms.tree);
    }
    return *this;
  }

  // Iterators
  iterator begin() { return tree.begin(); }
  const_iterator begin() const { return tree.begin(); }
  iterator end() { return tree.end(); }
  const_iterator end() const { return tree.end(); }

  // Capacity
  bool empty() { return tree.empty(); }
  size_type size() { return tree.size(); }
  size_type max_size() { return tree.max_size(); }

  // // Modifiers
  void clear() { tree.clear(); }

  iterator insert(const value_type& value) {
    auto result = tree.multiInsert(value, DEF);
    return iterator(result.first);
  }

  void erase(iterator pos) {
    if (pos == tree.end()) {
      throw std::out_of_range("multiset::erase()");
    }
    tree.erase(pos);
  }

  void swap(multiset& other) { tree.swap(other.tree); }

  void merge(multiset& other) {
    for (auto&& item : other) {
      insert(std::move(item));
    }
    other.clear();
  }

  // // Lookup
  size_type count(const Key& key) { return tree.count(key); }
  iterator find(const Key& key) { return tree.find(key); }
  bool contains(const Key& key) { return tree.find(key) != tree.end(); }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return tree.equal_range(key);
  }

  iterator lower_bound(const Key& key) { return tree.lower_bound(key); }
  iterator upper_bound(const Key& key) { return tree.upper_bound(key); }

 private:
  BinaryTree<Key, int> tree;
};

}  // namespace s21

#endif  // __S21_MULTISET_H__