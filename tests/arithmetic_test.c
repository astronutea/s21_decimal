#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../s21_decimal.h"

// Helper function to convert decimal to string for debugging
void decimal_to_string(s21_decimal decimal, char *str) {
    sprintf(str, "%d %d %d %d", decimal.bits[0], decimal.bits[1], decimal.bits[2], decimal.bits[3]);
}

// Test suite for addition
START_TEST(test_add_normal) {
    s21_decimal num1 = {{5, 0, 0, 0}};
    s21_decimal num2 = {{3, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{8, 0, 0, 0}};
    
    int status = s21_add(&num1, &num2, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[1], expected.bits[1]);
    ck_assert_int_eq(result.bits[2], expected.bits[2]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_add_overflow) {
    s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal num2 = {{1, 0, 0, 0}};
    s21_decimal result;
    
    int status = s21_add(&num1, &num2, &result);
    ck_assert_int_eq(status, 1); // Should return overflow error
}
END_TEST

START_TEST(test_add_negative) {
    s21_decimal num1 = {{5, 0, 0, 0x80000000}}; // -5
    s21_decimal num2 = {{3, 0, 0, 0}}; // 3
    s21_decimal result;
    s21_decimal expected = {{2, 0, 0, 0x80000000}}; // -2
    
    int status = s21_add(&num1, &num2, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// Test suite for subtraction
START_TEST(test_sub_normal) {
    s21_decimal num1 = {{5, 0, 0, 0}};
    s21_decimal num2 = {{3, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{2, 0, 0, 0}};
    
    int status = s21_sub(&num1, &num2, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_sub_negative_result) {
    s21_decimal num1 = {{3, 0, 0, 0}};
    s21_decimal num2 = {{5, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{2, 0, 0, 0x80000000}}; // -2
    
    int status = s21_sub(&num1, &num2, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// Test suite for multiplication
START_TEST(test_mul_normal) {
    s21_decimal num1 = {{5, 0, 0, 0}};
    s21_decimal num2 = {{3, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{15, 0, 0, 0}};
    
    int status = s21_mul(num1, num2, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_mul_overflow) {
    s21_decimal num1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal num2 = {{2, 0, 0, 0}};
    s21_decimal result;
    
    int status = s21_mul(num1, num2, &result);

    ck_assert_int_eq(status, 1); // Should return overflow error
}
END_TEST

// Test suite for division
START_TEST(test_div_normal) {
    s21_decimal num1 = {{63, 0, 0, 0}};
    s21_decimal num2 = {{3, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{21, 0, 0, 0}};
    
    int status = s21_div(num1, num2, &result);
    ck_assert_int_eq(status, 0);
    print_dec(num1);
    print_dec(num2);
    print_dec(result);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_div_by_zero) {
    s21_decimal num1 = {{15, 0, 0, 0}};
    s21_decimal num2 = {{0, 0, 0, 0}};
    s21_decimal result;
    
    int status = s21_div(num1, num2, &result);
    ck_assert_int_eq(status, 3); // Should return division by zero error
}
END_TEST

// Test suite for modulo
START_TEST(test_mod_normal) {
    s21_decimal num1 = {{17, 0, 0, 0}};
    s21_decimal num2 = {{5, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{2, 0, 0, 0}};
    
    int status = s21_mod(num1, num2, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_mod_by_zero) {
    s21_decimal num1 = {{17, 0, 0, 0}};
    s21_decimal num2 = {{0, 0, 0, 0}};
    s21_decimal result;
    
    int status = s21_mod(num1, num2, &result);
    ck_assert_int_eq(status, 3); // Should return division by zero error
}
END_TEST

// Test suite for bank rounding
START_TEST(test_bank_round_normal) {
    s21_decimal num1 = {{1234567, 0, 0, 0x00020000}}; // 12.34567
    s21_decimal num2 = {{0, 0, 0, 0}}; // Dummy value
    s21_decimal result;
    s21_decimal expected = {{1234567, 0, 0, 0x00020000}}; // Keep original value
    
    int status = s21_bank_round(&num1, &num2, &result, 2);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_bank_round_edge) {
    s21_decimal num1 = {{1234565, 0, 0, 0x00020000}}; // 12.34565
    s21_decimal num2 = {{0, 0, 0, 0}}; // Dummy value
    s21_decimal result;
    s21_decimal expected = {{1234565, 0, 0, 0x00020000}}; // Keep original value
    
    int status = s21_bank_round(&num1, &num2, &result, 2);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(result.bits[0], expected.bits[0]);
    ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

Suite *arithmetic_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Arithmetic Operations");
    tc_core = tcase_create("Core");

    // Add tests
    tcase_add_test(tc_core, test_add_normal);
    tcase_add_test(tc_core, test_add_overflow);
    tcase_add_test(tc_core, test_add_negative);
    tcase_add_test(tc_core, test_sub_normal);
    tcase_add_test(tc_core, test_sub_negative_result);
    tcase_add_test(tc_core, test_mul_normal);
    tcase_add_test(tc_core, test_mul_overflow);
    tcase_add_test(tc_core, test_div_normal);
    tcase_add_test(tc_core, test_div_by_zero);
    tcase_add_test(tc_core, test_mod_normal);
    tcase_add_test(tc_core, test_mod_by_zero);
    tcase_add_test(tc_core, test_bank_round_normal);
    tcase_add_test(tc_core, test_bank_round_edge);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = arithmetic_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
} 