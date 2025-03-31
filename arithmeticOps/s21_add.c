#include "arithmetic.h"

int s21_add(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
    int status = 0;
    s21_null_decimal(result);

    s21_normalize(num1, num2);

    int scale1 = s21_get_scale(num1);

    unsigned long long carry = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long long temp = (unsigned long long)num1->bits[i] + (unsigned long long)num2->bits[i] + carry;
        result->bits[i] = (int)temp;
        carry = temp >> 32;
    }

    s21_set_scale(result, scale1);
    return status;
}
