#include "arithmetic.h"

int s21_add(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
    s21_null_decimal(result);
    int status = 0;

    s21_normalize(num1, num2);
    int scale = s21_get_scale(num1);
    int sign1 = s21_get_sign(num1);
    int sign2 = s21_get_sign(num2);

    // Обработка разных знаков
    if (sign1 != sign2) {
        s21_decimal num2_copy = *num2;
        s21_set_sign(&num2_copy, sign1);
        status = s21_sub(num1, &num2_copy, result);
        s21_set_scale(result, scale);
        return status;
    }

    unsigned long long carry = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long long sum = (unsigned long long)num1->bits[i] +
                                 (unsigned long long)num2->bits[i] + carry;
        result->bits[i] = (int)(sum & 0xFFFFFFFF);
        carry = sum >> 32;
    }

    if (carry != 0) {
        status = s21_bank_round(num1, num2, result, scale);
        if (status == 0) {
            s21_set_scale(result, scale);
            s21_set_sign(result, sign1);
        }
    } else {
        s21_set_scale(result, scale);
        s21_set_sign(result, sign1);
    }

    return status;
}
