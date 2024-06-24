#ifndef CPP2_S21_CONTAINERS_1_S21_LIST_H
#define CPP2_S21_CONTAINERS_1_S21_LIST_H
#include <limits>

#include "initializer_list"
#include "stdexcept"

namespace s21 {
template <typename T>
class List {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  /* LIST MEMBER METHODS */

  List() : ListSize(0) {
    ChainNode = new Node(value_type());
    ChainNode->next = ChainNode;
    ChainNode->prev = ChainNode;
  }

  explicit List(size_type n) : List() {
    for (size_type i = 0; i != n; ++i) {
      push_back(value_type());
    }
  }

  List(std::initializer_list<value_type> const &items) : List() {
    for (const_reference item : items) {
      push_back(item);
    }
  }

  List(const List &other) : List() {
    for (const_reference item : other) {
      push_back(item);
    }
  }

  List(List &&other) noexcept : List() {
    ListSize = other.ListSize;
    other.ListSize = 0;
    std::swap(ChainNode, other.ChainNode);
  }

  List<value_type> &operator=(const List<value_type> &other) {
    if (this != &other) {
      clear();
      for (const_reference item : other) {
        push_back(item);
      }
    }
    return *this;
  }

  List<T> &operator=(List<T> &&other) noexcept {
    clear();
    ListSize = other.ListSize;
    other.ListSize = 0;
    std::swap(ChainNode, other.ChainNode);

    return *this;
  }

  ~List() {
    clear();
    delete ChainNode;
    ListSize = 0;
  }

 private:
  /* PRIVATE ATTRIBUTES */
  struct Node {
    value_type value;
    Node *next;
    Node *prev;
    explicit Node(const_reference value)
        : value(value), next(nullptr), prev(nullptr){};
  };
  size_type ListSize;
  Node *ChainNode;

  /**** LIST ITERATOR ****/
  class ListIterator {
   public:
    explicit ListIterator(Node *node, Node *chainNode)
        : CurrentNode(node), ChainNode(chainNode) {}

    ListIterator &operator++() {
      CurrentNode = CurrentNode->next;
      return *this;
    }
    ListIterator &operator--() {
      CurrentNode = CurrentNode->prev;
      return *this;
    }
    reference operator*() const {
      if (CurrentNode == ChainNode) {
        throw std::runtime_error("Node is out of list");
      }
      return CurrentNode->value;
    }
    bool operator==(const ListIterator &other) const {
      if (CurrentNode == other.CurrentNode) {
        return true;
      }
      return false;
    }
    bool operator!=(const ListIterator &other) const {
      return CurrentNode != other.CurrentNode;
      ;
    }

    Node *GetCurrentNode() { return CurrentNode; }

   private:
    /* CurrentNode is a reference to current position of Node in Linked List
     * * ChainNode is a dummy node, reference on virtual Node, that can link
     * begin Node and end Node */
    Node *CurrentNode;
    Node *ChainNode;
  };
  class ListConstIterator {
   public:
    explicit ListConstIterator(Node *node, Node *ChainNode)
        : CurrentNode(node), ChainNode(ChainNode) {}

    ListConstIterator &operator++() {
      CurrentNode = CurrentNode->next;
      return *this;
    }

    ListConstIterator &operator--() {
      CurrentNode = CurrentNode->prev;
      return *this;
    }

    const_reference operator*() const {
      if (CurrentNode == ChainNode) {
        throw std::runtime_error("Node is out of list (ChainNode)");
      }
      return CurrentNode->value;
    }

    bool operator==(const ListConstIterator &other) const {
      return CurrentNode == other.CurrentNode;
    }

    bool operator!=(const ListConstIterator &other) const {
      return CurrentNode != other.CurrentNode;
      ;
    }

    Node *getCurrentNode() { return CurrentNode; }

   private:
    Node *CurrentNode;
    Node *ChainNode;
  };

 public:
  /* PUBLIC ATTRIBUTES (ITERATION) */
  using iterator = ListIterator;
  using const_iterator = const ListConstIterator;

  /*
  Returns a reference to the first element in the container.
  Calling front on an empty container causes undefined behavior.
   */
  reference front() { return ChainNode->next->value; }
  const_reference front() const { return ChainNode->next->value; }

  /*
  Returns a reference to the last element in the container.
  Calling back on an empty container causes undefined behavior.
  */
  reference back() { return ChainNode->prev->value; }
  const_reference back() const { return ChainNode->prev->value; }

  /* Iterator to the first node of list */
  iterator begin() noexcept { return iterator(ChainNode->next, ChainNode); }
  const_iterator begin() const noexcept {
    return const_iterator(ChainNode->next, ChainNode);
  }

  /* Iterator to the last node of list (actually ChainNode)
   * Real last node is ChainNode.prev */
  iterator end() noexcept { return iterator(ChainNode, ChainNode); };
  const_iterator end() const noexcept {
    return const_iterator(ChainNode, ChainNode);
  };

  /* Erase Node on entry position */
  iterator erase(iterator pos) {
    Node *CurrNode = pos.GetCurrentNode();
    Node *NextNode = CurrNode->next;

    if (is_ChainNode(pos)) {
      ListSize--;
      return pos;
    }

    if (is_ChainNode(++pos)) {
      NextNode = NextNode->next;
    }

    CurrNode->prev->next = CurrNode->next;
    CurrNode->next->prev = CurrNode->prev;

    delete CurrNode;
    ListSize--;

    return iterator(NextNode, ChainNode);
  }

  /* Insert node in entry position, return position of the next node */
  iterator insert(iterator pos, const_reference value) {
    Node *NewNode = new Node(value);
    NewNode->next = pos.GetCurrentNode();
    NewNode->prev = pos.GetCurrentNode()->prev;
    pos.GetCurrentNode()->prev->next = NewNode;
    pos.GetCurrentNode()->prev = NewNode;
    ListSize++;
    return iterator(NewNode, ChainNode);
  }

  /* Push node to the back of list */
  void push_back(const_reference value) { insert(end(), value); }

  /* Push node to the front of list */
  void push_front(const_reference value) { insert(begin(), value); }

  /* Remove last node of list */
  void pop_back() {
    iterator pos = --end();
    erase(pos);
  }

  /* Remove first node of list */
  void pop_front() { erase(begin()); }

  /* bool expression that check empty list or not */
  bool empty() const noexcept { return ChainNode == ChainNode->next; }

  /* Return size of list */
  size_type size() const noexcept { return ListSize; }

  /* Returns the maximum number of elements the container is able to hold due to
   * system or library implementation limitations, i.e. std::distance(begin(),
   * end()) for the largest container. */
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }

  /* Clean up list */
  void clear() {
    Node *CurrNode = ChainNode->next;
    while (CurrNode != ChainNode) {
      Node *TempNode = CurrNode;
      CurrNode = CurrNode->next;
      delete TempNode;
    }

    ChainNode->next = ChainNode;
    ChainNode->prev = ChainNode;
    ListSize = 0;
  }

  /* Swap list with other list */
  void swap(List<T> &other) {
    std::swap(ChainNode, other.ChainNode);
    std::swap(ListSize, other.ListSize);
  }

  /* Other list entry in current list*/
  void merge(List<value_type> &other) {
    if (this == &other) {
      return;
    }

    ListSize += other.ListSize;
    iterator it1 = begin();
    iterator it2 = other.begin();

    while (it1 != end() && it2 != other.end()) {
      if (*it1 > *it2) {
        insert(it1, *it2);
        ++it2;
      } else {
        ++it1;
      }
    }

    while (it2 != other.end()) {
      push_back(*it2);
      ++it2;
    }

    other.clear();
  }

  /* Reverse current list */
  void reverse() noexcept {
    if (ListSize < 2) {
      return;
    }
    Node *node = ChainNode->next;
    while (node != ChainNode) {
      std::swap(node->next, node->prev);
      node = node->prev;
    }
    std::swap(ChainNode->prev, ChainNode->next);
  }

  /* Removes all  duplicate from the list */
  void unique() {
    if (ListSize < 2) return;

    iterator it = begin();
    iterator next = it;
    ++next;

    while (next != end()) {
      if (*it == *next) {
        // erase return reference to the next node
        next = erase(next);
      } else {
        ++it;
        ++next;
      }
    }
  }

  /* Sorts the elements and preserves the order of equivalent elements */
  void sort() {
    if (ListSize < 2) return;

    List<value_type> left;
    List<value_type> right;

    size_type middle = ListSize / 2;
    iterator it = begin();
    for (size_type i = 0; i < middle; ++i) {
      left.push_back(*it);
      ++it;
    }
    while (it != end()) {
      right.push_back(*it);
      ++it;
    }

    // Рекурсивная сортировка обеих половин
    left.sort();
    right.sort();

    // Слияние двух отсортированных половин
    clear();  // Очищаем текущий список
    *this = left;
    merge(right);
  }

  /* Transfers elements from one list to another */
  void splice(iterator pos, List<T> &other) {
    if (other.empty()) {
      return;
    }
    iterator otherIt = other.begin();
    while (otherIt != other.end()) {
      pos = insert(pos, *otherIt);
      ++pos;
      ++otherIt;
    }
    other.clear();
  }

 private:
  /* PRIVATE ATTRIBUTES */
  bool is_ChainNode(iterator pos) {
    Node *CurrNode = pos.GetCurrentNode();
    return CurrNode == ChainNode ? true : false;
  }
};

};      // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_S21_LIST_H