#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_decimal temp = value;
  int scale = (value.bits[3] >> 16) & 0xFF;
  int sign = (value.bits[3] >> 31) & 1;

  if (scale == 0) {
    *result = value;
    return 0;
  }

  s21_truncate(value, &temp);

  if (sign && s21_is_not_equal(value, temp)) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_sub(temp, one, &temp);
  }

  *result = temp;
  return 0;
}
