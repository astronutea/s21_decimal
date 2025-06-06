#include "../s21_decimal.h"

int s21_sub(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
  s21_decimal a = *num1, b = *num2;
  s21_set_sign(&b, (s21_get_sign(num2) + 1) % 2);
  int status = s21_add(&a, &b, result);
  return status;
}
