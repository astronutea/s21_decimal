#include "arithmetic.h"

int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    int status = 0;
    s21_null_decimal(result);
    
    int sign1 = s21_get_sign(&num1);
    int sign2 = s21_get_sign(&num2);
    int scale1 = s21_get_scale(&num1);
    int scale2 = s21_get_scale(&num2);
    
    s21_set_sign(result, sign1 ^ sign2);
    
    int result_scale = scale1 + scale2;
    if (result_scale > 28) {
        status = 1;
    } else {
        unsigned long long temp[4] = {0};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                unsigned long long product = (unsigned long long)num1.bits[i] * (unsigned long long)num2.bits[j];
                int k = i + j;
                while (product && k < 4) {
                    unsigned long long sum = temp[k] + product;
                    temp[k] = sum & 0xFFFFFFFF;
                    product = sum >> 32;
                    k++;
                }
            }
        }
        
        if (temp[3] > 0) {
            status = 1;
        } else {
            for (int i = 0; i < 3; i++) {
                result->bits[i] = (int)temp[i];
            }
            s21_set_scale(result, result_scale);
        }
    }
    
    return status;
}
