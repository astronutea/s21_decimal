#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 1;

    if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) return 0;
    if (s21_get_scale(&value_1) != s21_get_scale(&value_2)) return 0;

    int digits_count = value_1.exponent + 1;
    if (digits_count > 96) digits_count = 96;

    for (int i = digits_count - 1; i >= 0; i--) {
        if (value_1.digits[i] != value_2.digits[i]) {
            result = 0;
            break;
        }
    }

    return result;
}
