#include "../s21_decimal.h"

int s21_get_bit(s21_decimal *num, int index) {
  return (num->bits[index / 32] >> (31 - index % 32)) & 1;
}