#include "../s21_decimal.h"

int s21_get_big_decimal_bit(s21_big_decimal *num, int index) {
    int array_index = index / 32;
    int bit_index = index % 32;
    return (num->bits[array_index] >> bit_index) & 1;
}