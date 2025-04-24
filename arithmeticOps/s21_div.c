#include "../s21_decimal.h"

int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    s21_null_decimal(result);

    if (num2.bits[0] == 0 && num2.bits[1] == 0 && num2.bits[2] == 0) {
        return 3;
    }

    int status = 0;
    int sign = s21_get_sign(&num1) ^ s21_get_sign(&num2);
    int scale1 = s21_get_scale(&num1);
    int scale2 = s21_get_scale(&num2);

    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);

    int result_scale = scale1 - scale2;

    int added_scale = 0;
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal temp_num1 = num1;

    s21_decimal quotient = {0}, remainder = {0};

    while (added_scale + result_scale < 28) {
        s21_div_mod(temp_num1, num2, &quotient, &remainder);
        if (remainder.bits[0] == 0 && remainder.bits[1] == 0 && remainder.bits[2] == 0)
            break;

        if (s21_mul10(&temp_num1)) break;
        added_scale++;
    }

    result_scale += added_scale;

    s21_div_mod(temp_num1, num2, &quotient, &remainder);

    if (quotient.bits[2] >= 0xFFFFFFFF) {
        status = 1;
    } else {
        *result = quotient;
        s21_set_scale(result, result_scale);
        s21_set_sign(result, sign);
    }

    return status;
}
