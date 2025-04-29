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

  // Округляем до ближайшего целого
  s21_truncate(temp, &temp);

  // Проверяем, нужно ли округлять вверх
  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);  // 0.5

  if (sign) {
    s21_set_sign(&half, 1);
  }

  s21_decimal remainder;
  s21_div_mod(value, temp, NULL, &remainder);

  if (s21_is_greater_or_equal(remainder, half)) {
    s21_decimal one = {{1, 0, 0, 0}};
    if (sign) {
      s21_sub(&temp, &one, &temp);
    } else {
      s21_add(&temp, &one, &temp);
    }
  }

  *result = temp;
  return 0;
}
