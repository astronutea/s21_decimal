#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int answer = 0;

  if (s21_is_equal(value_1, value_2)) {
    answer = 0;
  } else {
    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);
    if (sign1 != sign2) {
      if (sign1 > sign2) {
        answer = 1;
      } else {
        answer = 0;
      }
    } else {
      for (int i = 95; i >= 0 && answer == 0; --i) {
        if (value_1.bits[i] < value_2.bits[i]) {
          if (sign1 == 0) {
            answer = 1;
          } else {
            answer = 0;
          }
        } else if (value_1.bits[i] > value_2.bits[i]) {
          if (sign1 == 0) {
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
