#include "../s21_decimal.h"

int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  s21_null_decimal(result);

  if (num2.bits[0] == 0 && num2.bits[1] == 0 && num2.bits[2] == 0) {
    return 3;
  }
  if (num1.bits[0] == 0 && num1.bits[1] == 0 && num1.bits[2] == 0) {
    s21_null_decimal(result);
    return 0;
  }

  int status = 0;
  int sign = s21_get_sign(&num1) ^ s21_get_sign(&num2);
  int scale1 = s21_get_scale(&num1);
  int scale2 = s21_get_scale(&num2);

  s21_set_sign(&num1, 0);
  s21_set_sign(&num2, 0);

  int result_scale = scale1 - scale2;

  s21_decimal temp_num1 = num1;
  s21_decimal quotient = {0}, remainder = {0};
  int i = 95;
  while (!s21_get_bit(&temp_num1, i)) i--;
  quotient.bits[i] = 1;
  while (s21_is_greater(num2, quotient)) {
    s21_bit_move_left(&quotient, 1);
    s21_set_bit(&quotient, 0, s21_get_bit(&temp_num1, i - 1));
    i--;
  }
  s21_sub(&quotient, &num2, &remainder);
  quotient = remainder;
  while (i > 0) {
    s21_bit_move_left(&quotient, 1);
    s21_set_bit(&quotient, 0, s21_get_bit(&temp_num1, i));
    if (s21_is_greater_or_equal(quotient, num2)) {
      s21_sub(&quotient, &num2, &remainder);
      s21_bit_move_left(result, 1);
      s21_set_bit(result, 0, 1);
      quotient = remainder;
    } else {
      s21_bit_move_left(result, 1);
      s21_set_bit(result, 0, 0);
    }
    i--;
  }
  s21_set_sign(result, sign);
  s21_set_scale(result, result_scale);
  return status;
}
