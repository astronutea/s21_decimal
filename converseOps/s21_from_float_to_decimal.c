#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) return ERROR_CONVERT;
  int f = OK;

  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }

  if (isnan(src) || isinf(src)) {
    return ERROR_CONVERT;
  }

  float abs_src = fabsf(src);

  if (abs_src >= 1e+28f || (abs_src > 0 && abs_src < 1e-28f)) {
    return ERROR_CONVERT;
  }

  if (f == OK) {
    int sign = (src < 0) ? 1 : 0;

    char buffer[50] = {0};
    sprintf(buffer, "%.7g", abs_src);

    char *exp_ptr = strchr(buffer, 'e');
    int exp_value = 0;
    char base_str[50] = {0};
    if (exp_ptr != NULL) {
      *exp_ptr = '\0';
      strcpy(base_str, buffer);
      exp_value = atoi(exp_ptr + 1);
    } else {
      strcpy(base_str, buffer);
    }

    int len = (int)strlen(base_str);
    char digits[50] = {0};
    int d_index = 0;
    int decimal_pos = -1;
    for (int i = 0; i < len; i++) {
      if (base_str[i] == '.') {
        decimal_pos = i;
      } else {
        digits[d_index++] = base_str[i];
      }
    }
    digits[d_index] = '\0';
    int num_digits = d_index;
    int num_after_decimal = 0;
    if (decimal_pos >= 0) {
      num_after_decimal = len - decimal_pos - 1;
    }

    int power_adjust = exp_value - num_after_decimal;
    int scale = 0;

    s21_big_decimal integer_value = {0};
    for (int i = 0; i < num_digits; i++) {
      // Умножаем на 10
      for (int j = 6; j >= 0; j--) {
        unsigned long long temp =
            (unsigned long long)integer_value.bits[j] * 10;
        if (j < 6) {
          temp += (unsigned long long)integer_value.bits[j + 1] >> 32;
        }
        integer_value.bits[j] = (int)temp;
      }
      // Добавляем новую цифру
      integer_value.bits[0] += (digits[i] - '0');
    }

    if (power_adjust < 0) {
      scale = -power_adjust;
      if (scale > 28) {
        scale = 28;
      }
    } else {
      for (int i = 0; i < power_adjust; i++) {
        // Умножаем на 10
        for (int j = 6; j >= 0; j--) {
          unsigned long long temp =
              (unsigned long long)integer_value.bits[j] * 10;
          if (j < 6) {
            temp += (unsigned long long)integer_value.bits[j + 1] >> 32;
          }
          integer_value.bits[j] = (int)temp;
        }
      }
      scale = 0;
    }

    // Копируем первые 3 слова из big_decimal в decimal
    for (int i = 0; i < 3; i++) {
      dst->bits[i] = integer_value.bits[i];
    }

    s21_set_scale(dst, scale);
    s21_set_sign(dst, sign);
  }
  return f;
}