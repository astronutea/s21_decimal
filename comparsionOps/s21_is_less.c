#include "s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
    int answer = 0;

    if (s21_is_equal(value1, value2)) {
        answer = 0;
    } else {
        if (value1.sign != value2.sign) {
            if (value1.sign > value2.sign) {
                answer = 1;
            } else {
                answer = 0;
            }
        } else {
            for (int i = 95; i >= 0 && answer == 0; --i) {
                if (value1.digits[i] < value2.digits[i]) {
                    if (value1.sign == 0) {
                        answer = 1;
                    } else {
                        answer = 0;
                    }
                } else if (value1.digits[i] > value2.digits[i]) {
                    if (value1.sign == 0) {
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
