#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_decimal temp = value;
  s21_decimal one = {{1, 0, 0, 0}};
  int scale = s21_get_scale(&temp);
  int sign = s21_get_sign(&temp);

  if (scale == 0) {
    *result = value;
    return 0;
  }

  // Сначала округляем вниз (отбрасываем дробную часть)
  s21_truncate(temp, &temp);

  // Для отрицательных чисел всегда вычитаем 1, если была дробная часть
  if (sign) {
    // Проверяем, была ли дробная часть
    s21_decimal check = temp;
    s21_set_scale(&check, scale);

    // Если после truncate значение не равно оригинальному,
    // значит была дробная часть
    if (!s21_is_equal(check, value)) {
      s21_sub(&temp, &one, &temp);
    }
  }

  *result = temp;
  return 0;
}
