#include <gtest/gtest.h>

#include <stdexcept>

#include "../s21_containers.h"

TEST(Group_exmple, example1) { ASSERT_TRUE(1 == 1); }

TEST(S21setTest, DefaultConstructor) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  ASSERT_EQ(0U, set.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, InitializerListConstructor) {
  s21::set<int> s1({1, 2, 3});
  ASSERT_FALSE(s1.empty());
  ASSERT_EQ(3U, s1.size());
}

TEST(S21setTest, CopyConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(S21setTest, MoveConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> move(std::move(set));
  ASSERT_TRUE(set.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, AssignmentOperator1) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = set1;
  ASSERT_FALSE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(set1.size(), set2.size());
}

TEST(S21setTest, AssignmentOperator2) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = std::move(set1);
  ASSERT_TRUE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(3U, set2.size());
}

TEST(S21setTest, IteratorBegin) {
  s21::set<int> set({1, 2, 3});
  s21::set<int>::iterator iterat;
  iterat = set.begin();
  s21::set<int>::iterator itFind;
  itFind = set.find(1);
  ASSERT_TRUE(iterat == itFind);
  ASSERT_EQ(itFind, iterat);
}

TEST(S21setTest, CapacityEmpty) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(S21setTest, CapacitySize) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  EXPECT_EQ(set.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

TEST(S21setTest, CapacityMaxSize) {
  s21::set<int> set({1, 2, 3});
  EXPECT_EQ(set.max_size(), std::numeric_limits<size_t>::max());
}

TEST(S21setTest, ModifierClear) {
  s21::set<int> set({1, 2, 3});
  ASSERT_FALSE(set.empty());
  set.clear();
  ASSERT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, ModifierInsert1) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(S21setTest, ModifierInsert2) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(S21setTest, ModifierErase) {
  s21::set<int> set = {1, 2, 3};
  EXPECT_EQ(set.size(), 3U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.contains(2));
}

TEST(S21setTest, ModifierSwap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};
  set1.swap(set2);
  EXPECT_EQ(set1.size(), 3U);
  EXPECT_EQ(set2.size(), 3U);
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
  ASSERT_TRUE(set1.contains(6));
  ASSERT_TRUE(set2.contains(1));
  ASSERT_TRUE(set2.contains(2));
  ASSERT_TRUE(set2.contains(3));
}

TEST(S21setTest, ModifierMerge) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 5U);
  EXPECT_EQ(set2.size(), 3U);
  ASSERT_TRUE(set1.contains(1));
  ASSERT_TRUE(set1.contains(2));
  ASSERT_TRUE(set1.contains(3));
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
}
