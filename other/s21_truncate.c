#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
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
  for (int i = 0; i < scale && (temp.bits[0] || temp.bits[1] || temp.bits[2]);
       i++) {
    s21_div(temp, ten, &temp);
  }

  // Восстанавливаем знак
  s21_set_sign(&temp, sign);
  *result = temp;

  return 0;
}
