#ifndef CPPCONTAINERS_STACK_HPP
#define CPPCONTAINERS_STACK_HPP

#include <cstdio>
#include <initializer_list>

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack : protected s21::List<T> {
 private:
  using stack_type = s21::List<T>;

  /* Stack Member type */
  using value_type = typename stack_type::value_type;
  using reference = typename stack_type::reference;
  using const_reference = typename stack_type::const_reference;
  using size_type = typename stack_type::size_type;

 public:
  /* Stack Member type */
  using stack_type::stack_type;

  /* Stack Member functions */
  stack(std::initializer_list<value_type> const &items) : stack() {
    for (value_type value : items) {
      stack_type::push_front(value);
    }
  }

  /* Stack Element access */
  [[nodiscard]] const_reference top() const noexcept {
    return stack_type::front();
  };

  /* Stack Capacity */
  using stack_type::empty;
  using stack_type::size;

  /* Stack Modifiers */
  void push(const_reference value) { stack_type::push_front(value); };
  void pop() noexcept { stack_type::pop_front(); };
  void swap(stack &s) noexcept {
    stack_type::swap(static_cast<stack_type &>(s));
  }
};

}  // namespace s21

#endif  // CPPCONTAINERS_STACK_HPP
