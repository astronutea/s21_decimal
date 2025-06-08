#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return ERROR_CONVERT;

  int sign = s21_get_sign(src);
  int scale = s21_get_scale(src);

  long double result = 0;

  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i)) {
      result += pow(2, i);
    }
  }
  for (int i = 0; i < scale; i++) {
    result /= 10.0;
  }
  if (sign) {
    *dst = -result;
  } else {
    *dst = result;
  }

  return OK;
}