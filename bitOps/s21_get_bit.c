#include "../s21_decimal.h"

int s21_get_bit(s21_decimal *num, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;
  return (num->bits[num_int] & (1u << num_bit)) >> num_bit;
}