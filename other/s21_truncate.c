#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int scale = s21_get_scale(&value);
  int sign = s21_get_sign(&value);

  if (scale == 0) {
    *result = value;
    return 0;
  }

  
  if (scale >= 27) {
    s21_null_decimal(result);
    s21_set_sign(result, sign);
    return 0;
  }

  s21_decimal temp = {{1, 0, 0, 0}}, ten = {{10, 0, 0, 0}};
  int overflow = 0;
  for (int i = 0; i < scale; i++) {
    if (s21_mul(temp, ten, &temp) != 0) {
      overflow = 1;
      break;
    }
  }
  if (overflow) {
    s21_null_decimal(result);
    s21_set_sign(result, sign);
    return 0;
  }

  s21_decimal abs_value = value;
  s21_set_scale(&abs_value, 0);
  s21_set_sign(&abs_value, 0);
  s21_div(abs_value, temp, result);
  s21_set_scale(result, 0);
  s21_set_sign(result, sign);
  return 0;
}
