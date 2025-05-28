#include "../s21_decimal.h"

int s21_add(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
  s21_null_decimal(result);

  s21_decimal a = *num1, b = *num2;
  s21_normalize(&a, &b);

  int scale = s21_get_scale(&a);
  int sign1 = s21_get_sign(&a);
  int sign2 = s21_get_sign(&b);
  int status = 0;

  if (sign1 == sign2) {
    status = s21_bit_add(&a, &b, result);
    s21_set_sign(result, sign1);
  } else {
    s21_set_sign(&a, 0);
    s21_set_sign(&b, 0);
    if (s21_is_less_or_equal(a, b)) {
      status = s21_bit_sub(&b, &a, result);
      s21_set_sign(result, sign2);
    } else {
      status = s21_bit_sub(&a, &b, result);
      s21_set_sign(result, sign1);
    }
  }
  s21_set_scale(result, scale);
  return status;
}
