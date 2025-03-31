#include "arithmetic.h"

int s21_sub(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
    int status = 0;
    s21_null_decimal(result);

    s21_normalize(num1, num2);

    int scale1 = s21_get_scale(num1);

    int sign1 = s21_get_sign(num1);
    int sign2 = s21_get_sign(num2);

    if (sign1 == sign2) {
        s21_add(num1, num2, result);
    } else if (sign1 == 0) {
            s21_set_sign(num2, 1);
            s21_add(num1, num2, result);
            s21_set_sign(num2, sign2);
    }
    
    s21_set_scale(result, scale1);
    return status;
}
