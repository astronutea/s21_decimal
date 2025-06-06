#include "../s21_decimal.h"

void s21_null_decimal(s21_decimal *num) {
  for (int i = 0; i < 4; i++) num->bits[i] = 0;
}