#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
  int res = 0;
  int sign = 0;
  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);
  if (sign1 != sign2) sign = 1;
  s21_set_sign(&value_1, 0);
  s21_set_sign(&value_2, 0);
  if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) {
    res = 3;
  } else {
    s21_decimal tmp = {0};
    int scale1 = s21_get_scale(&value_1);
    int scale2 = s21_get_scale(&value_2);
    s21_set_scale(&value_1, 0);
    s21_set_scale(&value_2, 0);
    res = s21_support_div(value_1, value_2, result, &tmp);
    int result_scale = scale1 - scale2;
    if (result_scale < 0) result_scale = 0;
    if (result_scale > 28) result_scale = 28;
    s21_set_scale(result, result_scale);
  }
  s21_set_sign(result, sign);
  return res;
}

int s21_support_div(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result, s21_decimal *tmp) {
  int res = 0;
  s21_null_decimal(result);
  s21_null_decimal(tmp);

  if (s21_is_less(value_1, value_2)) {
    return res;
  }

  if (s21_is_equal(value_1, value_2)) {
    result->bits[0] = 1;
    return res;
  }

  int dividend_bits = s21_get_last_bit(value_1);

  for (int i = dividend_bits; i >= 0; i--) {
    s21_bit_move_left(tmp, 1);

    if (s21_get_bit(&value_1, i)) {
      s21_set_bit(tmp, 0, 1);
    }

    s21_bit_move_left(result, 1);

    if (s21_is_greater_or_equal(*tmp, value_2)) {
      s21_decimal temp_remainder = {0};
      s21_sub(tmp, &value_2, &temp_remainder);
      *tmp = temp_remainder;

      s21_set_bit(result, 0, 1);
    }
  }

  return res;
}