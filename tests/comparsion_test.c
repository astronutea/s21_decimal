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

START_TEST(test_is_less_1) {
  s21_decimal a, b;
  s21_null_decimal(&a);
  s21_null_decimal(&b);
  a.bits[0] = 3;
  b.bits[0] = 5;
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

Suite *comparsion_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Comparison Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_equal_1);
  tcase_add_test(tc_core, test_is_equal_2);
  tcase_add_test(tc_core, test_is_equal_3);
  tcase_add_test(tc_core, test_is_equal_4);
  tcase_add_test(tc_core, test_is_greater_1);
  tcase_add_test(tc_core, test_is_greater_2);
  tcase_add_test(tc_core, test_is_greater_3);
  tcase_add_test(tc_core, test_is_greater_4);
  tcase_add_test(tc_core, test_is_less_1);
  tcase_add_test(tc_core, test_is_less_2);
  tcase_add_test(tc_core, test_is_less_3);
  tcase_add_test(tc_core, test_is_less_4);
  tcase_add_test(tc_core, test_is_less_or_equal_1);
  tcase_add_test(tc_core, test_is_less_or_equal_2);
  tcase_add_test(tc_core, test_is_less_or_equal_3);
  tcase_add_test(tc_core, test_is_less_or_equal_4);
  tcase_add_test(tc_core, test_is_not_equal_1);
  tcase_add_test(tc_core, test_is_not_equal_2);
  tcase_add_test(tc_core, test_is_not_equal_3);
  tcase_add_test(tc_core, test_is_not_equal_4);
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