#include <check.h>

#include "../s21_decimal.h"

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
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = other_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
