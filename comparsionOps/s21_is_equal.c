#include "../s21_decimal.h"

// Helper function to check if decimal is zero
int s21_is_zero(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  s21_decimal v1 = value_1;
  s21_decimal v2 = value_2;

  // If both values are zero, they are equal regardless of scale
  if (s21_is_zero(v1) && s21_is_zero(v2)) return 1;

  // Different signs mean numbers are not equal (unless both are zero, handled
  // above)
  if (s21_get_sign(&v1) != s21_get_sign(&v2)) return 0;

  // Normalize scales
  int scale1 = s21_get_scale(&v1);
  int scale2 = s21_get_scale(&v2);

  if (scale1 > scale2) {
    while (scale1 > scale2) {
      s21_mul10(&v2);
      scale2++;
    }
  } else if (scale2 > scale1) {
    while (scale2 > scale1) {
      s21_mul10(&v1);
      scale1++;
    }
  }

  // Compare all bits
  for (int i = 0; i < 3; i++) {
    if (v1.bits[i] != v2.bits[i]) {
      result = 0;
      break;
    }
  }

  return result;
}
