#include <gtest/gtest.h>
#include <string.h>

#include <utility>

#include "../s21_containersplus.h"

TEST(S21arrayTest, DefaultConstructor) {
  s21::Array<double, 5> arr2;
  EXPECT_EQ(arr2.size(), 5.0);
}

TEST(S21arrayTest, testzero) {
  s21::Array<double, 0> arr;
  EXPECT_EQ(arr.size(), 0.0);
}

TEST(s21Array, initial) {
  s21::Array<int, 7> arr;
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayInitializationTest, InitializerListTest) {
  s21::Array<int, 3> arr5 = {10, 20, 30};
  EXPECT_EQ(arr5[0], 10);
  EXPECT_EQ(arr5[1], 20);
  EXPECT_EQ(arr5[2], 30);
}

TEST(S21arrayTest, copyconstructor) {
  s21::Array<int, 10> array;

  for (size_t i = 0; i < array.size(); ++i) {
    array[i] = i;
  }
  s21::Array<int, 10> copy_array(array);

  for (size_t i = 0; i < array.size(); ++i) {
    EXPECT_EQ(array[i], copy_array[i]);
  }
}

TEST(S21arrayTest1, Hellow) {
  s21::Array<std::string, 2> hellow;
  hellow[0] = "Hellow";
  hellow[1] = "World!";

  for (size_t i = 0; i < hellow.size(); ++i) {
    EXPECT_EQ(hellow[i], hellow[i]);
  }
}

TEST(S21arrayTest2, FloatTest) {
  s21::Array<double, 100> colec_float;
  for (size_t i = 0; i < colec_float.size(); ++i) {
    colec_float[i] = i;
  }
  for (size_t i = 0; i < colec_float.size(); ++i) {
    EXPECT_EQ(colec_float[i], i);
  }
}

TEST(S21Array_copy, copy_int_float_string) {
  s21::Array<std::string, 2> hellow;
  hellow[0] = "Hellow";
  hellow[1] = "World!";
  s21::Array<std::string, 2> dest_hellow = hellow;
  s21::Array<double, 100> colec_float;
  for (size_t i = 0; i < colec_float.size(); ++i) {
    colec_float[i] = i;
  }
  s21::Array<double, 100> dest_float = colec_float;
  s21::Array<int, 100> colec_int;
  for (size_t i = 0; i < colec_int.size(); ++i) {
    colec_int[i] = i;
  }
  s21::Array<int, 100> dest_int = colec_int;

  EXPECT_EQ(dest_hellow[0], hellow[0]);
  EXPECT_EQ(dest_hellow[1], hellow[1]);

  for (size_t i = 0; i < dest_float.size(); ++i) {
    EXPECT_EQ(dest_float[i], colec_float[i]);
  }

  for (size_t i = 0; i < dest_int.size(); ++i) {
    EXPECT_EQ(dest_int[i], colec_int[i]);
  }
}

TEST(S21ArraySize, Size_double) {
  s21::Array<double, 3> arr;

  for (size_t i = 0; i < arr.size(); ++i) {
    arr[i] = i * 1.5;
  }

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_DOUBLE_EQ(arr[i], i * 1.5);
  }
}

TEST(S21ArraySize, Size_char) {
  s21::Array<char, 10> arr;

  EXPECT_EQ(static_cast<int>(arr.size()), 10);

  s21::Array<std::string, 1> arr2;
  EXPECT_EQ(arr2.size(), static_cast<size_t>(1));
}

TEST(S21ArrayAt, int_test) {
  s21::Array<int, 10> arrayint;
  for (size_t i = 0; i > arrayint.size(); ++i) {
    arrayint[i] = i + 15;
  }

  EXPECT_THROW(arrayint.at(11), std::invalid_argument);
}
TEST(S21ArrayAt, TestFloat) {
  s21::Array<float, 10> arrayfloat;
  for (size_t i = 0; i > arrayfloat.size(); ++i) {
    arrayfloat[i] = 0.0;
  }
  EXPECT_THROW(arrayfloat.at(-11), std::invalid_argument);
}

TEST(Arryoperatoreq, testoperator) {
  s21::Array<int, 50> eqarray;
  for (size_t i = 0; i < eqarray.size(); i++) {
    eqarray[i] = i + 2;
  }
  s21::Array<int, 50> &destarray = eqarray;

  for (size_t i = 0; i < eqarray.size(); i++) {
    EXPECT_EQ(destarray[i], eqarray[i]);
  }
}
TEST(S21Array, testchar) {
  s21::Array<char, 50> eqarray;
  for (size_t i = 0; i < eqarray.size(); ++i) {
    eqarray[i] = i;
  }
  s21::Array<char, 50> &destarray = eqarray;
  for (size_t i = 0; i < eqarray.size(); i++) {
    EXPECT_EQ(destarray[i], eqarray[i]);
  }
}

TEST(S21Array, constfloat) {
  s21::Array<float, 5> array;
  for (size_t i = 0; i < array.size(); ++i) {
    array[i] = 0.0;
  }
  const s21::Array<float, 5> &const_array = array;
  for (size_t i = 0; i < const_array.size(); ++i) {
    EXPECT_EQ(array[i], const_array[i]);
  }
}

TEST(S21Array, conststr) {
  s21::Array<std::string, 100> arraystr;
  for (size_t i = 0; i < arraystr.size(); ++i) {
    arraystr[i] = "0";
  }
  const s21::Array<std::string, 100> &const_array = arraystr;
  for (size_t i = 0; i < const_array.size(); ++i) {
    EXPECT_EQ(arraystr[i], const_array[i]);
  }
}

TEST(S21Array, constchar) {
  s21::Array<char, 10> arraychar;
  for (size_t i = 0; i < arraychar.size(); ++i) {
    arraychar[i] = '0';
  }
  const s21::Array<char, 10> &const_array = arraychar;
  for (size_t i = 0; i < const_array.size(); ++i) {
    EXPECT_EQ(arraychar[i], const_array[i]);
  }
}

TEST(S21ArrayTest, Test) {
  s21::Array<int, 5> arr;
  const s21::Array<int, 5> &const_arr = arr;

  for (size_t i = 0; i < const_arr.size(); ++i) {
    EXPECT_EQ(const_arr[i], arr[i]);
  }
}

TEST(S21Array, data) {
  s21::Array<int, 3> datarray;
  datarray[0] = 1;
  EXPECT_EQ(datarray.data(), &datarray[0]);
}

TEST(S21Array, end) {
  s21::Array<int, 4> endarray;

  auto Ptr4 = &endarray[4];

  EXPECT_EQ(endarray.end(), Ptr4);
}

TEST(S21Array, testint) {
  s21::Array<int, 10> valint;
  auto Ptr = valint[0];
  auto Ptr2 = valint.front();
  EXPECT_EQ(Ptr, Ptr2);
}

TEST(S21Array_char, testchar) {
  s21::Array<char, 6> valchar;
  for (auto i = 0; i < 6; ++i) {
    valchar[i] = 'a' + i;
  }
  auto Ptr = valchar[0];
  auto Ptr2 = valchar.front();
  EXPECT_EQ(Ptr, Ptr2);
}
TEST(S21Array_string, test_string) {
  s21::Array<std::string, 2> valstring;
  s21::Array<std::string, 2> word;
  word[0] = "Hello schcool 21";
  valstring[0] = "Hello schcool 21";
  EXPECT_EQ(valstring.front(), word.front());
}

TEST(S21Array_back, test_char) {
  s21::Array<char, 6> letters;
  for (auto i = 0; i < 6; ++i) {
    letters[i] = 'a' + i;
  }

  EXPECT_EQ(letters.back(), letters[5]);
}
TEST(S21array_back, test_int) {
  s21::Array<int, 6> intvalue;
  for (auto i = 0; i < 6; ++i) {
    intvalue[i] = i;
  }
  EXPECT_EQ(intvalue.back(), intvalue[5]);
}

TEST(s21Array_back, test_float) {
  s21::Array<float, 10> floatvalue;
  for (auto i = 0; i < 10; ++i) {
    floatvalue[i] = i;
  }
  EXPECT_EQ(floatvalue.back(), floatvalue[9]);
}

TEST(S21Array, empty_zero) {
  s21::Array<float, 0> zero;
  ASSERT_TRUE(zero.empty());
}
TEST(S21Array, empty_full) {
  s21::Array<int, 3> full;
  for (size_t i = 0; i < full.size(); ++i) {
    full[i] = i;
  }
  EXPECT_FALSE(full.empty());
}

TEST(S21Array, swap) {
  s21::Array<int, 3> origin = {1, 2, 3};
  s21::Array<int, 3> coppy = {0, 0, 0};
  s21::Array<int, 3> zero = {0, 0, 0};
  s21::Array<int, 3> num = {1, 2, 3};
  origin.swap(coppy);
  for (size_t i = 0; i < origin.size(); ++i) {
    EXPECT_EQ(zero[i], origin[i]);
    EXPECT_EQ(num[i], coppy[i]);
  }
}

TEST(S21ARRAY, operatoreqfalse) {
  s21::Array<int, 3> origin = {1, 2, 3};
  s21::Array<int, 3> coppy = {0, 0, 0};
  bool res;
  res = origin == coppy;
  EXPECT_FALSE(res);
}
TEST(S21ARRAY, operatoreqtrue) {
  s21::Array<float, 3> zero_n1 = {0.0, 0.0, 0.0};
  s21::Array<float, 3> zero_n2 = {0.0, 0.0, 0.0};
  EXPECT_TRUE(zero_n1 == zero_n2);
}
