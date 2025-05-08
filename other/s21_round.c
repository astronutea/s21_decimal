#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    if (result == NULL) {
        return 1;  
    }
 
    s21_decimal half = {{5, 0, 0, 0x10000}};  
    s21_decimal temp = value;
    int scale = (value.bits[3] >> 16) & 0xFF;  

    
    if (scale == 0) {
        *result = value;
        return 0;
    }

    
    int sign = (value.bits[3] >> 31) & 1;
    temp.bits[3] = 0;  

    
    s21_add(&temp, &half, &temp);

    
    for (int i = 0; i < scale; i++) {
        s21_div(temp, (s21_decimal){{10, 0, 0, 0}}, &temp);
    }

    
    temp.bits[3] |= (sign << 31);
    *result = temp;

    return 0;
}
