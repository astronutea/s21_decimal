#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_null_decimal(result);
    int status = 0;

    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        return 3;
    }

    s21_decimal quotient = {0};
    s21_decimal int_part = {0};
    s21_decimal multiplied = {0};
    s21_decimal temp = {0};

    s21_div(value_1, value_2, &quotient);
    s21_truncate(quotient, &int_part);
    s21_mul(int_part, value_2, &multiplied);
    status = s21_sub(&value_1, &multiplied, &temp);

    if (status == 1) {
        s21_truncate(temp, result);
        status = 0;
    } else {
        *result = temp;
    }

    s21_set_sign(result, s21_get_sign(&value_1));
    return status;
}
