#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

START_TEST(test_is_equal) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_equal_negative) {
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

START_TEST(test_is_equal_different_signs) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_greater) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;

  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
}
END_TEST

START_TEST(test_is_greater_negative) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater(b, a), 1);
}
END_TEST

START_TEST(test_is_less) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);
}
END_TEST

START_TEST(test_is_less_negative) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_is_less_or_equal) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, a), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_negative) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, a), 1);
}
END_TEST

START_TEST(test_is_not_equal) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;

  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, a), 0);
}
END_TEST

START_TEST(test_is_not_equal_negative) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 5;
  s21_set_sign(&a, 1);

  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, a), 0);
}
END_TEST

START_TEST(test_is_greater_or_equal) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, a), 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_negative) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 5;
  b.bits[0] = 3;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, a), 1);
}
END_TEST

Suite *comparsion_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Comparison Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_equal);
  tcase_add_test(tc_core, test_is_equal_negative);
  tcase_add_test(tc_core, test_is_equal_different_signs);
  tcase_add_test(tc_core, test_is_greater);
  tcase_add_test(tc_core, test_is_greater_negative);
  tcase_add_test(tc_core, test_is_less);
  tcase_add_test(tc_core, test_is_less_negative);
  tcase_add_test(tc_core, test_is_less_or_equal);
  tcase_add_test(tc_core, test_is_less_or_equal_negative);
  tcase_add_test(tc_core, test_is_not_equal);
  tcase_add_test(tc_core, test_is_not_equal_negative);
  tcase_add_test(tc_core, test_is_greater_or_equal);
  tcase_add_test(tc_core, test_is_greater_or_equal_negative);
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