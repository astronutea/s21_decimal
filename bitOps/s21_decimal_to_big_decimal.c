#include "../s21_decimal.h"

void s21_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
  for (int i = 4; i < 7; i++) {
    dst->bits[i] = 0;
  }
}
