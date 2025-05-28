CC = gcc
CFLAGS = -Wall -Werror -Wextra -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS = -lcheck -lm -lpthread
LIB = s21_decimal.a

PATH := /Users/angellat/goinfre/.brew/bin:$(PATH)

ARITHMETIC_SRC = arithmeticOps/s21_add.c arithmeticOps/s21_sub.c arithmeticOps/s21_mul.c arithmeticOps/s21_div.c arithmeticOps/s21_mod.c arithmeticOps/support_func.c arithmeticOps/s21_bank_round.c
OTHER_SRC = other/s21_floor.c other/s21_negate.c other/s21_round.c other/s21_truncate.c
COMPARSION_SRC = comparsionOps/s21_is_equal.c comparsionOps/s21_is_greater.c comparsionOps/s21_is_greater_or_equal.c comparsionOps/s21_is_less.c comparsionOps/s21_is_less_or_equal.c comparsionOps/s21_is_not_equal.c
BIT_SRC = bitOps/s21_get_bit.c bitOps/s21_get_scale.c bitOps/s21_get_sign.c bitOps/s21_null_decimal.c bitOps/s21_set_scale.c bitOps/s21_set_sign.c bitOps/s21_set_bit.c
SUPPORT_SRC = arithmeticOps/support_func.c
CONVERSION_SRC = converseOps/s21_from_decimal_to_float.c converseOps/s21_from_decimal_to_int.c converseOps/s21_from_float_to_decimal.c converseOps/s21_from_int_to_decimal.c

ARITHMETIC_TEST = tests/arithmetic_test.c
OTHER_TEST = tests/other_test.c
COMPARSION_TEST = tests/comparsion_test.c
CONVERSION_TEST = tests/conversion_test.c
ALL_TESTS = tests/tests.c

COMMON_SRC = $(ARITHMETIC_SRC) $(OTHER_SRC) $(COMPARSION_SRC) $(BIT_SRC) $(SUPPORT_SRC) $(CONVERSION_SRC)

all: test_all

$(LIB): $(COMMON_SRC)
	$(CC) $(CFLAGS) -c $(COMMON_SRC)
	ar rcs $(LIB) *.o
	rm -f *.o

test_arithmetic: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(ARITHMETIC_TEST) $(LIB) -o test_arithmetic $(TEST_FLAGS)
	./test_arithmetic || true
	rm -f *.o *.a test_arithmetic

test_other: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(OTHER_TEST) $(LIB) -o test_other $(TEST_FLAGS)
	./test_other || true
	rm -f *.o *.a test_other

test_comparsion: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(COMPARSION_TEST) $(LIB) -o test_comparsion $(TEST_FLAGS)
	./test_comparsion || true
	rm -f *.o *.a test_comparsion

test_conversion: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(CONVERSION_TEST) $(LIB) -o test_conversion $(TEST_FLAGS)
	./test_conversion || true
	rm -f *.o *.a test_conversion

test_all: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(ALL_TESTS) $(LIB) -o test_all $(TEST_FLAGS)
	./test_all || true
	rm -f *.o *.a test_all

gcov_report: test_all
	lcov --no-checksum --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info || true
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html

clean:
	rm -f *.o *.a *.gcno *.gcda *.info
	rm -f test_arithmetic test_other test_comparsion test_conversion test_all
	rm -rf gcov_report

.PHONY: all test_arithmetic test_other test_comparsion test_conversion test_all clean gcov_report