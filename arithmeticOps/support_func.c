#include "arithmetic.h"

int s21_get_sign(s21_decimal *num) {
    return (num->bits[3] >> 31) & 1;
}

void s21_set_sign(s21_decimal *num, int sign) {
    if (sign)
        num->bits[3] |= (1u << 31);
    else
        num->bits[3] &= ~(1u << 31);
}

int s21_get_scale(s21_decimal *num) {
    return (num->bits[3] >> 16) & 0xFF;
}

void s21_set_scale(s21_decimal *num, int scale) {
    num->bits[3] &= ~(0xFFu << 16);
    num->bits[3] |= (scale << 16);
}

int s21_mul10(s21_decimal *num) {
    unsigned long long carry = 0;
    int status = 0;
    if (num->bits[2] >= 0x19999999)
        status = 1;
    for (int i = 0; i < 3; i++) {
        unsigned long long temp = (unsigned long long)num->bits[i] * 10 + carry;
        num->bits[i] = (int)temp;
        carry = temp >> 32;
    }
    return status;
}

int s21_normalize(s21_decimal *num1, s21_decimal *num2) {
    int scale1 = s21_get_scale(num1);
    int scale2 = s21_get_scale(num2);
    int result = 0;

    while (scale1 < scale2) {
        if (!s21_mul10(num1))
            break;
        scale1++;
    }

    while (scale1 > scale2) {
        if (!s21_mul10(num2))
            break;
        scale2++;
    }

    s21_set_scale(num1, scale1);
    s21_set_scale(num2, scale2);
    return result;
}
