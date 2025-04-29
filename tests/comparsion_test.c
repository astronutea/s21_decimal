#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

START_TEST(test_is_equal) {
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);

  a.bits[0] = 1;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_not_equal) {
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};

  ck_assert_int_eq(s21_is_not_equal(a, b), 0);

  a.bits[0] = 1;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_greater) {
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};

  ck_assert_int_eq(s21_is_greater(a, b), 0);

  a.bits[0] = 2;
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_greater(a, b), 1);

  ck_assert_int_eq(s21_is_greater(b, a), 0);
}
END_TEST

START_TEST(test_is_less) {
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};

  ck_assert_int_eq(s21_is_less(a, b), 0);

  a.bits[0] = 1;
  b.bits[0] = 2;
  ck_assert_int_eq(s21_is_less(a, b), 1);

  ck_assert_int_eq(s21_is_less(b, a), 0);
}
END_TEST

START_TEST(test_is_greater_or_equal) {
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);

  a.bits[0] = 2;
  b.bits[0] = 1;
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);

  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 0);
}
END_TEST

START_TEST(test_is_less_or_equal) {
  s21_decimal a = {{0}};
  s21_decimal b = {{0}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  a.bits[0] = 1;
  b.bits[0] = 2;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
}
END_TEST

Suite *comparison_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Comparison Operations");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_equal);
  tcase_add_test(tc_core, test_is_not_equal);
  tcase_add_test(tc_core, test_is_greater);
  tcase_add_test(tc_core, test_is_less);
  tcase_add_test(tc_core, test_is_greater_or_equal);
  tcase_add_test(tc_core, test_is_less_or_equal);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = comparison_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}