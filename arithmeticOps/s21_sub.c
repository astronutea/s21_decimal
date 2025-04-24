#include "../s21_decimal.h"

int s21_sub(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
    s21_null_decimal(result);
    int status = 0;

    s21_normalize(num1, num2);
    int scale = s21_get_scale(num1);

    int sign1 = s21_get_sign(num1);
    int sign2 = s21_get_sign(num2);

    if (sign1 != sign2) {
        s21_decimal b_copy = *num2;
        s21_set_sign(&b_copy, sign1);
        status = s21_add(num1, &b_copy, result);
        s21_set_scale(result, scale);
        return status;
    }

    int cmp = s21_is_greater_or_equal(*num1, *num2);

    s21_decimal left = *num1;
    s21_decimal right = *num2;

    if (!cmp) {
        left = *num2;
        right = *num1;
    }

    unsigned long long borrow = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long long minuend = (unsigned long long)left.bits[i];
        unsigned long long subtrahend = (unsigned long long)right.bits[i] + borrow;

        if (minuend < subtrahend) {
            result->bits[i] = (int)(0x100000000 + minuend - subtrahend);
            borrow = 1;
        } else {
            result->bits[i] = (int)(minuend - subtrahend);
            borrow = 0;
        }
    }

    if (cmp) {
        s21_set_sign(result, sign1);
    } else {
        s21_set_sign(result, !sign1);
    }

    s21_set_scale(result, scale);
    return status;
}

