#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  int scale = s21_get_scale(&value);
  int sign = s21_get_sign(&value);

  if (scale == 0) {
    *result = value;
    return 0;
  }

  s21_decimal trunc = {0};
  s21_truncate(value, &trunc);

  s21_decimal frac = {0};
  s21_sub(&value, &trunc, &frac);

  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);

  if (s21_is_greater_or_equal(frac, half)) {
    s21_decimal one = {{1, 0, 0, 0}};
    if (sign) {
      if (s21_sub(&trunc, &one, &trunc)) return 1;
    } else {
      if (s21_add(&trunc, &one, &trunc)) return 1;
    }
  }

  *result = trunc;
  return 0;
}
