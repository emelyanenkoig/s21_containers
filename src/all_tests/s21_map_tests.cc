#include <gtest/gtest.h>

#include <map>

#include "../containers/s21_map.h"

TEST(MapTest, BasicConstructor) {
  s21::map<int, int> test;
  EXPECT_EQ(test.empty(), true);
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, int> test1;
  test1.insert(1, 2);
  test1.insert(2, 3);
  test1.insert(3, 4);
  s21::map<int, int> test2(test1);
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2(std::move(test1));
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
  EXPECT_EQ(test2.at(4), 5);
}

TEST(MapTest, ConstructorsList) {
  s21::map<int, std::string> new_map;

  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (my_iter != my_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(std_iter == std_map.end());

  s21::map<int, std::string> my_map2(my_map);
  std::map<int, std::string> std_map2(std_map);

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());

  s21::map<int, std::string> my_map3 = std::move(my_map2);
  std::map<int, std::string> std_map3 = std::move(std_map2);

  my_iter = my_map3.begin();
  std_iter = std_map3.begin();

  while (std_iter != std_map3.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map3.end());

  s21::map<int, std::string> my_map4 = std::move(my_map2);
  std::map<int, std::string> std_map4 = std::move(std_map2);
}

TEST(MapTest, ConstructorsList2) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.empty(), false);
  EXPECT_EQ(test.at(1), 2);
  EXPECT_EQ(test.at(2), 3);
  EXPECT_EQ(test.at(3), 4);
  EXPECT_EQ(test.at(4), 5);
}

TEST(MapTest, At) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map.at(33);
  auto std_ans = std_map.at(33);
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map.at(3);
  std_ans = std_map.at(3);
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(MapTest, AtOneValue) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_EQ(test.at(1), 2);
}

TEST(MapTest, AtManyValue) {
  s21::map<int, int> test;
  test.insert(1, 2);
  test.insert(2, 3);
  test.insert(3, 4);
  test.insert(-1, 5);
  EXPECT_EQ(test.at(3), 4);
}

TEST(MapTest, SquareBrackets) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_ans = my_map[33];
  auto std_ans = std_map[33];
  ASSERT_TRUE(my_ans == std_ans);

  my_ans = my_map[3];
  std_ans = std_map[3];
  ASSERT_TRUE(my_ans == std_ans);
}

TEST(MapTest, SquareBrackets1) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_EQ(test[1], 2);
}

TEST(MapTest, SquareBrackets2) {
  s21::map<int, int> test;
  test.insert(1, 2);
  test.insert(2, 3);
  test.insert(3, 4);
  test.insert(-1, 5);
  EXPECT_EQ(test[3], 4);
  test[4] = 5;
  test[5] = 6;
  EXPECT_EQ(test[5], 6);
}

TEST(MapTest, Empty) {
  s21::map<int, std::string> new_map;
  ASSERT_TRUE(new_map.empty() == true);

  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_TRUE(my_map.empty() == false);
}

TEST(MapTest, Size) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(MapTest, Clear) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  ASSERT_EQ(my_map.size(), std_map.size());
}

TEST(MapTest, Insert1) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert(1, "one");
  std_map.insert({1, "one"});
  my_map.insert(2, "two");
  std_map.insert({2, "two"});
  my_map.insert(22, "twotwo");
  std_map.insert({22, "twotwo"});
  my_map.insert(-22, "-twotwo");
  std_map.insert({-22, "-twotwo"});
  my_map.insert(22, "three");
  std_map.insert({22, "three"});
  my_map.insert(22234, "two3two");
  std_map.insert({22234, "two3two"});
  my_map.insert(12, "onetwo");
  std_map.insert({12, "onetwo"});
  my_map.insert(-12, "-onetwo");
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(MapTest, Insert2) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert({1, "one"});
  std_map.insert({1, "one"});
  my_map.insert({2, "two"});
  std_map.insert({2, "two"});
  my_map.insert({22, "twotwo"});
  std_map.insert({22, "twotwo"});
  my_map.insert({-22, "-twotwo"});
  std_map.insert({-22, "-twotwo"});
  my_map.insert({22, "three"});
  std_map.insert({22, "three"});
  my_map.insert({22234, "two3two"});
  std_map.insert({22234, "two3two"});
  my_map.insert({12, "onetwo"});
  std_map.insert({12, "onetwo"});
  my_map.insert({-12, "-onetwo"});
  std_map.insert({-12, "-onetwo"});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(MapTest, Erase) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.erase(test.begin());
  EXPECT_EQ(test.contains(1), false);
}

TEST(MapTest, Erase1) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Erase2) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Erase3) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ++my_iter;
  ++std_iter;
  ++my_iter;
  ++std_iter;

  my_map.erase(my_iter);
  std_map.erase(std_iter);

  my_iter = my_map.begin();
  std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Swap) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  s21::map<int, std::string> my_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(-42, "fodasfo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.swap(my_map2);
  std_map.swap(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());

  my_iter = my_map2.begin();
  std_iter = std_map2.begin();

  while (std_iter != std_map2.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map2.end());
}

TEST(MapTest, Merge) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  s21::map<int, std::string> my_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};
  std::map<int, std::string> std_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  my_map.merge(my_map2);
  std_map.merge(std_map2);

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}

TEST(MapTest, Merge1) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2({{5, 6}, {6, 7}});
  test1.merge(test2);
  EXPECT_EQ(test1.size(), 6U);
  EXPECT_EQ(test1[1], 2);
  EXPECT_EQ(test1[5], 6);
  EXPECT_EQ(test1[6], 7);
}

TEST(MapTest, InsertAsign) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> std_map;

  my_map.insert_or_assign(1, "one");
  std_map.insert_or_assign(1, "one");
  my_map.insert_or_assign(2, "two");
  std_map.insert_or_assign(2, "two");
  my_map.insert_or_assign(22, "twotwo");
  std_map.insert_or_assign(22, "twotwo");
  my_map.insert_or_assign(-22, "-twotwo");
  std_map.insert_or_assign(-22, "-twotwo");
  my_map.insert_or_assign(22, "three");
  std_map.insert_or_assign(22, "three");
  my_map.insert_or_assign(22234, "two3two");
  std_map.insert_or_assign(22234, "two3two");
  my_map.insert_or_assign(12, "onetwo");
  std_map.insert_or_assign(12, "onetwo");
  my_map.insert_or_assign(-12, "-onetwo");
  std_map.insert_or_assign(-12, "-onetwo");

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  while (std_iter != std_map.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    ASSERT_EQ((*my_iter).second, (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
}

TEST(MapTest, Contains) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  ASSERT_EQ(my_map.contains(42), true);
  ASSERT_EQ(my_map.contains(42342), false);
  ASSERT_EQ(my_map.contains(33), true);
  ASSERT_EQ(my_map.contains(0), false);
}

TEST(MapTest, Emplace) {
  s21::map<int, std::string> my_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};
  std::map<int, std::string> std_map{
      std::make_pair(42, "foo"), std::make_pair(3, "bar"),
      std::make_pair(33, "aboba"), std::make_pair(3, "ba")};

  std::map<int, std::string> std_map2{
      std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
      std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba")};

  std_map.merge(std_map2);
  my_map.emplace(std::make_pair(42, "foo"), std::make_pair(323, "basdar"),
                 std::make_pair(343, "abobaaWD"), std::make_pair(-3, "ba"));

  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();

  while (std_iter != std_map.end()) {
    ASSERT_TRUE((*my_iter).first == (*std_iter).first);
    ASSERT_TRUE((*my_iter).second == (*std_iter).second);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_map.end());
}
