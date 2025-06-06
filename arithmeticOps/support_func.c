#include "../s21_decimal.h"

int s21_mul10(s21_decimal *num) {
  unsigned long long carry = 0;
  int status = 0;

  for (int i = 0; i < 3; i++) {
    unsigned long long temp = (unsigned long long)num->bits[i] * 10 + carry;
    num->bits[i] = (int)temp;
    carry = temp >> 32;
  }

  if (carry) status = 1;
  return status;
}

int s21_normalize(s21_decimal *num1, s21_decimal *num2) {
  int scale1 = s21_get_scale(num1);
  int scale2 = s21_get_scale(num2);
  int result = 0;

  while (scale1 < scale2 && scale1 < 28) {
    if (s21_mul10(num1)) { result = 1; break; }
    scale1++;
  }

  while (scale1 > scale2 && scale2 < 28) {
    if (s21_mul10(num2)) { result = 1; break; }
    scale2++;
  }

  s21_set_scale(num1, scale1);
  s21_set_scale(num2, scale2);
  return result;
}

int s21_div_mod(s21_decimal dividend, s21_decimal divisor,
                s21_decimal *quotient, s21_decimal *remainder) {
  s21_null_decimal(quotient);
  s21_null_decimal(remainder);

  if (divisor.bits[0] == 0 && divisor.bits[1] == 0 && divisor.bits[2] == 0) {
    return 3;
  }

  s21_decimal temp_dividend = dividend;
  s21_decimal temp_divisor = divisor;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal temp = {0};

  int sign = s21_get_sign(&dividend) ^ s21_get_sign(&divisor);
  int scale = s21_get_scale(&dividend) - s21_get_scale(&divisor);

  s21_set_sign(&temp_dividend, 0);
  s21_set_sign(&temp_divisor, 0);

  while (s21_is_greater_or_equal(temp_dividend, temp_divisor)) {
    s21_sub(&temp_dividend, &temp_divisor, &temp);
    temp_dividend = temp;
    s21_add(quotient, &one, quotient);
  }

  *remainder = temp_dividend;

  s21_set_scale(quotient, scale >= 0 ? scale : 0);
  s21_set_scale(remainder, scale >= 0 ? scale : 0);
  s21_set_sign(quotient, sign);
  s21_set_sign(remainder, s21_get_sign(&dividend));

  return 0;
}

int s21_is_zero(s21_decimal value) {
  int status = 0;

  if ((value.bits[0] || value.bits[1] || value.bits[2]) == 0) status = 1;

  return status;
}

int s21_bit_add(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *res) {
  int carry = 0;
  int sign = s21_get_sign(value_1);
  int status = 0;

  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(value_1, i);
    int bit2 = s21_get_bit(value_2, i);
    int sum  = bit1 + bit2 + carry;
    s21_set_bit(res, i, sum & 1);
    carry = sum >> 1;
  }

  if (carry) {
    status = 1 + sign;
  }
  return status;
}

int s21_bit_sub(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *res) {
  int borrow = 0;

  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(value_1, i);
    int bit2 = s21_get_bit(value_2, i);

    int sub = bit1 - bit2 + borrow;
    if (sub >= 0) {
      s21_set_bit(res, i, sub);
      borrow = 0;
    } else {
      s21_set_bit(res, i, sub + 2);
      borrow = -1;
    }
  }

  return 0;
}

void s21_bit_move_left(s21_decimal *num, int k) {
  for (int i = 95; i >= k; i--) {
    s21_set_bit(num, i, s21_get_bit(num, i - k));
  }
  for (int i = k - 1; i >= 0; i--)
    s21_set_bit(num, i, 0);
}

int s21_get_last_bit(s21_decimal num) {
  int bitLast = 95;
  for (; (bitLast >= 0) && (!s21_get_bit(&num, bitLast));)
    bitLast -= 1;
  return bitLast;
}

void print_dec(s21_decimal num) {
  for (int i = 0; i < 128; i++) {
    int bit1 = s21_get_bit(&num, i);
    printf("%d", bit1);
    if (i % 32 == 31)
      printf(".");
  }
  printf("\n");
}