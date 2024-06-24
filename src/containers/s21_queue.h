#ifndef CPP2_S21_CONTAINERS_1_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_1_S21_QUEUE_H
#ifndef CPP2_SRC_S21_QUEUE_H_
#define CPP2_SRC_S21_QUEUE_H_

#include <initializer_list>

#include "s21_list.h"
#include "stdexcept"

namespace s21 {

template <typename T, typename Parent = s21::List<T>>
class Queue {
 public:
  /* LIST MEMBER METHODS */
  using value_type = typename Parent::value_type;
  using reference = typename Parent::reference;
  using const_reference = typename Parent::const_reference;
  using size_type = typename Parent::size_type;

  Queue() : container() {}

  Queue(std::initializer_list<value_type> const &items) : container(items) {}

  Queue(const Queue &other) : container(other.container) {}

  // Queue(Queue &&other) noexcept : container(std::move(other.container)) {} --
  // move заменил на swap
  Queue(Queue &&other) noexcept { std::swap(container, other.container); }

  Queue<T, Parent> &operator=(const Queue &other) {
    container = other.container;
    return *this;
  }
  Queue<T, Parent> &operator=(Queue &&other) noexcept {
    std::swap(container, other.container);  // move заменил на swap
    return *this;
  }

  ~Queue() = default;

  /* REFERENCES */

  /*
  Returns a reference to the first element in the container
  */
  reference front() { return container.front(); }

  /*
  Returns a reference to the last element in the container.
  */
  reference back() { return container.back(); }

  /*
  Checks if the container has no elements.
  */
  bool empty() const noexcept { return container.empty(); }

  /*
  Returns the number of elements in the container.
  */
  size_type size() const noexcept { return container.size(); }

  /* Push node to the back of куеуе */
  void push(const_reference value) { container.push_back(value); }

  /* Remove last node of queue */
  void pop() { container.pop_front(); }

  /* Swap list with other list */
  void swap(Queue &other) { container.swap(other.container); }

 private:
  /*  container = s21::List<T>
   *  The private attribute of  s21::Queue is a s21::List object.
   *  That is the reason why the variable called Parent (cause Queue include
   * List methods. */
  Parent container;
};
}  // namespace s21

#endif  // CPP2_SRC_S21_QUEUE_H_
#endif  // CPP2_S21_CONTAINERS_1_S21_QUEUE_H
