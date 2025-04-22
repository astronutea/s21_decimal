#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    if (result == NULL) {
        return 1;  
    }

    s21_decimal temp = value;
    int scale = (value.bits[3] >> 16) & 0xFF;  

    
    if (scale == 0) {
        *result = value;
        return 0;
    }

    
    int sign = (value.bits[3] >> 31) & 1;
    temp.bits[3] = 0;  

    
    for (int i = 0; i < scale; i++) {
        s21_div(temp, (s21_decimal){{10, 0, 0, 0}}, &temp);
    }

    
    temp.bits[3] |= (sign << 31);
    *result = temp;

    return 0;
}
