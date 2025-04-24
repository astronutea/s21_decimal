#include "../s21_decimal.h"

void s21_set_sign(s21_decimal *num, int sign) {
    if (sign)
        num->bits[3] |= (1u << 31);
    else
        num->bits[3] &= ~(1u << 31);
}