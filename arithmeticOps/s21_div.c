#include "../s21_decimal.h"

int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  s21_null_decimal(result);

  if (num2.bits[0] == 0 && num2.bits[1] == 0 && num2.bits[2] == 0) {
    return 3;
  }

  int status = 0;
  int sign = s21_get_sign(&num1) ^ s21_get_sign(&num2);
  int scale1 = s21_get_scale(&num1);
  int scale2 = s21_get_scale(&num2);

  s21_set_sign(&num1, 0);
  s21_set_sign(&num2, 0);

  int result_scale = scale1 - scale2;

  // Нормализуем числа
  if (s21_normalize(&num1, &num2)) {
    return 1;  // Ошибка переполнения при нормализации
  }

  s21_decimal quotient = {0}, remainder = {0};
  s21_div_mod(num1, num2, &quotient, &remainder);

  // Проверяем переполнение
  if ((unsigned int)quotient.bits[2] >= 0xFFFFFFFF) {
    status = 1;
  } else {
    *result = quotient;
    s21_set_scale(result, result_scale);
    s21_set_sign(result, sign);
  }

  return status;
}
