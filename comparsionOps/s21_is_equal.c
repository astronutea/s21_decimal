#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;

  if (s21_is_zero(value_1) && s21_is_zero(value_2)) {
    result = 1;
  } else if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    result = 0;
  }

  s21_normalize(&value_1, &value_2);

  for (int i = 0; i < 96 && result; i++) {
    if (s21_get_bit(value_1, i) != s21_get_bit(value_2, i)) {
      result = 0;
      break;
    }
  }

  return result;
}