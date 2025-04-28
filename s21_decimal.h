#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdio.h>

typedef struct {
  int bits[4];
} s21_decimal;

int s21_get_scale(s21_decimal *num);
int s21_get_sign(s21_decimal *num);
void s21_set_scale(s21_decimal *num, int scale);
void s21_set_sign(s21_decimal *num, int sign);
void s21_null_decimal(s21_decimal *num);
int s21_get_bit(s21_decimal *num, int index);

int s21_mul10(s21_decimal *num);
int s21_normalize(s21_decimal *num1, s21_decimal *num2);
int s21_div_mod(s21_decimal dividend, s21_decimal divisor,
                s21_decimal *quotient, s21_decimal *remainder);

int s21_add(s21_decimal *num1, s21_decimal *num2, s21_decimal *result);
int is_half_or_more(s21_decimal *frac);
int is_exact_half(s21_decimal *frac);
int s21_bank_round(s21_decimal *num1, s21_decimal *num2, s21_decimal *result,
                   int scale);
int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result);

int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

#endif  // S21_DECIMAL_H