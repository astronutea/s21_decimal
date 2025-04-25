#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if (s21_is_equal(value_1, value_2)) {
        return 0;
    }

    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);

    if (sign1 != sign2) {
        result = sign1 > sign2;
    } else {
        s21_normalize(&value_1, &value_2);

        for (int i = 95; i >= 0 && !result; i--) {
            int bit1 = s21_get_bit(&value_1, i);
            int bit2 = s21_get_bit(&value_2, i);

            if (bit1 != bit2) {
                if (sign1) {
                    if (bit1 > bit2) {
                        result = 1;
                    } else {
                        result = 0;
                    }
                } else {
                    if (bit1 < bit2) {
                        result = 1;
                    } else {
                        result = 0;
                    }
                }
                break;
            }
        }
    }

    return result;
}
