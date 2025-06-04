#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (!dst) return ERROR_CONVERT;
    memset(dst, 0, sizeof(s21_decimal));

    if (src < 0) {
        s21_set_sign(dst, 1);
        long long abs_value = -(long long)src;
        dst->bits[0] = (int)abs_value;
    } else {
        dst->bits[0] = src;
    }

    return OK;
}