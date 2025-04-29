#include <stdint.h>

#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  // Проверяем знаки
  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);

  if (sign1 != sign2) {
    return sign1 ==
           1;  // Если первое число отрицательное, а второе положительное
  }

  // Нормализуем числа
  s21_normalize(&value_1, &value_2);

  // Сравниваем биты
  for (int i = 2; i >= 0; i--) {
    uint32_t v1 = (uint32_t)value_1.bits[i];
    uint32_t v2 = (uint32_t)value_2.bits[i];
    if (v1 < v2) {
      return sign1 == 0;
    } else if (v1 > v2) {
      return sign1 == 1;
    }
  }

  return 0;  // Числа равны
}
