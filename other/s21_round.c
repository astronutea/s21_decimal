// round(12.345) = 12  #1

// round(12.745) = 13  #2
#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    if (result == NULL) {
        return 1;
    }

    int scale = s21_get_scale(&value);
    int sign = s21_get_sign(&value);

    if (scale == 0) {
        *result = value;
        return 0;
    }

    s21_decimal trunc = {0};
    s21_truncate(value, &trunc);

    s21_decimal frac = {0};
    s21_sub(&value, &trunc, &frac);
    s21_decimal half = {{5, 0, 0, 0}};
    s21_set_scale(&half, 1);

    if (sign) {
        *result = trunc;
        return 0;
    }

    if (s21_is_greater_or_equal(frac, half)) {
        trunc.bits[0] += 1;
    }

    *result = trunc;
    return 0;
}
