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

    if (scale >= 27) {
        s21_decimal half = {{5, 0, 0, 0}};
        s21_set_scale(&half, scale);
        s21_null_decimal(result);
        if (sign) {
            s21_decimal abs_value = value;
            s21_set_sign(&abs_value, 0);
            if (s21_is_greater(abs_value, half)) {
                result->bits[0] = 1;
                s21_set_sign(result, 1);
            } else {
                s21_set_sign(result, 1);
            }
        } else {

            if (s21_is_greater_or_equal(value, half)) {
                result->bits[0] = 1;
            }
            s21_set_sign(result, 0);
        }
        return 0;
    }

    s21_decimal trunc = {0};
    s21_truncate(value, &trunc);

    s21_decimal frac = {0};
    s21_sub(&value, &trunc, &frac);

    s21_decimal half = {{5, 0, 0, 0}};
    s21_set_scale(&half, 1);
    for (int i = 1; i < scale; i++) {
        s21_mul10(&half);
        s21_set_scale(&half, i + 1);
    }
    s21_set_scale(&half, scale);

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
