#include <stdint.h>

#include "../s21_decimal.h"

int s21_add(s21_decimal *num1, s21_decimal *num2, s21_decimal *result) {
  if (!num1 || !num2 || !result) return 1;

  s21_null_decimal(result);
  int sign1 = s21_get_sign(num1);
  int sign2 = s21_get_sign(num2);
  int scale1 = s21_get_scale(num1);
  int scale2 = s21_get_scale(num2);

  // If signs are different, use subtraction
  if (sign1 != sign2) {
    s21_decimal temp = *num2;
    s21_set_sign(&temp, !sign2);
    int status = s21_sub(num1, &temp, result);
    if (status == 0) {
      // Determine the correct sign based on comparison
      s21_decimal abs_num1 = *num1;
      s21_decimal abs_temp = temp;
      s21_set_sign(&abs_num1, 0);
      s21_set_sign(&abs_temp, 0);
      if (s21_is_less(abs_num1, abs_temp)) {
        s21_set_sign(result, !sign1);
      } else {
        s21_set_sign(result, sign1);
      }
    }
    return status;
  }

  // Align scales
  while (scale1 > scale2) {
    s21_mul10(num2);
    scale2++;
  }
  while (scale2 > scale1) {
    s21_mul10(num1);
    scale1++;
  }

  // Add numbers
  uint64_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t sum = (uint64_t)(uint32_t)num1->bits[i] +
                   (uint64_t)(uint32_t)num2->bits[i] + carry;
    result->bits[i] = (uint32_t)sum;
    carry = sum >> 32;
  }

  // Check for overflow
  if (carry) {
    if (scale1 > 0) {
      // If there's a fractional part, round
      s21_decimal temp = *result;
      s21_bank_round(&temp, NULL, result, scale1);
      scale1--;
    } else {
      // Store carry in next bit
      if (carry <= 0xFFFFFFFF) {
        result->bits[1] = (uint32_t)carry;
        carry = 0;
      } else {
        return 1;  // Overflow
      }
    }
  }

  // Set result sign and scale
  s21_set_sign(result, sign1);
  s21_set_scale(result, scale1);

  return 0;
}
