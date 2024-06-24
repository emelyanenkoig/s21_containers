#ifndef CPPCONTAINERS_MAP_H
#define CPPCONTAINERS_MAP_H

#include <cstdio>
#include <initializer_list>
#include <utility>

#include "s21_vector.h"
#include "tree/tree.h"

namespace s21 {

template <typename Key, typename T>
class map : public tree<std::pair<Key, T>> {
  /* Map Member type */
 private:
  using tree<std::pair<Key, T>>::tree;
  using key_type = Key;
  using map_type = T;
  using value_type = std::pair<key_type, map_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename tree<value_type>::Iterator;
  using const_iterator = typename tree<value_type>::IteratorConst;
  using size_type = std::size_t;

 public:
  /* Member functions */

  map(std::initializer_list<value_type> const& items) : map() {
    for (value_type value : items) {
      insert(value.first, value.second);
    }
  }

  /* Map Element access */

  [[nodiscard]] map_type& at(const key_type& key) {
    auto found = find_contains_map(key);
    if (!found) throw std::out_of_range("There is no such key!");
    return found->value_.second;
  }

  map_type& operator[](const key_type& key) {
    try {
      return at(key);
    } catch (...) {
      value_type val = value_type(key, map_type());
      tree<value_type>::default_insert(val);
      return at(key);
    }
  }

  /* Map Iterators */

  /* Map Capacity */

  /* Map Modifiers */

  std::pair<iterator, bool> insert(const key_type& key, const map_type& obj) {
    if (contains(key))
      return std::make_pair(iterator(this->find_contains_map(key)), false);
    iterator iter = tree<value_type>::default_insert(std::make_pair(key, obj));
    return std::make_pair(iter, true);
  }

  std::pair<iterator, bool> insert(const value_type& value) override {
    return insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const map_type& obj) {
    typename tree<value_type>::Node* a = find_contains_map(key);
    if (a) {
      a->value_ = std::make_pair(key, obj);
      return std::make_pair(iterator(a), true);
    }
    iterator iter = tree<value_type>::default_insert(std::make_pair(key, obj));
    return std::make_pair(iter, true);
  }
  void merge(map& other) { merge_map(other, other.return_root()); }

  /* Map Modifiers */

  [[nodiscard]] bool contains(const key_type& key) noexcept {
    return find_contains_map(key);
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    std::vector<std::pair<iterator, bool>> res = {(insert(args))...};
    return res;
  }

 private:
  typename tree<value_type>::Node* find_contains_map(
      const key_type& key) noexcept {
    if (this->empty()) return nullptr;
    auto* current = tree<value_type>::return_root();
    while (true) {
      if (current == nullptr) {
        return nullptr;
      } else if (current->value_.first == key) {
        return current;
      } else if (current->value_.first > key) {
        current = current->left_node_;
      } else {
        current = current->right_node_;
      }
    }
  }

  void merge_map(map& other, typename tree<value_type>::Node* Node) {
    if (Node->right_node_) merge_map(other, Node->right_node_);
    if (Node->left_node_) merge_map(other, Node->left_node_);
    auto result = insert(Node->value_);
    if (result.second) {
      auto iter = iterator(Node);
      other.erase(iter);
    }
  }
};

}  // namespace s21

#endif  // CPPCONTAINERS_MAP_H
