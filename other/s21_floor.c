#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_decimal temp = value;
  s21_decimal one = {{1, 0, 0, 0}};
  int scale = s21_get_scale(&temp);
  int sign = s21_get_sign(&temp);

  if (scale == 0) {
    *result = value;
    return 0;
  }

  if (sign) {
    s21_truncate(temp, &temp);
    if (scale > 0) {
      s21_sub(&temp, &one, &temp);
    }
  } else {
    s21_truncate(temp, &temp);
  }

  *result = temp;
  return 0;
}
