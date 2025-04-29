#include "../s21_decimal.h"

int is_half_or_more(s21_decimal *frac) {
  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);
  return s21_is_greater_or_equal(*frac, half);
}

int is_exact_half(s21_decimal *frac) {
  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);
  return s21_is_equal(*frac, half);
}

int s21_bank_round(s21_decimal *num1, s21_decimal *num2, s21_decimal *result,
                   int scale) {
  if (!num1 || !result) return 1;

  s21_decimal sum = {0};
  int sign = s21_get_sign(num1);
  s21_set_sign(num1, 0);

  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long temp = (unsigned long long)num1->bits[i] +
                              (num2 ? (unsigned long long)num2->bits[i] : 0) +
                              carry;
    sum.bits[i] = (unsigned int)temp;
    carry = temp >> 32;
  }

  if (carry) {
    if (scale == 0) return 1;

    s21_decimal quotient = {0};
    s21_decimal remainder = {0};

    s21_decimal ten = {{10, 0, 0, 0}};
    s21_div_mod(sum, ten, &quotient, &remainder);

    if (is_half_or_more(&remainder)) {
      if (is_exact_half(&remainder)) {
        if (quotient.bits[0] & 1) {
          s21_decimal one = {{1, 0, 0, 0}};
          s21_add(&quotient, &one, &quotient);
        }
      } else {
        s21_decimal one = {{1, 0, 0, 0}};
        s21_add(&quotient, &one, &quotient);
      }
    }

    *result = quotient;
    s21_set_scale(result, scale - 1);
    s21_set_sign(result, sign);
    return 0;
  }

  *result = sum;
  s21_set_scale(result, scale);
  s21_set_sign(result, sign);
  return 0;
}
