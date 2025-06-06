#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) {
    return 3;
  } else {
    s21_null_decimal(result);
    s21_decimal div_result, mul_result;
    s21_decimal a = value_1, b = value_2;
    int sign = s21_get_sign(&value_1);
    s21_set_sign(&b, 0);
    s21_div(a, b, &div_result);
    s21_set_sign(&div_result, 0);
    s21_mul(div_result, b, &mul_result);
    s21_sub(a, mul_result, result);
    s21_set_sign(result, sign);
    return 0;
  }
}
