CC = gcc
CFLAGS = -Wall -Werror -Wextra -I.
TEST_FLAGS = -lcheck -lm -lpthread

# Исходные файлы для разных операций
ARITHMETIC_SRC = arithmeticOps/s21_add.c arithmeticOps/s21_sub.c arithmeticOps/s21_mul.c arithmeticOps/s21_div.c arithmeticOps/s21_mod.c arithmeticOps/support_func.c arithmeticOps/s21_bank_round.c
OTHER_SRC = other/s21_floor.c other/s21_negate.c other/s21_round.c other/s21_truncate.c
COMPARSION_SRC = comparsionOps/s21_is_equal.c comparsionOps/s21_is_greater.c comparsionOps/s21_is_greater_or_equal.c comparsionOps/s21_is_less.c comparsionOps/s21_is_less_or_equal.c comparsionOps/s21_is_not_equal.c
BIT_SRC = bitOps/s21_get_bit.c bitOps/s21_get_scale.c bitOps/s21_get_sign.c bitOps/s21_null_decimal.c bitOps/s21_set_scale.c bitOps/s21_set_sign.c

# Тестовые файлы
ARITHMETIC_TEST = tests/arithmetic_test.c
OTHER_TEST = tests/other_test.c
COMPARSION_TEST = tests/comparsion_test.c
ALL_TESTS = tests/test.c

# Общие исходные файлы
COMMON_SRC = $(ARITHMETIC_SRC) $(OTHER_SRC) $(COMPARSION_SRC) $(BIT_SRC)

all: test_all

# Компиляция библиотек
arithmetic.a: $(ARITHMETIC_SRC) $(BIT_SRC) $(COMPARSION_SRC)
	$(CC) $(CFLAGS) -c $(ARITHMETIC_SRC) $(BIT_SRC) $(COMPARSION_SRC)
	ar rcs arithmetic.a *.o
	rm -f *.o

other.a: $(OTHER_SRC) $(ARITHMETIC_SRC) $(COMPARSION_SRC) $(BIT_SRC)
	$(CC) $(CFLAGS) -c $(OTHER_SRC) $(ARITHMETIC_SRC) $(COMPARSION_SRC) $(BIT_SRC)
	ar rcs other.a *.o
	rm -f *.o

comparsion.a: $(COMPARSION_SRC) $(BIT_SRC)
	$(CC) $(CFLAGS) -c $(COMPARSION_SRC) $(BIT_SRC)
	ar rcs comparsion.a *.o
	rm -f *.o

all.a: $(COMMON_SRC)
	$(CC) $(CFLAGS) -c $(COMMON_SRC)
	ar rcs all.a *.o
	rm -f *.o

# Компиляция и запуск тестов
test_arithmetic: arithmetic.a
	$(CC) $(CFLAGS) $(ARITHMETIC_TEST) arithmetic.a -o test_arithmetic $(TEST_FLAGS)
	./test_arithmetic || true
	rm -f *.o *.a test_arithmetic

test_other: other.a
	$(CC) $(CFLAGS) $(OTHER_TEST) other.a -o test_other $(TEST_FLAGS)
	./test_other || true
	rm -f *.o *.a test_other

test_comparsion: comparsion.a
	$(CC) $(CFLAGS) $(COMPARSION_TEST) comparsion.a -o test_comparsion $(TEST_FLAGS)
	./test_comparsion || true
	rm -f *.o *.a test_comparsion

test_all: all.a
	$(CC) $(CFLAGS) $(ALL_TESTS) all.a -o test_all $(TEST_FLAGS)
	./test_all || true
	rm -f *.o *.a test_all

clean:
	rm -f *.o *.a test_arithmetic test_other test_comparsion test_all

.PHONY: all test_arithmetic test_other test_comparsion test_all clean
