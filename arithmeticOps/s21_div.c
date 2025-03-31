#include "arithmetic.h"

int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    int status = 0;
    s21_null_decimal(result);
    
    if (num2.bits[0] == 0 && num2.bits[1] == 0 && num2.bits[2] == 0) {
        status = 3;
    } else {
        int sign1 = s21_get_sign(&num1);
        int sign2 = s21_get_sign(&num2);
        int scale1 = s21_get_scale(&num1);
        int scale2 = s21_get_scale(&num2);
        
        s21_set_sign(result, sign1 ^ sign2);
        
        s21_normalize(&num1, &num2);
        
        s21_decimal temp = {0};
        s21_decimal one = {{1, 0, 0, 0}};
        s21_decimal quotient = {0};
        
        while (1) {
            if (s21_sub(&num1, &num2, &temp) == 0) {
                s21_add(&quotient, &one, &quotient);
                num1 = temp;
            } else {
                break;
            }
        }
        
        for (int i = 0; i < 3; i++) {
            result->bits[i] = quotient.bits[i];
        }
        
        s21_set_scale(result, scale1 - scale2);
    }
    
    return status;
}
