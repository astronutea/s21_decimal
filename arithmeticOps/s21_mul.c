#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_null_decimal(result);
  s21_decimal temp1 = {{0, 0, 0, 0}};
  s21_decimal temp2 = {{0, 0, 0, 0}};
  s21_decimal shifted = {{0, 0, 0, 0}};

  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);
  int result_scale = scale1 + scale2;
  int flag = 0;
  int overflow = 0;
  if (result_scale > 28) {
    return 1;
  }
  int last_bit1 = s21_get_last_bit(value_1);
  int last_bit2 = s21_get_last_bit(value_2);
  if (last_bit1 + last_bit2 >= 96) {
    return 1;
  }

  for (int i = 0; i < 96 && !overflow; i++) {
    if (s21_get_bit(value_2, i)) {
      shifted = value_1;
      s21_bit_move_left(&shifted, i);
      if (!flag) {
        overflow = s21_bit_add(temp1, shifted, &temp2);
        flag = 1;
      } else {
        overflow = s21_bit_add(temp2, shifted, &temp1);
        flag = 0;
      }
    }
  }
  if (overflow) {
    return 1;
  }
  if (flag)
    *result = temp2;
  else
    *result = temp1;

  s21_set_scale(result, result_scale);
  s21_set_sign(result, (sign1 ^ sign2));

  return 0;
}
