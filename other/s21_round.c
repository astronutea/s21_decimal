
// round(12.345) = 12  #1

// round(12.745) = 13  #2
#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    if (result == NULL) {
        return 1;
    }

    int scale = s21_get_scale(&value);  // 3
    int sign = s21_get_sign(&value);    // 0

    if (scale == 0) {
        *result = value;
        return 0;
    }
    float d_val;
    s21_from_decimal_to_float(value, &d_val);
    printf("%f", d_val);

    s21_decimal trunc = {0};  // 12
    s21_truncate(value, &trunc);

    float d_trun;
    s21_from_decimal_to_float(trunc, &d_trun);
    printf(" - %f = ", d_trun);

    s21_decimal frac = {0};  //.345
    s21_sub(&value, &trunc, &frac);

    float d_frac;
    s21_from_decimal_to_float(frac, &d_frac);
    printf("%f\n", d_frac);

    s21_decimal half = {{5, 0, 0, 0}};
    s21_set_scale(&half, 1);

    if (sign) {
        *result = trunc;
        return 0;
    }
    if (s21_is_greater_or_equal(frac, half)) {
        s21_decimal one = {{1, 0, 0, 0}};
        if (sign) {
            if (s21_sub(&trunc, &one, &trunc)) return 1;
        } else {
            if (s21_add(&trunc, &one, &trunc)) return 1;
        }
    }

    *result = trunc;
    return 0;
}
