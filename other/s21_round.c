#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
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
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  // Получаем целую часть и последнюю цифру
  s21_decimal last_digit = temp;
  for (int i = 0; i < scale - 1; i++) {
    s21_div(last_digit, ten, &last_digit);
  }
  s21_mod(last_digit, ten, &last_digit);

  // Делим на 10^scale
  for (int i = 0; i < scale; i++) {
    s21_div(temp, ten, &temp);
  }

  // Если последняя цифра >= 5, округляем вверх
  if (s21_is_greater_or_equal(last_digit, five)) {
    if (sign) {
      s21_sub(&temp, &one, &temp);
    } else {
      s21_add(&temp, &one, &temp);
    }
  }

  // Восстанавливаем знак
  s21_set_sign(&temp, sign);
  *result = temp;

  return 0;
}
