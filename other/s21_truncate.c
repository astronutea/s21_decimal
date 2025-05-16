#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  s21_decimal temp = {{1, 0, 0, 0}}, ten = {{10, 0, 0, 0}};

  int scale = s21_get_scale(&value);
  if (scale == 0) {
    *result = value;
    return 0;
  }
  for (int i = 0; i < scale; i++) {
    s21_mul(temp, ten, &temp);
  }
  s21_set_scale(&value, 0);
  s21_div(value, temp, result);
  return 0;
}
