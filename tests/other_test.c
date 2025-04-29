#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_floor) {
  s21_decimal num, result, expected;

  // Тест 1: положительное число
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // floor(12.345) = 12

  int status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);

  // Тест 2: отрицательное число
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 13;
  s21_set_sign(&expected, 1);  // floor(-12.345) = -13

  status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));

  // Тест 3: число без дробной части
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 0);  // 12345

  s21_null_decimal(&expected);
  expected.bits[0] = 12345;  // floor(12345) = 12345

  status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);

  // Тест 4: отрицательное число без дробной части
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 0);
  s21_set_sign(&num, 1);  // -12345

  s21_null_decimal(&expected);
  expected.bits[0] = 12345;
  s21_set_sign(&expected, 1);  // floor(-12345) = -12345

  status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));

  // Тест 5: число с большой дробной частью
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 4);  // 1.2345

  s21_null_decimal(&expected);
  expected.bits[0] = 1;  // floor(1.2345) = 1

  status = s21_floor(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_negate) {
  s21_decimal num, result, expected;

  // Тест 1: положительное число
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

  // Тест 2: отрицательное число
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 12345;
  s21_set_scale(&expected, 3);  // 12.345

  status = s21_negate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

START_TEST(test_round) {
  s21_decimal num, result, expected;

  // Тест 1: округление вверх
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // round(12.345) = 12

  int status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);

  // Тест 2: округление вниз
  s21_null_decimal(&num);
  num.bits[0] = 12340;
  s21_set_scale(&num, 3);  // 12.340

  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // round(12.340) = 12

  status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);

  // Тест 3: округление ровно до половины
  s21_null_decimal(&num);
  num.bits[0] = 12350;
  s21_set_scale(&num, 3);  // 12.350

  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // round(12.350) = 12

  status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);

  // Тест 4: отрицательное число с округлением вверх
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 12;
  s21_set_sign(&expected, 1);  // round(-12.345) = -12

  status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));

  // Тест 5: число с большой дробной частью
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 4);  // 1.2345

  s21_null_decimal(&expected);
  expected.bits[0] = 1;  // round(1.2345) = 1

  status = s21_round(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_truncate) {
  s21_decimal num, result, expected;

  // Тест 1: положительное число
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);  // 12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 12;  // truncate(12.345) = 12

  int status = s21_truncate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);

  // Тест 2: отрицательное число
  s21_null_decimal(&num);
  num.bits[0] = 12345;
  s21_set_scale(&num, 3);
  s21_set_sign(&num, 1);  // -12.345

  s21_null_decimal(&expected);
  expected.bits[0] = 12;
  s21_set_sign(&expected, 1);  // truncate(-12.345) = -12

  status = s21_truncate(num, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(s21_get_sign(&result), s21_get_sign(&expected));
}
END_TEST

Suite *other_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Other Operations");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_floor);
  tcase_add_test(tc_core, test_negate);
  tcase_add_test(tc_core, test_round);
  tcase_add_test(tc_core, test_truncate);
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
