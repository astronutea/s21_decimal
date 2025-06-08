#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 1;
  if (dst) {
    s21_decimal truncated_value;
    if (!s21_truncate(src, &truncated_value)) {
      if ((truncated_value.bits[2] != 0) || (truncated_value.bits[1] != 0)) {
        result = 1;
      } else {
        int value = truncated_value.bits[0];
        if (s21_get_sign(truncated_value)) {
          value = -value;
        }
        if ((value <= INT_MAX) && (value >= INT_MIN)) {
          *dst = value;
          result = 0;
        }
      }
    }
  }
  return result;
}