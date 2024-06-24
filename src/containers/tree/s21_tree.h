#ifndef __S21_TREE_H__
#define __S21_TREE_H__

#include <iostream>  //std::endl
#include <limits>    //max_size
#include <memory>    //std::unique_ptr

using namespace std;
namespace s21 {

template <typename Key, typename T>
class BinaryTree {
 private:
  struct Node {
    Node(Key k, T v)
        : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr) {}

    Key key;
    T value;
    Node* parent = nullptr;
    std::unique_ptr<Node> left = nullptr;  // ? nullptr не обязательно, по
                                           // умолчание инициализирунтся нулом
    std::unique_ptr<Node> right = nullptr;
  };
  size_t t_size;

 public:
  class Iterator;
  class ConstIterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  class Iterator {
   public:
    Iterator(Node* node = nullptr) : current(node) {}

    bool operator==(const Iterator& other) const {
      return current == other.current;
    };
    bool operator!=(const Iterator& other) const {
      return current != other.current;
    };
    Iterator& operator++() {
      if (current->right) {
        current = current->right.get();
        while (current->left) {
          current = current->left.get();
        }
      } else {
        Node* parent = current->parent;
        while (parent && current == parent->right.get()) {
          current = parent;
          parent = parent->parent;
        }
        current = parent;
      }
      return *this;
    }

    Key& operator*() const { return std::ref(current->key); }

    Node* current;
  };

  class ConstIterator {
   public:
    ConstIterator(Node* node = nullptr) : current(node) {}

    bool operator==(const ConstIterator& other) const {
      return current == other.current;
    };
    bool operator!=(const ConstIterator& other) const {
      return current != other.current;
    };
    ConstIterator& operator++() {
      if (current->right) {
        current = current->right.get();
        while (current->left) {
          current = current->left.get();
        }
      } else {
        Node* parent = current->parent;
        while (parent && current == parent->right.get()) {
          current = parent;
          parent = parent->parent;
        }
        current = parent;
      }
      return *this;
    }

    std::pair<const Key&, const T&> operator*() const {
      return std::make_pair(std::ref(current->key), std::ref(current->value));
    }

    Node* current;
  };

  std::unique_ptr<Node> root;

  BinaryTree() : t_size(0), root(nullptr){};

  ~BinaryTree() { clear(); };
  BinaryTree(BinaryTree& other) : BinaryTree() {
    for (const auto& p : other) {
      insert(p);
    }
  };
  BinaryTree(BinaryTree&& other) : BinaryTree() { swap(other); };

  BinaryTree& operator=(BinaryTree other) {
    swap(other);
    return *this;
  }

  Iterator begin() {
    if (!root) {
      return end();
    }
    Node* node = root.get();
    while (node->left) {
      node = node->left.get();
    }
    return Iterator(node);
  }
  Iterator end() { return Iterator(nullptr); }

  ConstIterator begin() const {
    if (!root) {
      return end();
    }
    Node* node = root.get();
    while (node->left) {
      node = node->left.get();
    }
    return ConstIterator(node);
  }
  ConstIterator end() const { return ConstIterator(nullptr); }

  std::pair<Iterator, bool> multiInsert(const Key key, T val) {
    return insert(key, val, true);
  }

  std::pair<Iterator, bool> insert(const std::pair<Key, T>& pair) {
    return insert(pair.first, pair.second);
  }

  std::pair<Iterator, bool> insert(Key k, T v, bool multi = false) {
    if (!root) {
      root = std::make_unique<Node>(k, v);
      ++t_size;
      return std::make_pair(Iterator(root.get()), true);
    }
    Node* current = root.get();
    while (true) {
      if (k < current->key) {
        if (!current->left) {
          current->left = std::make_unique<Node>(k, v);
          current->left->parent = current;
          t_size++;
          return std::make_pair(Iterator(current->left.get()), true);
        }
        current = current->left.get();
      } else if (current->key < k || (current->key == k && multi)) {
        if (!current->right) {
          current->right = std::make_unique<Node>(k, v);
          current->right->parent = current;
          ++t_size;
          return std::make_pair(Iterator(current->right.get()), true);
        }
        current = current->right.get();
      } else {
        return std::make_pair(Iterator(current), false);
      }
    }
  }

  Iterator find(const Key& k) {
    Node* current = root.get();
    while (current) {
      if (k < current->key) {
        current = current->left.get();
      } else if (current->key < k) {
        current = current->right.get();
      } else {
        return Iterator(current);
      }
    }
    return end();
  }
  ConstIterator find(const Key& k) const {
    Node* current = root.get();
    while (current) {
      if (k < current->key) {
        current = current->left.get();
      } else if (current->key < k) {
        current = current->right.get();
      } else {
        return ConstIterator(current);
      }
    }
    return end();
  }

  size_t count(const Key& key) {
    size_t result = 0;
    if (find(key) != nullptr) {
      for (auto it = begin(); it != end(); ++it) {
        if ((*it) == key) {
          result++;
        }
      }
    }
    return result;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    auto low = lower_bound(key);
    auto up = low;
    if (up != end()) {
      up = upper_bound(key);
    }
    return std::make_pair(low, up);
  }

  Iterator lower_bound(const Key& key) {
    if (find(key) == nullptr) {
      return end();
    }
    return find(key);
  }

  Iterator upper_bound(const Key& key) {
    auto it = begin();
    for (; it != end(); ++it) {
      if ((*it) > key) {
        break;
      }
    }
    return it;
  }

  size_t size() const { return t_size; };
  size_t max_size() const { return std::numeric_limits<size_t>::max(); }
  void clear() {
    root = nullptr;
    t_size = 0;
  };
  void swap(BinaryTree& other) {
    std::swap(root, other.root);
    std::swap(t_size, other.t_size);
  };
  bool empty() const { return root == nullptr; }
  void erase(const Key& k) {
    auto it = find(k);
    if (it != end()) {
      erase(it);
    }
  }

  void erase(iterator it) {
    Node* current = it.current;
    if (current->left && current->right) {
      auto successor = ++it;
      std::swap(current->key, successor.current->key);
      current = successor.current;
    }
    Node* child = nullptr;
    if (current->left) {
      current->left->parent = current->parent;
      child = current->left.release();
    } else if (current->right) {
      current->right->parent = current->parent;
      child = current->right.release();
    }
    if (current->parent) {
      if (current->parent->left.get() == current) {
        current->parent->left.reset(child);
      } else {
        current->parent->right.reset(child);
      }
    } else {
      root.reset(child);
    }
    --t_size;
  }
};
}  // namespace s21

#endif  // __S21_TREE_H__