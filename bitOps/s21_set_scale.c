#include "../s21_decimal.h"

void s21_set_scale(s21_decimal *num, int scale) {
    num->bits[3] &= ~(0xFFu << 16);
    num->bits[3] |= (scale << 16);
}