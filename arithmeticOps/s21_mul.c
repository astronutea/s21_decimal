#include "../s21_decimal.h"

int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  s21_null_decimal(result);
  int status = 0;

  int sign1 = s21_get_sign(&num1);
  int sign2 = s21_get_sign(&num2);
  int scale1 = s21_get_scale(&num1);
  int scale2 = s21_get_scale(&num2);
  int result_scale = scale1 + scale2;

  s21_set_sign(result, sign1 ^ sign2);

  unsigned long long temp[6] = {0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      unsigned long long a = (unsigned int)num1.bits[i];
      unsigned long long b = (unsigned int)num2.bits[j];
      unsigned long long mul = a * b;

      int k = i + j;
      while (mul != 0 && k < 6) {
        mul += temp[k];
        temp[k] = mul & 0xFFFFFFFF;
        mul >>= 32;
        k++;
      }
    }
  }

  while ((temp[3] || temp[4] || temp[5]) && result_scale > 0) {
    unsigned long long carry = 0;
    for (int i = 5; i >= 0; i--) {
      unsigned long long part = (carry << 32) | temp[i];
      temp[i] = (unsigned int)(part / 10);
      carry = part % 10;
    }

    if (carry > 5 || (carry == 5 && (temp[0] & 1))) {
      temp[0]++;
      for (int i = 0; i < 5; i++) {
        if (temp[i] < 0x100000000ULL) break;
        temp[i] = 0;
        temp[i + 1]++;
      }
    }

    result_scale--;
  }

  if (temp[3] || temp[4] || temp[5]) {
    return 1;
  }

  for (int i = 0; i < 3; i++) {
    result->bits[i] = (int)temp[i];
  }

  s21_set_scale(result, result_scale);
  return status;
}
