#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst == NULL) return 1;
    int f = OK;

    for (int i = 0; i < 4; i++) {
        dst->bits[i] = 0;
    }
    float abs_src = fabsf(src);

    if (abs_src > 7.922816e28f || (abs_src > 0 && abs_src < 1e-28f)) {
        f = ERROR_CONVERT;
    }
    if (f == OK) {
        int sign = (src < 0) ? 1 : 0;

        char buffer[50] = {0};
        sprintf(buffer, "%.7g", abs_src);

        char *exp_ptr = strchr(buffer, 'e');
        int exp_value = 0;
        char base_str[50] = {0};
        if (exp_ptr != NULL) {
            *exp_ptr = '\0';
            strcpy(base_str, buffer);
            exp_value = atoi(exp_ptr + 1);
        } else {
            strcpy(base_str, buffer);
        }

        int len = (int)strlen(base_str);
        char digits[50] = {0};
        int d_index = 0;
        int decimal_pos = -1;
        for (int i = 0; i < len; i++) {
            if (base_str[i] == '.') {
                decimal_pos = i;
            } else {
                digits[d_index++] = base_str[i];
            }
        }
        digits[d_index] = '\0';
        int num_digits = d_index;
        int num_after_decimal = 0;
        if (decimal_pos >= 0) {
            num_after_decimal = len - decimal_pos - 1;
        }

        int power_adjust = exp_value - num_after_decimal;
        int scale = 0;

        __int128 integer_value = 0;
        for (int i = 0; i < num_digits; i++) {
            integer_value = integer_value * 10 + (digits[i] - '0');
        }

        if (power_adjust < 0) {
            scale = -power_adjust;
            if (scale > 28) {
                scale = 28;
            }
        } else {
            for (int i = 0; i < power_adjust; i++) {
                integer_value *= 10;
            }
            scale = 0;
        }

        for (int bit = 0; bit < 96; bit++) {
            int bit_value = (integer_value >> bit) & 1;
            set_bit(dst, bit, bit_value);
        }

        set_scale(dst, scale);
        set_sign(dst, sign);
    }
    return f;
}