#ifndef CPPCONTAINERS_TREE_H
#define CPPCONTAINERS_TREE_H

#include <iostream>
#include <limits>

#include "../s21_vector.h"

namespace s21 {

template <typename T>
class tree {
 public:
  class Iterator;
  class IteratorConst;

  using key_type = T;
  using value_type = T;
  using cosnt_value_type = const T;
  using iterator = Iterator;
  using const_iterator = IteratorConst;
  using size_type = size_t;

 public:
  struct Node {
    Node *parent_;
    Node *left_node_;
    Node *right_node_;
    value_type value_;
    bool is_empty = false;

    explicit Node()
        : parent_(nullptr),
          left_node_(nullptr),
          right_node_(nullptr),
          value_(value_type{}) {}
    explicit Node(const value_type &value)
        : parent_(nullptr),
          left_node_(nullptr),
          right_node_(nullptr),
          value_(value) {}
  };

  class Iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;

   public:
    Node *curr_node;

    Iterator() = delete;

    explicit Iterator(Node *node) : curr_node(node) {}

    value_type &operator*() noexcept { return curr_node->value_; }

    bool operator==(const Iterator &other) const noexcept {
      return curr_node == other.curr_node;
    }

    bool operator!=(const Iterator &other) const noexcept {
      return curr_node != other.curr_node;
    }

    Iterator &operator++() noexcept {
      IteratorPlus();
      return *this;
    }

    Iterator operator++(int) noexcept {
      iterator *n = this;
      IteratorPlus();
      return *n;
    }

    Iterator &operator--() noexcept {
      IteratorMinus();
      return *this;
    }

    Iterator operator--(int) noexcept {
      iterator *n = this;
      IteratorMinus();
      return *n;
    }

   private:
    void IteratorPlus() {
      if (curr_node->right_node_) {
        curr_node = curr_node->right_node_;
        while (curr_node->left_node_) {
          curr_node = curr_node->left_node_;
        }
      } else {
        Node *buff = curr_node;
        curr_node = curr_node->parent_;
        while (buff == curr_node->right_node_ && !curr_node->is_empty) {
          buff = curr_node;
          curr_node = curr_node->parent_;
        }
      }
    }
    void IteratorMinus() {
      if (curr_node->left_node_) {
        curr_node = curr_node->left_node_;
        while (curr_node->right_node_) {
          curr_node = curr_node->right_node_;
        }
      } else {
        Node *buff = curr_node;
        curr_node = curr_node->parent_;
        while (buff == curr_node->left_node_) {
          buff = curr_node;
          curr_node = curr_node->parent_;
        }
      }
    }
  };

  class IteratorConst {
   public:
    using iterator_category = std::bidirectional_iterator_tag;

   public:
    Node *curr_node;

    IteratorConst() = delete;
    IteratorConst(Iterator &it) : curr_node(it.curr_node) {}
    IteratorConst(Iterator &&it) : curr_node(it.curr_node) {}
    explicit IteratorConst(Node *node) : curr_node(node) {}
    cosnt_value_type &operator*() noexcept { return curr_node->value_; }

    bool operator==(const Iterator &other) const noexcept {
      return curr_node == other.curr_node;
    }

    bool operator!=(const Iterator &other) const noexcept {
      return curr_node != other.curr_node;
    }

    IteratorConst &operator++() noexcept {
      IteratorPlus();
      return *this;
    }

    IteratorConst operator++(int) noexcept {
      iterator *n = this;
      IteratorPlus();
      return *n;
    }

    IteratorConst &operator--() noexcept {
      IteratorMinus();
      return *this;
    }

    IteratorConst operator--(int) noexcept {
      iterator *n = this;
      IteratorMinus();
      return *n;
    };

   private:
    void IteratorPlus() {
      if (curr_node->right_node_) {
        curr_node = curr_node->right_node_;
        while (curr_node->left_node_) {
          curr_node = curr_node->left_node_;
        }
      } else {
        Node *buff = curr_node;
        curr_node = curr_node->parent_;
        while (buff == curr_node->right_node_ && !curr_node->is_empty) {
          buff = curr_node;
          curr_node = curr_node->parent_;
        }
      }
    }
    void IteratorMinus() {
      if (curr_node->left_node_) {
        curr_node = curr_node->left_node_;
        while (curr_node->right_node_) {
          curr_node = curr_node->right_node_;
        }
      } else {
        Node *buff = curr_node;
        curr_node = curr_node->parent_;
        while (buff == curr_node->left_node_) {
          buff = curr_node;
          curr_node = curr_node->parent_;
        }
      }
    }
  };

 private:
  Node *root_node;
  Node *node;
  size_type tree_size;

 public:
  tree() : node(new Node()), tree_size(0) { root_is_empty(); }

  tree(const tree &other) : tree() { copy_tree(other.root_node); }

  tree(tree &&other) noexcept
      : root_node(other.root_node),
        node(other.node),
        tree_size(other.tree_size) {
    other.root_node = nullptr;
    other.node = nullptr;
    other.tree_size = 0;
  }

  ~tree() {
    if (root_node != node) destroy_node(root_node);
    delete node;
  }

  tree &operator=(tree &&other) noexcept {
    root_node = other.root_node;
    node = other.node;
    tree_size = other.tree_size;

    other.root_node = nullptr;
    other.node = nullptr;
    other.tree_size = 0;

    return *this;
  }

  [[nodiscard]] iterator begin() noexcept {
    return Iterator(node->right_node_);
  }
  [[nodiscard]] iterator end() noexcept { return Iterator(node); }

  [[nodiscard]] const_iterator begin() const noexcept {
    return IteratorConst(node->right_node_);
  }
  [[nodiscard]] const_iterator end() const noexcept {
    return IteratorConst(node);
  }

  [[nodiscard]] bool empty() const noexcept { return root_node == node; }
  [[nodiscard]] size_type size() const noexcept { return tree_size; }
  [[nodiscard]] size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  };

  void clear() {
    if (!empty()) {
      destroy_node(root_node);
      root_is_empty();
    }
  }

  virtual std::pair<iterator, bool> insert(const value_type &value) {
    return auto_insert(value, true);
  }

  void erase(iterator pos) noexcept {
    Node *curr_pos = pos.curr_node;
    if (curr_pos == node->left_node_) {
      iterator buff = pos;
      --buff;
      node->left_node_ = buff.curr_node;
    } else if (curr_pos == node->right_node_) {
      iterator buff = pos;
      ++buff;
      node->right_node_ = buff.curr_node;
    }
    if (!curr_pos->left_node_ && !curr_pos->right_node_) {
      if (curr_pos->parent_ == node) {
        root_is_empty();
      } else if (curr_pos == curr_pos->parent_->left_node_) {
        curr_pos->parent_->left_node_ = nullptr;
      } else {
        curr_pos->parent_->right_node_ = nullptr;
      }
    } else if (!curr_pos->right_node_) {
      if (curr_pos->parent_ == node) {
        node->parent_ = curr_pos->left_node_;
        curr_pos->left_node_->parent_ = node;
        root_node = curr_pos->left_node_;
      } else if (curr_pos == curr_pos->parent_->left_node_) {
        curr_pos->parent_->left_node_ = curr_pos->left_node_;
        curr_pos->left_node_->parent_ = curr_pos->parent_;
      } else {
        curr_pos->parent_->right_node_ = curr_pos->left_node_;
        curr_pos->left_node_->parent_ = curr_pos->parent_;
      }
    } else if (!curr_pos->left_node_) {
      if (curr_pos->parent_ == node) {
        node->parent_ = curr_pos->right_node_;
        curr_pos->right_node_->parent_ = node;
        root_node = curr_pos->right_node_;
      } else if (curr_pos == curr_pos->parent_->left_node_) {
        curr_pos->parent_->left_node_ = curr_pos->right_node_;
        curr_pos->right_node_->parent_ = curr_pos->parent_;

      } else {
        curr_pos->parent_->right_node_ = curr_pos->right_node_;
        curr_pos->right_node_->parent_ = curr_pos->parent_;
      }
    } else {
      iterator buff = pos;
      ++pos;
      std::swap(buff.curr_node->value_, pos.curr_node->value_);
      if (buff.curr_node->right_node_ == pos.curr_node) {
        buff.curr_node->right_node_ = pos.curr_node->right_node_;
      } else {
        pos.curr_node->parent_->left_node_ = pos.curr_node->right_node_;
      }
    }
    --tree_size;
    delete pos.curr_node;
  }

  void swap(tree &other) noexcept {
    std::swap(root_node, other.root_node);
    std::swap(node, other.node);
    std::swap(tree_size, other.tree_size);
  }

  void merge(tree &other) { default_merge(other, other.root_node); }

  iterator find(const key_type &key) noexcept {
    Node *node = find_contains(key);
    if (node->value_ != key) return iterator(nullptr);
    return iterator(node);
  }

  [[nodiscard]] bool contains(const key_type &key) noexcept {
    Node *node = find_contains(key);
    return !(!node || node->value_ != key);
  }

 protected:
  std::pair<iterator, bool> auto_insert(const value_type &value, bool multi) {
    if (!multi && contains(value)) {
      iterator find_node = find(value);
      return std::make_pair(find_node, false);
    }
    iterator iter = default_insert(value);
    return std::make_pair(iter, true);
  }

  void default_merge(tree &other, Node *item) {
    if (item->right_node_) default_merge(other, item->right_node_);
    if (item->left_node_) default_merge(other, item->left_node_);
    insert(item->value_);
    auto iter = iterator(item);
    other.erase(iter);
  }

  iterator default_insert(const value_type &value) {
    auto *new_node = new Node(value);
    if (root_node == node) {
      root_node = new_node;
      node->parent_ = new_node;
      node->left_node_ = new_node;
      node->right_node_ = new_node;
      new_node->parent_ = node;
    } else {
      Node *buff = root_node;
      while (true) {
        if (buff->value_ > new_node->value_) {
          if (buff->left_node_) {
            buff = buff->left_node_;
          } else {
            buff->left_node_ = new_node;
            new_node->parent_ = buff;
            if (node->right_node_->value_ > new_node->value_) {
              node->right_node_ = new_node;
            }
            break;
          }
        } else {
          if (buff->right_node_) {
            buff = buff->right_node_;
          } else {
            buff->right_node_ = new_node;
            new_node->parent_ = buff;
            if (node->left_node_->value_ < new_node->value_) {
              node->left_node_ = new_node;
            }
            break;
          }
        }
      }
    }
    ++tree_size;
    return Iterator(new_node);
  }

  Node *find_contains(const key_type &key) {
    if (empty()) return nullptr;
    Node *current = root_node;
    while (true) {
      if (current == nullptr) {
        return nullptr;
      } else if (current->value_ == key) {
        return current;
      } else if (current->value_ > key) {
        if (!current->left_node_) return current;
        current = current->left_node_;
      } else {
        if (!current->right_node_) return current;
        current = current->right_node_;
      }
    }
  }

  void destroy_node(Node *root) {
    if (root->left_node_) destroy_node(root->left_node_);
    if (root->right_node_) destroy_node(root->right_node_);
    delete root;
  }

  void root_is_empty() {
    node->is_empty = true;
    node->parent_ = node;
    node->left_node_ = node;
    node->right_node_ = node;
    root_node = node;
    tree_size = 0;
  }

  void copy_tree(const Node *other) {
    default_insert(other->value_);
    if (other->left_node_) copy_tree(other->left_node_);
    if (other->right_node_) copy_tree(other->right_node_);
  }

  Node *return_root() noexcept { return root_node; }
};

}  // namespace s21

#endif  // CPPCONTAINERS_TREE_H
