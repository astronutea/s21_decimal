#include "../s21_decimal.h"

int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    s21_null_decimal(result);
    s21_decimal temp1 = {{0, 0, 0, 0}};
    s21_decimal temp2 = {{0, 0, 0, 0}};
    s21_decimal shifted = {{0, 0, 0, 0}};

    int sign1 = s21_get_sign(&num1);
    int sign2 = s21_get_sign(&num2);
    int scale1 = s21_get_scale(&num1);
    int scale2 = s21_get_scale(&num2);
    int result_scale = scale1 + scale2;
    int flag = 0;

    for (int i = 0; i < 96; i++) {
        if (s21_get_bit(&num2, i)) {
            shifted = num1;
            s21_bit_move_left(&shifted, i);
            if (!flag) {
                s21_add(&temp1, &shifted, &temp2);
                flag = 1;
            } else {
                s21_add(&temp2, &shifted, &temp1);
                flag = 0;
            }
        }
    }
    if (flag)
        *result = temp2;
    else
        *result = temp1;

    s21_set_scale(result, result_scale);
    s21_set_sign(result, (sign1 ^ sign2));

    return 0;
}

