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
  ck_assert_int_eq((unsigned int)result.bits[0], 0xFFFFFFFE);
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

START_TEST(test_div_1) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 6;
  num2.bits[0] = 2;
  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
}
END_TEST

START_TEST(test_div_2) {
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

START_TEST(test_div_3) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 6;
  num2.bits[0] = 2;
  s21_set_sign(&num1, 1);  // -6
  s21_set_sign(&num2, 1);  // -2
  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(test_div_4) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 6;
  num2.bits[0] = 0;
  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 3);  // Деление на ноль
}
END_TEST

START_TEST(test_div_5) {
  s21_decimal num1, num2, result;
  s21_null_decimal(&num1);
  s21_null_decimal(&num2);
  num1.bits[0] = 0;
  num2.bits[0] = 5;
  int status = s21_div(num1, num2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

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
  tcase_add_test(tc_core, test_div_1);
  tcase_add_test(tc_core, test_div_2);
  tcase_add_test(tc_core, test_div_3);
  tcase_add_test(tc_core, test_div_4);
  tcase_add_test(tc_core, test_div_5);
  suite_add_tcase(s, tc_core);

  return s;
}

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

START_TEST(test_from_decimal_to_float_1) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 12345;
  s21_set_scale(&src, 3);  // 12.345
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(dst, 12.345f);
}
END_TEST

START_TEST(test_from_decimal_to_float_2) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 12345;
  s21_set_scale(&src, 3);
  s21_set_sign(&src, 1);  // -12.345
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(dst, -12.345f);
}
END_TEST

START_TEST(test_from_decimal_to_float_3) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 0;  // 0
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(dst, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_4) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 0xFFFFFFFF;
  src.bits[1] = 0xFFFFFFFF;
  src.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&src, 0);  // Максимальное значение
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(dst, 79228162514264337593543950335.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_5) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 12345;
  s21_set_scale(&src, 3);
  float *dst = NULL;
  int status = s21_from_decimal_to_float(src, dst);
  ck_assert_int_eq(status, 1);  // ERROR_CONVERT
}
END_TEST

// Тесты для s21_from_decimal_to_int
START_TEST(test_from_decimal_to_int_1) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 12345;
  s21_set_scale(&src, 3);  // 12.345
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst, 12);
}
END_TEST

START_TEST(test_from_decimal_to_int_2) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 12345;
  s21_set_scale(&src, 3);
  s21_set_sign(&src, 1);  // -12.345
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst, -12);
}
END_TEST

START_TEST(test_from_decimal_to_int_3) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 0;  // 0
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_4) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 0xFFFFFFFF;
  src.bits[1] = 0xFFFFFFFF;
  src.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&src, 0);  // Максимальное значение
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, 1);  // ERROR_CONVERT
}
END_TEST

START_TEST(test_from_decimal_to_int_5) {
  s21_decimal src;
  s21_null_decimal(&src);
  src.bits[0] = 12345;
  s21_set_scale(&src, 3);
  int *dst = NULL;
  int status = s21_from_decimal_to_int(src, dst);
  ck_assert_int_eq(status, 1);  // ERROR_CONVERT
}
END_TEST

// Тесты для s21_from_float_to_decimal
START_TEST(test_from_float_to_decimal_1) {
  float src = 12.345f;
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(s21_get_scale(&dst), 3);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_2) {
  float src = -12.345f;
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(s21_get_scale(&dst), 3);
  ck_assert_int_eq(s21_get_sign(&dst), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_3) {
  float src = 0.0f;
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_4) {
  float src = 1e-29f;  // Меньше минимального
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, 1);  // ERROR_CONVERT
}
END_TEST

START_TEST(test_from_float_to_decimal_5) {
  float src = 12.345f;
  s21_decimal *dst = NULL;
  int status = s21_from_float_to_decimal(src, dst);
  ck_assert_int_eq(status, 1);  // ERROR_CONVERT
}
END_TEST

// Тесты для s21_from_int_to_decimal
START_TEST(test_from_int_to_decimal_1) {
  int src = 12345;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_2) {
  int src = -12345;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(s21_get_sign(&dst), 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_3) {
  int src = 0;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_4) {
  int src = INT_MAX;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(dst.bits[0], INT_MAX);
  ck_assert_int_eq(s21_get_sign(&dst), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_5) {
  int src = 12345;
  s21_decimal *dst = NULL;
  int status = s21_from_int_to_decimal(src, dst);
  ck_assert_int_eq(status, 1);  // ERROR_CONVERT
}
END_TEST

Suite *conversion_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Conversion Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_from_decimal_to_float_1);
  tcase_add_test(tc_core, test_from_decimal_to_float_2);
  tcase_add_test(tc_core, test_from_decimal_to_float_3);
  tcase_add_test(tc_core, test_from_decimal_to_float_4);
  tcase_add_test(tc_core, test_from_decimal_to_float_5);
  tcase_add_test(tc_core, test_from_decimal_to_int_1);
  tcase_add_test(tc_core, test_from_decimal_to_int_2);
  tcase_add_test(tc_core, test_from_decimal_to_int_3);
  tcase_add_test(tc_core, test_from_decimal_to_int_4);
  tcase_add_test(tc_core, test_from_decimal_to_int_5);
  tcase_add_test(tc_core, test_from_float_to_decimal_1);
  tcase_add_test(tc_core, test_from_float_to_decimal_2);
  tcase_add_test(tc_core, test_from_float_to_decimal_3);
  tcase_add_test(tc_core, test_from_float_to_decimal_4);
  tcase_add_test(tc_core, test_from_float_to_decimal_5);
  tcase_add_test(tc_core, test_from_int_to_decimal_1);
  tcase_add_test(tc_core, test_from_int_to_decimal_2);
  tcase_add_test(tc_core, test_from_int_to_decimal_3);
  tcase_add_test(tc_core, test_from_int_to_decimal_4);
  tcase_add_test(tc_core, test_from_int_to_decimal_5);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_floor_1) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // floor(12.345) = 12
  int status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_floor_2) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 13;
  s21_set_sign(&expected, 1);  // floor(-12.345) = -13
  int status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_floor_3) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 0);  // 12345
  s21_null_decimal(&expected);
  expected.bits[0] = 12345;  // floor(12345) = 12345
  int status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_floor_4) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 0);
  s21_set_sign(&num, 1);  // -12345
  s21_null_decimal(&expected);
  expected.bits[0] = 12345;
  s21_set_sign(&expected, 1);  // floor(-12345) = -12345
  int status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_floor_5) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 4);  // 1.2345
  s21_null_decimal(&expected);
  expected.bits[0] = 1;  // floor(1.2345) = 1
  int status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_negate_1) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12345;
  s21_set_scale(&expected, 3);
  s21_set_sign(&expected, 1);  // -12.345
  int status = s21_negate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_negate_2) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12345;
  s21_set_scale(&expected, 3);  // 12.345
  int status = s21_negate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_negate_3) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 0;  // 0
  s21_null_decimal(&expected);
  expected.bits[0] = 0;
  s21_set_sign(&expected, 1);  // -0
  int status = s21_negate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_negate_4) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 0;
  s21_set_sign(&num, 1);  // -0
  s21_null_decimal(&expected);
  expected.bits[0] = 0;  // 0
  int status = s21_negate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_negate_5_fn) {
  s21_decimal num;
  s21_null_decimal(&num);
  num.bits[0] = 0xFFFFFFFF;
  num.bits[1] = 0xFFFFFFFF;
  num.bits[2] = 0xFFFFFFFF;
  s21_set_sign(&num, 1);
  ck_assert_int_eq(s21_negate(num, &num), 0);
  ck_assert_int_eq(s21_get_sign(&num), 0);
}
END_TEST

START_TEST(test_round_1) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // round(12.345) = 12
  int status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_round_2) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12745;
  s21_set_scale(&num, 3);  // 12.745
  s21_null_decimal(&expected);
  expected.bits[0] = 13;  // round(12.745) = 13
  int status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_round_3) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12;
  s21_set_sign(&expected, 1);  // round(-12.345) = -12
  int status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_round_4) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12745;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.745
  s21_null_decimal(&expected);
  expected.bits[0] = 13;
  s21_set_sign(&expected, 1);  // round(-12.745) = -13
  int status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_round_5_fn) {
  s21_decimal num;
  s21_null_decimal(&num);
  num.bits[0] = 0xFFFFFFFF;
  num.bits[1] = 0xFFFFFFFF;
  num.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&num, 1);
  ck_assert_int_eq(s21_round(num, &num), 0);
  ck_assert_int_eq(s21_get_scale(&num), 0);
}
END_TEST

START_TEST(test_truncate_1) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // truncate(12.345) = 12
  int status = s21_truncate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345
  s21_null_decimal(&expected);
  expected.bits[0] = 12;
  s21_set_sign(&expected, 1);  // truncate(-12.345) = -12
  int status = s21_truncate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_truncate_3) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 0);  // 12345
  s21_null_decimal(&expected);
  expected.bits[0] = 12345;  // truncate(12345) = 12345
  int status = s21_truncate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_truncate_4) {
  s21_decimal num, result, expected;
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 4);  // 1.2345
  s21_null_decimal(&expected);
  expected.bits[0] = 1;  // truncate(1.2345) = 1
  int status = s21_truncate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_truncate_5_fn) {
  s21_decimal num;
  s21_null_decimal(&num);
  num.bits[0] = 0xFFFFFFFF;
  num.bits[1] = 0xFFFFFFFF;
  num.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&num, 1);
  ck_assert_int_eq(s21_truncate(num, &num), 0);
  ck_assert_int_eq(s21_get_scale(&num), 0);
}
END_TEST

Suite *other_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Other Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_floor_1);
  tcase_add_test(tc_core, test_floor_2);
  tcase_add_test(tc_core, test_floor_3);
  tcase_add_test(tc_core, test_floor_4);
  tcase_add_test(tc_core, test_floor_5);
  tcase_add_test(tc_core, test_negate_1);
  tcase_add_test(tc_core, test_negate_2);
  tcase_add_test(tc_core, test_negate_3);
  tcase_add_test(tc_core, test_negate_4);
  tcase_add_test(tc_core, test_negate_5_fn);
  tcase_add_test(tc_core, test_round_1);
  tcase_add_test(tc_core, test_round_2);
  tcase_add_test(tc_core, test_round_3);
  tcase_add_test(tc_core, test_round_4);
  tcase_add_test(tc_core, test_round_5_fn);
  tcase_add_test(tc_core, test_truncate_1);
  tcase_add_test(tc_core, test_truncate_2);
  tcase_add_test(tc_core, test_truncate_3);
  tcase_add_test(tc_core, test_truncate_4);
  tcase_add_test(tc_core, test_truncate_5_fn);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed = 0;
  Suite *s;
  SRunner *sr;

  // Запуск арифметических тестов
  s = arithmetic_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Запуск тестов сравнения
  s = comparsion_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Запуск тестов конверсии
  s = conversion_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Запуск тестов other операций
  s = other_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}