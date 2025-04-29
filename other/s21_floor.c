#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_decimal temp = value;
  int scale = s21_get_scale(&temp);
  int sign = s21_get_sign(&temp);

  if (scale == 0) {
    *result = value;
    return 0;
  }

  // Убираем знак и масштаб для деления
  s21_set_sign(&temp, 0);
  s21_set_scale(&temp, 0);

  // Делим на 10^scale
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  // Получаем целую часть
  for (int i = 0; i < scale; i++) {
    s21_div(temp, ten, &temp);
  }

  // Для отрицательных чисел, если был остаток, добавляем 1
  if (sign) {
    s21_decimal check = temp;
    for (int i = 0; i < scale; i++) {
      s21_mul(check, ten, &check);
    }
    if (!s21_is_equal(check, value)) {
      s21_add(&temp, &one, &temp);
    }
  }

  // Восстанавливаем знак
  s21_set_sign(&temp, sign);
  *result = temp;

  return 0;
}
