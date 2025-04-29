#include "../s21_decimal.h"

int s21_get_sign(s21_decimal *num) { return (num->bits[3] >> 31) & 1; }