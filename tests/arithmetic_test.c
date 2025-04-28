#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_addition) {
  s21_decimal num1, num2, result, expected;
  // Инициализация num1 и num2
  // Установите ожидаемый результат в expected

  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  // Сравните result с expected
}
END_TEST

START_TEST(test_subtraction) {
  s21_decimal num1, num2, result, expected;
  // Инициализация num1 и num2
  // Установите ожидаемый результат в expected

  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  // Сравните result с expected
}
END_TEST

START_TEST(test_multiplication) {
  s21_decimal num1, num2, result, expected;
  // Инициализация num1 и num2
  // Установите ожидаемый результат в expected

  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  // Сравните result с expected
}
END_TEST

START_TEST(test_division) {
  s21_decimal num1, num2, result, expected;
  // Инициализация num1 и num2
  // Установите ожидаемый результат в expected

  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  // Сравните result с expected
}
END_TEST

Suite *arithmetic_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Arithmetic");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_addition);
  tcase_add_test(tc_core, test_subtraction);
  tcase_add_test(tc_core, test_multiplication);
  tcase_add_test(tc_core, test_division);
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