#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (!dst) return ERROR_CONVERT;
    int f = OK;

    int scale = s21_get_scale(&src);
    if (scale >= 27) {
        if (src.bits[0] == 1 && scale == 28) {
            *dst = 0;
            return OK;
        }
        return ERROR_CONVERT;
    }

    float temp = 0;
    if (s21_from_decimal_to_float(src, &temp) != OK) {
        f = ERROR_CONVERT;
    }

    if (temp > INT_MAX || temp < INT_MIN) {
        f = ERROR_CONVERT;
    }

    *dst = (int)temp;
    return f;
}