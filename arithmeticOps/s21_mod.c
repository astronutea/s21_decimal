#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_null_decimal(result);
    s21_decimal div_result, mul_result;
    s21_decimal a = value_1, b = value_2;
    int sign = s21_get_sign(&value_1);
    s21_set_sign(&b, 0);
    s21_div(a, b, &div_result);
    s21_set_sign(&div_result, 0);
    s21_mul(div_result, b, result);
    s21_set_sign(&result, sign);
    return 0;
}
