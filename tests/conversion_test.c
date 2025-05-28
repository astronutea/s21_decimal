#include <check.h>

#include "../s21_decimal.h"

// Тесты для s21_from_decimal_to_float
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

int main(void) {
  int number_failed = 0;
  Suite *s;
  SRunner *sr;

  s = conversion_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}