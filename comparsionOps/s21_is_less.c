#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  if (s21_is_equal(value_1, value_2)) {
    return 0;
  }

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);

  if (sign1 != sign2) {
    return sign1 > sign2;
  }

  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);

  if (scale1 != scale2) {
    if (sign1 == 0) {
      result = scale1 > scale2;
    } else {
      result = scale1 < scale2;
    }
  } else {
    s21_big_decimal big_value_1, big_value_2;
    s21_decimal_to_big_decimal(value_1, &big_value_1);
    s21_decimal_to_big_decimal(value_2, &big_value_2);

    for (int i = 95; i >= 0 && !result; i--) {
      int bit1 = s21_get_big_decimal_bit(&big_value_1, i);
      int bit2 = s21_get_big_decimal_bit(&big_value_2, i);

      if (bit1 != bit2) {
        if (sign1 == 0) {
          result = bit1 < bit2;
        } else {
          result = bit1 > bit2;
        }
        break;
      }
    }
  }

  return result;
}
