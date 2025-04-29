#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_addition) {
  s21_decimal num1, num2, result;
  // Инициализация num1 и num2
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;

  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 8);
}
END_TEST

START_TEST(test_addition_negative) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num2, 1);  // -3

  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_subtraction) {
  s21_decimal num1, num2, result;
  // Инициализация num1 и num2
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;

  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_subtraction_negative) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num1, 1);  // -5

  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_multiplication) {
  s21_decimal num1, num2, result;
  // Инициализация num1 и num2
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;

  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(test_multiplication_negative) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num1, 1);  // -5

  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_division) {
  s21_decimal num1, num2, result;
  // Инициализация num1 и num2
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 6;
  num2.bits[0] = 2;

  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
}
END_TEST

START_TEST(test_division_by_zero) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 6;
  num2.bits[0] = 0;

  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 3);  // Ошибка деления на ноль
}
END_TEST

START_TEST(test_division_with_scale) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 60;
  num2.bits[0] = 2;
  s21_set_scale(&num1, 1);  // 6.0
  s21_set_scale(&num2, 0);  // 2

  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(s21_get_scale(&result), 1);
}
END_TEST

START_TEST(test_division_negative) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 6;
  num2.bits[0] = 2;
  s21_set_sign(&num1, 1);  // -6

  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_division_large_numbers) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 1000000;
  num2.bits[0] = 2;

  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 500000);
}
END_TEST

Suite *arithmetic_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Arithmetic");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_addition);
  tcase_add_test(tc_core, test_addition_negative);
  tcase_add_test(tc_core, test_subtraction);
  tcase_add_test(tc_core, test_subtraction_negative);
  tcase_add_test(tc_core, test_multiplication);
  tcase_add_test(tc_core, test_multiplication_negative);
  tcase_add_test(tc_core, test_division);
  tcase_add_test(tc_core, test_division_by_zero);
  tcase_add_test(tc_core, test_division_with_scale);
  tcase_add_test(tc_core, test_division_negative);
  tcase_add_test(tc_core, test_division_large_numbers);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = arithmetic_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}