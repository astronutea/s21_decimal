#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal a = value_1, b = value_2;
  s21_set_sign(&b, (s21_get_sign(&value_2) + 1) % 2);
  int status = s21_add(a, b, result);
  return status;
}
