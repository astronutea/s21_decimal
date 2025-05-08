#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (!dst) return ERROR_CONVERT;
    int f = OK;

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