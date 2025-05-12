#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_add_1) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 8);
}
END_TEST

START_TEST(test_add_2) {
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

START_TEST(test_add_3) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num1, 1);  // -5
  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_add_4) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num1, 1);  // -5
  s21_set_sign(&num2, 1);  // -3
  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_add_5) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 0xFFFFFFFF;
  num2.bits[0] = 1;
  int status = s21_add(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 1);
}
END_TEST

START_TEST(test_sub_1) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_sub_2) {
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

START_TEST(test_sub_3) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num2, 1);  // -3
  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 8);
}
END_TEST

START_TEST(test_sub_4) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 5;
  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_sub_5) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 0;
  num2.bits[0] = 5;
  int status = s21_sub(&num1, &num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(test_mul_1) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(test_mul_2) {
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

START_TEST(test_mul_3) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 5;
  num2.bits[0] = 3;
  s21_set_sign(&num1, 1);  // -5
  s21_set_sign(&num2, 1);  // -3
  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(test_mul_4) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 0xFFFFFFFF;
  num2.bits[0] = 2;
  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 1);
}
END_TEST

START_TEST(test_mul_5) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 0;
  num2.bits[0] = 5;
  int status = s21_mul(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

// START_TEST(test_div_1) {
//   s21_decimal num1, num2, result;
//   s21_null_decimal(&num1);
//   s21_null_decimal(&num2);
//   num1.bits[0] = 6;
//   num2.bits[0] = 2;
//   int status = s21_div(num1, num2, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_int_eq(result.bits[0], 3);
// }
// END_TEST

// START_TEST(test_div_2) {
//   s21_decimal num1, num2, result;
//   s21_null_decimal(&num1);
//   s21_null_decimal(&num2);
//   num1.bits[0] = 6;
//   num2.bits[0] = 2;
//   s21_set_sign(&num1, 1);  // -6
//   int status = s21_div(num1, num2, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_int_eq(result.bits[0], 3);
//   ck_assert_int_eq(s21_get_sign(&result), 1);
// }
// END_TEST

// START_TEST(test_div_3) {
//   s21_decimal num1, num2, result;
//   s21_null_decimal(&num1);
//   s21_null_decimal(&num2);
//   num1.bits[0] = 6;
//   num2.bits[0] = 2;
//   s21_set_sign(&num1, 1);  // -6
//   s21_set_sign(&num2, 1);  // -2
//   int status = s21_div(num1, num2, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_int_eq(result.bits[0], 3);
//   ck_assert_int_eq(s21_get_sign(&result), 0);
// }
// END_TEST

// START_TEST(test_div_4) {
//   s21_decimal num1, num2, result;
//   s21_null_decimal(&num1);
//   s21_null_decimal(&num2);
//   num1.bits[0] = 6;
//   num2.bits[0] = 0;
//   int status = s21_div(num1, num2, &result);
//   ck_assert_int_eq(status, 3);  // Деление на ноль
// }
// END_TEST

// START_TEST(test_div_5) {
//   s21_decimal num1, num2, result;
//   s21_null_decimal(&num1);
//   s21_null_decimal(&num2);
//   num1.bits[0] = 0;
//   num2.bits[0] = 5;
//   int status = s21_div(num1, num2, &result);
//   ck_assert_int_eq(status, 0);
//   ck_assert_int_eq(result.bits[0], 0);
// }
// END_TEST

Suite *arithmetic_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Arithmetic");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add_1);
  tcase_add_test(tc_core, test_add_2);
  tcase_add_test(tc_core, test_add_3);
  tcase_add_test(tc_core, test_add_4);
  tcase_add_test(tc_core, test_add_5);
  tcase_add_test(tc_core, test_sub_1);
  tcase_add_test(tc_core, test_sub_2);
  tcase_add_test(tc_core, test_sub_3);
  tcase_add_test(tc_core, test_sub_4);
  tcase_add_test(tc_core, test_sub_5);
  tcase_add_test(tc_core, test_mul_1);
  tcase_add_test(tc_core, test_mul_2);
  tcase_add_test(tc_core, test_mul_3);
  tcase_add_test(tc_core, test_mul_4);
  tcase_add_test(tc_core, test_mul_5);
  // tcase_add_test(tc_core, test_div_1);
  // tcase_add_test(tc_core, test_div_2);
  // tcase_add_test(tc_core, test_div_3);
  // tcase_add_test(tc_core, test_div_4);
  // tcase_add_test(tc_core, test_div_5);
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