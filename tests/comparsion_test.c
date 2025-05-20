#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

START_TEST(test_is_equal_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);  // -0 == 0
}
END_TEST

START_TEST(test_is_equal_5) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_6) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 5);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_7) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_8) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 27);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_5) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 4);
  s21_set_scale(&b, 5);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_6) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_7) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 27);  // -99999999.9999
  s21_set_scale(&b, 28);  // -9999999.99999
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_less_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 555;  // 5.55
  b.bits[0] = 555;  // 55.5
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_5) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 4);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_6) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_7) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_or_equal_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_5) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 5);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_6) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_7) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_not_equal_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);  // -0 == 0
}
END_TEST

START_TEST(test_is_not_equal_5) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 4);
  s21_set_scale(&b, 5);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_6) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_not_equal_7) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_9) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_10) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_11) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_12) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_8) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_9) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_less_8) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_9) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_8) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_or_equal_9) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_8) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_9) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_max_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_max_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_min_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 1;
  b.bits[0] = 1;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_min_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 1;
  b.bits[0] = 1;
  s21_set_scale(&a, 28);
  s21_set_scale(&b, 28);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_zero_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_zero_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_scale_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 12345;
  b.bits[0] = 12345;
  s21_set_scale(&a, 3);
  s21_set_scale(&b, 3);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_scale_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 12345;
  b.bits[0] = 12345;
  s21_set_scale(&a, 3);
  s21_set_scale(&b, 4);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_scale_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 12345;
  b.bits[0] = 12345;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 6);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_scale_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 12345;
  b.bits[0] = 12345;
  s21_set_scale(&a, 5);
  s21_set_scale(&b, 5);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_sign_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 12345;
  b.bits[0] = 12345;
  s21_set_scale(&a, 3);
  s21_set_scale(&b, 3);
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_sign_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 12345;
  b.bits[0] = 12345;
  s21_set_scale(&a, 3);
  s21_set_scale(&b, 3);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_boundary_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_boundary_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_bits_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xAAAAAAAA;
  b.bits[0] = 0xAAAAAAAA;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_bits_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0x55555555;
  b.bits[0] = 0x55555555;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_max_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 27);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_max_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 27);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_min_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 1;
  b.bits[0] = 1;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 27);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_min_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 1;
  b.bits[0] = 1;
  s21_set_scale(&a, 27);
  s21_set_scale(&b, 27);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_zero_3) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_zero_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_scale_min_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 1;
  b.bits[0] = 1;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_equal_scale_min_2) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 1;
  b.bits[0] = 1;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_greater_12) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_13) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_is_less_12) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_13) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_12) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_or_equal_13) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_12) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 2);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_not_equal_13) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0xFFFFFFFF;
  b.bits[0] = 0xFFFFFFFF;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_bits_4) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0x55555555;
  a.bits[1] = 0x55555555;
  b.bits[0] = 0x55555555;
  b.bits[1] = 0x55555555;
  s21_set_scale(&a, 1);
  s21_set_scale(&b, 1);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_zero_5) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 3);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_zero_6) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 0;
  b.bits[0] = 0;
  s21_set_scale(&a, 2);
  s21_set_scale(&b, 3);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

Suite *comparsion_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Comparison Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_equal_1);
  tcase_add_test(tc_core, test_is_equal_2);
  tcase_add_test(tc_core, test_is_equal_3);
  tcase_add_test(tc_core, test_is_equal_4);
  tcase_add_test(tc_core, test_is_equal_5);
  tcase_add_test(tc_core, test_is_equal_6);
  tcase_add_test(tc_core, test_is_equal_7);
  tcase_add_test(tc_core, test_is_equal_8);
  tcase_add_test(tc_core, test_is_greater_1);
  tcase_add_test(tc_core, test_is_greater_2);
  tcase_add_test(tc_core, test_is_greater_3);
  tcase_add_test(tc_core, test_is_greater_4);
  tcase_add_test(tc_core, test_is_greater_5);
  tcase_add_test(tc_core, test_is_greater_6);
  tcase_add_test(tc_core, test_is_greater_7);
  tcase_add_test(tc_core, test_is_less_1);
  tcase_add_test(tc_core, test_is_less_2);
  tcase_add_test(tc_core, test_is_less_3);
  tcase_add_test(tc_core, test_is_less_4);
  tcase_add_test(tc_core, test_is_less_5);
  tcase_add_test(tc_core, test_is_less_6);
  tcase_add_test(tc_core, test_is_less_7);
  tcase_add_test(tc_core, test_is_less_or_equal_1);
  tcase_add_test(tc_core, test_is_less_or_equal_2);
  tcase_add_test(tc_core, test_is_less_or_equal_3);
  tcase_add_test(tc_core, test_is_less_or_equal_4);
  tcase_add_test(tc_core, test_is_less_or_equal_5);
  tcase_add_test(tc_core, test_is_less_or_equal_6);
  tcase_add_test(tc_core, test_is_less_or_equal_7);
  tcase_add_test(tc_core, test_is_not_equal_1);
  tcase_add_test(tc_core, test_is_not_equal_2);
  tcase_add_test(tc_core, test_is_not_equal_3);
  tcase_add_test(tc_core, test_is_not_equal_4);
  tcase_add_test(tc_core, test_is_not_equal_5);
  tcase_add_test(tc_core, test_is_not_equal_6);
  tcase_add_test(tc_core, test_is_not_equal_7);
  tcase_add_test(tc_core, test_is_equal_9);
  tcase_add_test(tc_core, test_is_equal_10);
  tcase_add_test(tc_core, test_is_equal_11);
  tcase_add_test(tc_core, test_is_equal_12);
  tcase_add_test(tc_core, test_is_greater_8);
  tcase_add_test(tc_core, test_is_greater_9);
  tcase_add_test(tc_core, test_is_less_8);
  tcase_add_test(tc_core, test_is_less_9);
  tcase_add_test(tc_core, test_is_less_or_equal_8);
  tcase_add_test(tc_core, test_is_less_or_equal_9);
  tcase_add_test(tc_core, test_is_not_equal_8);
  tcase_add_test(tc_core, test_is_not_equal_9);
  tcase_add_test(tc_core, test_is_equal_max_1);
  tcase_add_test(tc_core, test_is_equal_max_2);
  tcase_add_test(tc_core, test_is_equal_min_1);
  tcase_add_test(tc_core, test_is_equal_min_2);
  tcase_add_test(tc_core, test_is_equal_zero_1);
  tcase_add_test(tc_core, test_is_equal_zero_2);
  tcase_add_test(tc_core, test_is_equal_scale_1);
  tcase_add_test(tc_core, test_is_equal_scale_2);
  tcase_add_test(tc_core, test_is_equal_scale_3);
  tcase_add_test(tc_core, test_is_equal_scale_4);
  tcase_add_test(tc_core, test_is_equal_sign_1);
  tcase_add_test(tc_core, test_is_equal_sign_2);
  tcase_add_test(tc_core, test_is_equal_boundary_1);
  tcase_add_test(tc_core, test_is_equal_boundary_2);
  tcase_add_test(tc_core, test_is_equal_bits_1);
  tcase_add_test(tc_core, test_is_equal_bits_2);
  tcase_add_test(tc_core, test_is_equal_max_3);
  tcase_add_test(tc_core, test_is_equal_max_4);
  tcase_add_test(tc_core, test_is_equal_min_3);
  tcase_add_test(tc_core, test_is_equal_min_4);
  tcase_add_test(tc_core, test_is_equal_zero_3);
  tcase_add_test(tc_core, test_is_equal_zero_4);
  tcase_add_test(tc_core, test_is_equal_bits_4);
  tcase_add_test(tc_core, test_is_equal_zero_5);
  tcase_add_test(tc_core, test_is_equal_zero_6);
  tcase_add_test(tc_core, test_is_equal_scale_min_1);
  tcase_add_test(tc_core, test_is_equal_scale_min_2);
  tcase_add_test(tc_core, test_is_greater_12);
  tcase_add_test(tc_core, test_is_greater_13);
  tcase_add_test(tc_core, test_is_less_12);
  tcase_add_test(tc_core, test_is_less_13);
  tcase_add_test(tc_core, test_is_less_or_equal_12);
  tcase_add_test(tc_core, test_is_less_or_equal_13);
  tcase_add_test(tc_core, test_is_not_equal_12);
  tcase_add_test(tc_core, test_is_not_equal_13);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = comparsion_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}