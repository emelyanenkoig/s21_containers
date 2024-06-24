
#include "../containers/s21_vector.h"

#include <gtest/gtest.h>

#include "vector"

#define s21_EPS 1e-7

using MyTypes = testing::Types<int, double, std::vector<int>, std::string>;

template <typename T>
class VectorTest : public testing::Test {
 protected:
  s21::Vector<T> vec;
  std::vector<T> std_vec;
};

TEST(TestVector, DefaultConstructor) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(TestVector, ParamZeroConstructor) {
  size_t size = 0U;
  s21::Vector<int> vec(size);
  std::vector<int> std_vec(size);

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(TestVector, ParamSmallConstructor) {
  size_t size = 2U;
  s21::Vector<int> vec(size);
  std::vector<int> std_vec(size);

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(TestVector, ParamBigConstructor) {
  size_t size = 100U;
  s21::Vector<int> vec(size);
  std::vector<int> std_vec(size);

  EXPECT_EQ(vec.size(), std_vec.size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(ListVector, IntVector) {
  s21::Vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_EQ(vec.size(), std_vec.size());
  // EXPECT_EQ(vec.max_size(), std_vec.max_size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(ListVector, DoubleVector) {
  s21::Vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_EQ(vec.size(), std_vec.size());
  // EXPECT_EQ(vec.max_size(), std_vec.max_size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(ListVector, StringVector) {
  s21::Vector<std::string> vec{"1", "2", "3", "4", "5"};
  std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  EXPECT_EQ(vec.size(), std_vec.size());
  // EXPECT_EQ(vec.max_size(), std_vec.max_size());
  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(TestVector, CopyConstructor) {
  s21::Vector<unsigned> origin({1, 2, 3, 4});
  s21::Vector vec(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, ordata);
  EXPECT_EQ(vec.size(), origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], ordata[i]);
  }
}

TEST(TestVector, MoveConstructor) {
  s21::Vector<unsigned> origin({1, 2, 3, 4});
  s21::Vector vec(std::move(origin));

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4U, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(TestVector, CopyAssignment) {
  s21::Vector<unsigned> origin({1, 2, 3, 4});
  s21::Vector<unsigned> vec(15);

  vec = origin;

  EXPECT_EQ(4U, vec.size());
  EXPECT_EQ(4U, origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(origin[i], vec[i]);
  }
}

TEST(TestVector, MoveAssignment) {
  s21::Vector<unsigned> origin({1, 2, 3, 4});
  s21::Vector<unsigned> vec(15);

  vec = std::move(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4U, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(TestVector, MoveAssign) {
  s21::Vector<int> original(5);
  s21::Vector<int> moved(6);
  original = std::move(moved);

  std::vector<int> std_vec(5);
  std::vector<int> std_moved(6);
  std_vec = std::move(std_moved);

  EXPECT_EQ(moved.size(), 0U);
  EXPECT_EQ(moved.capacity(), 0U);
  EXPECT_EQ(original.size(), 6U);
  EXPECT_EQ(original.capacity(), 6U);

  EXPECT_EQ(std_moved.size(), 0U);
  EXPECT_EQ(std_moved.capacity(), 0U);
  EXPECT_EQ(std_vec.size(), 6U);
  EXPECT_EQ(std_vec.capacity(), 6U);
}

// TEST(VectorTest, MoveSelfAssign) {
//   // по сути это уб
//   s21::Vector<int> original(5);
//   original = std::move(original);

//   std::vector<int> std_vec(5);
//   std_vec = std::move(std_vec);

//   EXPECT_EQ(original.size(), 0U);
//   EXPECT_EQ(original.capacity(), 0U);

//   EXPECT_EQ(std_vec.size(), 0U);
//   EXPECT_EQ(std_vec.capacity(), 0U);
// }

// AT, [], front, back, empty
TEST(Vector, IntVector) {
  s21::Vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  vec.at(1) = 10;
  std_vec.at(1) = 10;

  EXPECT_EQ(vec.at(1), 10);
  EXPECT_EQ(std_vec.at(1), 10);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  vec[2] = 20;
  std_vec[2] = 20;

  EXPECT_EQ(vec[2], 20);
  EXPECT_EQ(std_vec[2], 20);

  vec.front() = 30;
  std_vec.front() = 30;

  EXPECT_EQ(vec.front(), 30);
  EXPECT_EQ(std_vec.front(), 30);

  vec.back() = 40;
  std_vec.back() = 40;

  EXPECT_EQ(vec.back(), 40);
  EXPECT_EQ(std_vec.back(), 40);
}

TEST(Vector, DoubleVector) {
  s21::Vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  vec.at(1) = 10.0;
  std_vec.at(1) = 10.0;

  EXPECT_TRUE(vec.at(1) - 10 < s21_EPS);
  EXPECT_TRUE(std_vec.at(1) - 10 < s21_EPS);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  vec[2] = 20.0;
  std_vec[2] = 20.0;

  EXPECT_TRUE(vec[2] - 20.0 < s21_EPS);
  EXPECT_TRUE(std_vec[2] - 20.0 < s21_EPS);

  vec.front() = 30.0;
  std_vec.front() = 30.0;

  EXPECT_TRUE(vec.front() - 30 < s21_EPS);
  EXPECT_TRUE(std_vec.front() - 30 < s21_EPS);

  vec.back() = 40.0;
  std_vec.back() = 40.0;

  EXPECT_TRUE(vec.back() - 40 < s21_EPS);
  EXPECT_TRUE(std_vec.back() - 40 < s21_EPS);
}

TEST(Vector, StringVector) {
  s21::Vector<std::string> vec{"1", "2", "3", "4", "5"};
  std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  vec.at(1) = "10";
  std_vec.at(1) = "10";

  EXPECT_EQ(vec.at(1), "10");
  EXPECT_EQ(std_vec.at(1), "10");

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  vec[2] = "20";
  std_vec[2] = "20";

  EXPECT_EQ(vec[2], "20");
  EXPECT_EQ(std_vec[2], "20");

  vec.front() = "30";
  std_vec.front() = "30";

  EXPECT_EQ(vec.front(), "30");
  EXPECT_EQ(std_vec.front(), "30");

  vec.back() = "40";
  std_vec.back() = "40";

  EXPECT_EQ(vec.back(), "40");
  EXPECT_EQ(std_vec.back(), "40");
}
// CONST!!!
TEST(Vector, ConstIntVector) {
  const s21::Vector<int> vec{1, 2, 3, 4, 5};
  const std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(std_vec.at(1), 2);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(std_vec[2], 3);

  EXPECT_EQ(vec.front(), 1);
  EXPECT_EQ(std_vec.front(), 1);

  EXPECT_EQ(vec.back(), 5);
  EXPECT_EQ(std_vec.back(), 5);
}

TEST(Vector, ConstDoubleVector) {
  const s21::Vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  const std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  EXPECT_TRUE(vec.at(1) - 2.0 < s21_EPS);
  EXPECT_TRUE(std_vec.at(1) - 2.0 < s21_EPS);

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  EXPECT_TRUE(vec[2] - 3.0 < s21_EPS);
  EXPECT_TRUE(std_vec[2] - 3.0 < s21_EPS);

  EXPECT_TRUE(vec.front() - 1.0 < s21_EPS);
  EXPECT_TRUE(std_vec.front() - 1.0 < s21_EPS);

  EXPECT_TRUE(vec.back() - 5.0 < s21_EPS);
  EXPECT_TRUE(std_vec.back() - 5.0 < s21_EPS);
}

TEST(Vector, ConstStringVector) {
  const s21::Vector<std::string> vec{"1", "2", "3", "4", "5"};
  const std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  EXPECT_FALSE(vec.empty());
  EXPECT_FALSE(std_vec.empty());

  EXPECT_EQ(vec.at(1), "2");
  EXPECT_EQ(std_vec.at(1), "2");

  EXPECT_THROW(vec.at(-1), std::out_of_range);
  EXPECT_THROW(vec.at(7), std::out_of_range);
  EXPECT_THROW(std_vec.at(-1), std::out_of_range);
  EXPECT_THROW(std_vec.at(7), std::out_of_range);

  EXPECT_EQ(vec[2], "3");
  EXPECT_EQ(std_vec[2], "3");

  EXPECT_EQ(vec.front(), "1");
  EXPECT_EQ(std_vec.front(), "1");

  EXPECT_EQ(vec.back(), "5");
  EXPECT_EQ(std_vec.back(), "5");
}

// iterators: data, begin, end + reserve

void check_int_iterator(const int* p, std::size_t size) {
  int entry = 0;
  for (std::size_t i = 0; i < size; ++i) {
    EXPECT_EQ(p[i], ++entry);
  }
}

template <typename Iterator>
void check_begin_end_int_iterator(Iterator begin, Iterator end) {
  int entry = 0;
  for (auto it = begin; it != end; ++it) {
    EXPECT_EQ(*it, ++entry);
  }
}

TEST(VectorIterator, IntIterator) {
  s21::Vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  check_int_iterator(vec.data(), vec.size());
  check_int_iterator(std_vec.data(), vec.size());

  vec.reserve(10);
  std_vec.reserve(10);

  check_begin_end_int_iterator(vec.begin(), vec.end());
  check_begin_end_int_iterator(std_vec.begin(), std_vec.end());
}

void check_double_iterator(const double* p, std::size_t size) {
  double entry = 1.0;
  for (std::size_t i = 0; i < size; ++i) {
    EXPECT_TRUE(std::abs(p[i] - entry) < s21_EPS);
    entry += 1.0;
  }
}

template <typename Iterator>
void check_begin_end_double_iterator(Iterator begin, Iterator end) {
  int entry = 1.0;
  for (auto it = begin; it != end; ++it) {
    EXPECT_TRUE(std::abs(*it - entry) < s21_EPS);
    entry += 1.0;
  }
}

TEST(VectorIterator, DoubleIterator) {
  s21::Vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  check_double_iterator(vec.data(), vec.size());
  check_double_iterator(std_vec.data(), vec.size());

  vec.reserve(10);
  std_vec.reserve(10);

  check_begin_end_double_iterator(vec.begin(), vec.end());
  check_begin_end_double_iterator(std_vec.begin(), std_vec.end());
}

void check_string_iterator(const std::string* p, std::size_t size) {
  int entry = 0;
  for (std::size_t i = 0; i < size; ++i) {
    std::string strNumber = std::to_string(++entry);
    EXPECT_EQ(p[i], strNumber);
  }
}

template <typename Iterator>
void check_begin_end_string_iterator(Iterator begin, Iterator end) {
  int entry = 0;
  for (auto it = begin; it != end; ++it) {
    std::string strNumber = std::to_string(++entry);
    EXPECT_EQ(*it, strNumber);
  }
}

TEST(VectorIterator, StringIterator) {
  s21::Vector<std::string> vec{"1", "2", "3", "4", "5"};
  std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  check_string_iterator(vec.data(), vec.size());
  check_string_iterator(std_vec.data(), vec.size());

  vec.reserve(10);
  std_vec.reserve(10);

  check_begin_end_string_iterator(vec.begin(), vec.end());
  check_begin_end_string_iterator(std_vec.begin(), std_vec.end());
}
// CONST!!!
TEST(VectorIterator, ConstIntIterator) {
  const s21::Vector<int> vec{1, 2, 3, 4, 5};
  const std::vector<int> std_vec{1, 2, 3, 4, 5};

  check_int_iterator(vec.data(), vec.size());
  check_int_iterator(std_vec.data(), vec.size());

  check_begin_end_int_iterator(vec.begin(), vec.end());
  check_begin_end_int_iterator(std_vec.begin(), std_vec.end());
}

TEST(VectorIterator, ConstDoubleIterator) {
  const s21::Vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  const std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  check_double_iterator(vec.data(), vec.size());
  check_double_iterator(std_vec.data(), vec.size());

  check_begin_end_double_iterator(vec.begin(), vec.end());
  check_begin_end_double_iterator(std_vec.begin(), std_vec.end());
}

TEST(VectorIterator, ConstStringIterator) {
  const s21::Vector<std::string> vec{"1", "2", "3", "4", "5"};
  const std::vector<std::string> std_vec{"1", "2", "3", "4", "5"};

  check_string_iterator(vec.data(), vec.size());
  check_string_iterator(std_vec.data(), vec.size());

  check_begin_end_string_iterator(vec.begin(), vec.end());
  check_begin_end_string_iterator(std_vec.begin(), std_vec.end());
}

// modifiers: insert, erase, push back, pop back
TEST(Modifiers, IntNotEmptyModifiers) {
  s21::Vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  vec.insert(vec.begin(), 10);
  vec.insert(vec.begin() + 2, 20);
  vec.insert(vec.end(), 30);
  std_vec.insert(std_vec.begin(), 10);
  std_vec.insert(std_vec.begin() + 2, 20);
  std_vec.insert(std_vec.end(), 30);
  ASSERT_EQ(vec.size(), 8U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }

  vec.erase(vec.begin());
  std_vec.erase(std_vec.begin());
  vec.erase(vec.end() - 1);
  std_vec.erase(std_vec.end() - 1);
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }

  vec.push_back(100);
  std_vec.push_back(100);

  ASSERT_EQ(vec.size(), 7U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }

  vec.pop_back();
  std_vec.pop_back();

  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }
}

TEST(Modifiers, IntEmptyBeginModifiers) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  vec.insert(vec.begin(), 10);
  std_vec.insert(std_vec.begin(), 10);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, IntEmptyEndModifiers) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  vec.insert(vec.end(), 10);
  std_vec.insert(std_vec.end(), 10);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, IntEmptyPushModifiers) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  vec.push_back(10);
  std_vec.push_back(10);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, IntEmptyPushCapacityChangeModifiers) {
  s21::Vector<int> vec(5);
  std::vector<int> std_vec(5);

  vec.push_back(10);
  std_vec.push_back(10);
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(5), std_vec.at(5));
}

TEST(Modifiers, DoubleNotEmptyModifiers) {
  s21::Vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> std_vec{1.0, 2.0, 3.0, 4.0, 5.0};

  vec.insert(vec.begin(), 10.0);
  vec.insert(vec.begin() + 2, 20.0);
  vec.insert(vec.end(), 30.0);
  std_vec.insert(std_vec.begin(), 10.0);
  std_vec.insert(std_vec.begin() + 2, 20.0);
  std_vec.insert(std_vec.end(), 30.0);
  ASSERT_EQ(vec.size(), 8U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }

  vec.erase(vec.begin());
  std_vec.erase(std_vec.begin());
  vec.erase(vec.end() - 1);
  std_vec.erase(std_vec.end() - 1);
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }

  vec.push_back(100.0);
  std_vec.push_back(100.0);
  ASSERT_EQ(vec.size(), 7U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }

  vec.pop_back();
  std_vec.pop_back();
  ASSERT_EQ(vec.size(), 6U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE((vec.at(i) - std_vec.at(i) < s21_EPS));
  }
}

TEST(Modifiers, DoubleEmptyBeginModifiers) {
  s21::Vector<double> vec;
  std::vector<double> std_vec;

  vec.insert(vec.begin(), 10.0);
  std_vec.insert(std_vec.begin(), 10.0);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  EXPECT_TRUE((vec.at(0) - std_vec.at(0) < s21_EPS));
}

TEST(Modifiers, DoubleEmptyEndModifiers) {
  s21::Vector<double> vec;
  std::vector<double> std_vec;

  vec.insert(vec.end(), 10.0);
  std_vec.insert(std_vec.end(), 10.0);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  EXPECT_TRUE((vec.at(0) - std_vec.at(0) < s21_EPS));
}

TEST(Modifiers, DoubleEmptyPushModifiers) {
  s21::Vector<double> vec;
  std::vector<double> std_vec;

  vec.push_back(10.0);
  std_vec.push_back(10.0);
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  EXPECT_TRUE((vec.at(0) - std_vec.at(0) < s21_EPS));
}

TEST(Modifiers, StringNotEmptyModifiers) {
  s21::Vector<std::string> vec{"1.0", "2.0", "3.0", "4.0", "5.0"};
  std::vector<std::string> std_vec{"1.0", "2.0", "3.0", "4.0", "5.0"};

  vec.insert(vec.begin(), "10");
  vec.insert(vec.begin() + 2, "20");
  vec.insert(vec.end(), "30");
  std_vec.insert(std_vec.begin(), "10");
  std_vec.insert(std_vec.begin() + 2, "20");
  std_vec.insert(std_vec.end(), "30");
  ASSERT_EQ(vec.size(), 8U);
  ASSERT_EQ(vec.size(), std_vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec.at(i), std_vec.at(i));
  }
}

TEST(Modifiers, StringEmptyBeginModifiers) {
  s21::Vector<std::string> vec;
  std::vector<std::string> std_vec;

  vec.insert(vec.begin(), "10");
  std_vec.insert(std_vec.begin(), "10");
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, StringEmptyEndModifiers) {
  s21::Vector<std::string> vec;
  std::vector<std::string> std_vec;

  vec.insert(vec.end(), "10");
  std_vec.insert(std_vec.end(), "10");
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(Modifiers, StringEmptyPushModifiers) {
  s21::Vector<std::string> vec;
  std::vector<std::string> std_vec;

  vec.push_back("10");
  std_vec.push_back("10");
  ASSERT_EQ(vec.size(), 1U);
  ASSERT_EQ(vec.size(), std_vec.size());
  ASSERT_EQ(vec.at(0), std_vec.at(0));
}

TEST(TestVector, EmptyIterator) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_TRUE(vec.begin() == vec.end());
  EXPECT_TRUE(std_vec.begin() == std_vec.end());
}

// reserve
TEST(TestVector, ReserseSmall) {
  size_t size = 2U;
  s21::Vector<int> vec(size);
  std::vector<int> std_vec(size);

  vec.reserve(1);
  std_vec.reserve(1);

  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

// reserve, shrink_to_fit
TEST(TestVector, ReserseBig) {
  size_t size = 2U;
  s21::Vector<int> vec(size);
  std::vector<int> std_vec(size);

  vec.reserve(5);
  std_vec.reserve(5);

  EXPECT_EQ(vec.capacity(), std_vec.capacity());

  vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(TestVector, Clear) {
  s21::Vector<int> vec;
  vec.clear();
  EXPECT_EQ(0U, vec.size());

  s21::Vector<char> vec2({'a', 'b', 'c'});
  vec2.clear();
  EXPECT_EQ(0U, vec2.size());
}

TEST(TestVector, Swap) {
  s21::Vector<int> vec({1, 2, 3, 4});
  s21::Vector copied_vec(vec);
  auto size = vec.size();
  auto capacity = vec.capacity();
  auto data = vec.data();

  s21::Vector<int> other_vec({5, 6, 7, 8, 9, 10});
  s21::Vector copied_other_vec(other_vec);
  auto other_size = other_vec.size();
  auto other_capacity = other_vec.capacity();
  auto other_data = other_vec.data();

  vec.swap(other_vec);

  EXPECT_EQ(vec.size(), other_size);
  EXPECT_EQ(other_vec.size(), size);

  EXPECT_EQ(copied_other_vec.size(), vec.size());
  EXPECT_EQ(copied_vec.size(), other_vec.size());

  EXPECT_EQ(vec.capacity(), other_capacity);
  EXPECT_EQ(other_vec.capacity(), capacity);

  EXPECT_EQ(vec.data(), other_data);
  EXPECT_EQ(other_vec.data(), data);

  for (size_t i = 0; i < copied_vec.size(); ++i) {
    EXPECT_EQ(copied_vec[i], other_vec[i]);
  }

  for (size_t i = 0; i < copied_other_vec.size(); ++i) {
    EXPECT_EQ(copied_other_vec[i], vec[i]);
  }
}
TEST(TestVector, Empty) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_TRUE(vec.empty());
  EXPECT_TRUE(std_vec.empty());
}

// [] - получим сег фолт даже по стандартному вектору
TEST(TestVector, AtFromEmpty) {
  s21::Vector<int> vec;
  std::vector<int> std_vec;

  EXPECT_THROW(vec.at(0), std::out_of_range);
  EXPECT_THROW(vec.at(1), std::out_of_range);
  EXPECT_THROW(std_vec.at(0), std::out_of_range);
  EXPECT_THROW(std_vec.at(1), std::out_of_range);
}
