#include "../s21_decimal.h"

int s21_set_bit(s21_decimal *num, int bit_index, int bit_value) {
    if (!num || bit_index < 0 || bit_index > 95) {
        return 0;
    }
    if (bit_value)
        num->bits[bit_index / 32] |= (1u << (bit_index % 32));
    else
        num->bits[bit_index / 32] &= ~(1u << (bit_index % 32));
    return 1;
}