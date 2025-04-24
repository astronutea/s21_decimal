#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
    int result = 1;

    if (value1.sign != value2.sign) return 0;
    if (value1.exponent != value2.exponent) return 0;

    int digits_count = value1.exponent + 1;
    if (digits_count > 96) digits_count = 96;

    for (int i = digits_count - 1; i >= 0; i--) {
        if (value1.digits[i] != value2.digits[i]) {
            result = 0;
            break;
        }
    }

    return result;
}
