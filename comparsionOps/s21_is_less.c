#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int answer = 0;

    if (s21_is_equal(value_1, value_2)) {
        answer = 0;
    } else {
        if (value_1.sign != value_2.sign) {
            if (value_1.sign > value_2.sign) {
                answer = 1;
            } else {
                answer = 0;
            }
        } else {
            for (int i = 95; i >= 0 && answer == 0; --i) {
                if (value_1.digits[i] < value_2.digits[i]) {
                    if (value_1.sign == 0) {
                        answer = 1;
                    } else {
                        answer = 0;
                    }
                } else if (value_1.digits[i] > value_2.digits[i]) {
                    if (value_1.sign == 0) {
                        answer = 0;
                    } else {
                        answer = 1;
                    }
                }
            }
        }
    }

    return answer;
}
