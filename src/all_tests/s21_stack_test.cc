#include "../containers/s21_stack.h"

#include <stack>

#include "gtest/gtest.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_EQ(my_stack.empty(), std_stack.empty());
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackTest, PushAndTop) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  my_stack.push(1);
  std_stack.push(1);
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.push(2);
  std_stack.push(2);
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.push(3);
  std_stack.push(3);
  ASSERT_EQ(my_stack.top(), std_stack.top());
}

TEST(StackTest, Pop) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  my_stack.push(1);
  std_stack.push(1);
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.push(2);
  std_stack.push(2);
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.push(3);
  std_stack.push(3);
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.pop();
  std_stack.pop();
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.pop();
  std_stack.pop();
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.pop();
  std_stack.pop();
  ASSERT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(StackTest, Size) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_EQ(my_stack.size(), std_stack.size());

  my_stack.push(1);
  std_stack.push(1);
  ASSERT_EQ(my_stack.size(), std_stack.size());

  my_stack.push(2);
  std_stack.push(2);
  ASSERT_EQ(my_stack.size(), std_stack.size());

  my_stack.pop();
  std_stack.pop();
  ASSERT_EQ(my_stack.size(), std_stack.size());

  my_stack.push(3);
  std_stack.push(3);
  ASSERT_EQ(my_stack.size(), std_stack.size());

  my_stack.pop();
  std_stack.pop();
  ASSERT_EQ(my_stack.size(), std_stack.size());

  my_stack.pop();
  std_stack.pop();
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackTest, Swap) {
  s21::stack<int> my_stack1;
  s21::stack<int> my_stack2;
  std::stack<int> std_stack1;
  std::stack<int> std_stack2;

  my_stack1.push(1);
  my_stack1.push(2);
  my_stack1.push(3);
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);

  my_stack1.swap(my_stack2);
  std_stack1.swap(std_stack2);

  ASSERT_EQ(my_stack1.empty(), std_stack1.empty());
  ASSERT_EQ(my_stack1.size(), std_stack1.size());

  ASSERT_EQ(my_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(my_stack2.size(), std_stack2.size());

  ASSERT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> my_stack1;
  std::stack<int> std_stack1;

  my_stack1.push(1);
  my_stack1.push(2);
  my_stack1.push(3);
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);

  s21::stack<int> my_stack2(my_stack1);
  std::stack<int> std_stack2(std_stack1);

  ASSERT_EQ(my_stack1.empty(), std_stack1.empty());
  ASSERT_EQ(my_stack1.size(), std_stack1.size());
  ASSERT_EQ(my_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(my_stack2.size(), std_stack2.size());
  ASSERT_EQ(my_stack1.top(), std_stack1.top());
  ASSERT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(StackTest, CopyConstructor2) {
  s21::stack<int> stack1;
  stack1.push(1);
  s21::stack<int> stack2(stack1);
  stack2.pop();

  EXPECT_EQ(stack1.size(), 1U);
  EXPECT_EQ(stack1.top(), 1);
  EXPECT_EQ(stack2.size(), 0U);
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> my_stack1;
  std::stack<int> std_stack1;

  my_stack1.push(1);
  my_stack1.push(2);
  my_stack1.push(3);
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);

  s21::stack<int> my_stack2(std::move(my_stack1));
  std::stack<int> std_stack2(std::move(std_stack1));

  ASSERT_EQ(my_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(my_stack2.size(), std_stack2.size());
  ASSERT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> my_stack1;
  std::stack<int> std_stack1;

  my_stack1.push(1);
  my_stack1.push(2);
  my_stack1.push(3);
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);

  s21::stack<int> my_stack2;
  std::stack<int> std_stack2;

  my_stack2 = std::move(my_stack1);
  std_stack2 = std::move(std_stack1);

  ASSERT_EQ(my_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(my_stack2.size(), std_stack2.size());
  ASSERT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(StackTest, OperatorOverloadMove) {
  s21::stack<int> stack1;
  stack1.push(1);
  s21::stack<int> stack2 = std::move(stack1);

  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.top(), 1);
  EXPECT_EQ(stack1.empty(), true);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> my_stack({1, 2, 3});
  std::stack<int> std_stack({1, 2, 3});

  ASSERT_EQ(my_stack.empty(), std_stack.empty());
  ASSERT_EQ(my_stack.size(), std_stack.size());
  ASSERT_EQ(my_stack.top(), std_stack.top());
}

TEST(StackTest, InitializerListConstructor2) {
  s21::stack<int> stack({1, 2, 3});
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stack.size(), 3U);
  EXPECT_EQ(stack.top(), 3);
  stack.pop();
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
  stack.pop();
  EXPECT_EQ(stack.empty(), true);
}
