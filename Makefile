CC = gcc
CFLAGS = -Wall -Werror -Wextra -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS = -lcheck -lm
LIB = s21_decimal.a

ifeq (${OS}, Linux)
	TEST_FLAGS = -lcheck -lm
else ifeq (${OS}, Darwin)
	TEST_FLAGS = -lcheck -lm
else
	TEST_FLAGS = -lcheck
endif

ARITHMETIC_SRC = $(wildcard arithmeticOps/*.c)
OTHER_SRC = $(wildcard other/*.c)
COMPARSION_SRC = $(wildcard comparsionOps/*.c)
BIT_SRC = $(wildcard bitOps/*.c)
SUPPORT_SRC = support/support_func.c
CONVERSION_SRC = $(wildcard converseOps/*.c)

ALL_TESTS = tests/tests.c

COMMON_SRC = $(ARITHMETIC_SRC) $(OTHER_SRC) $(COMPARSION_SRC) $(BIT_SRC) $(SUPPORT_SRC) $(CONVERSION_SRC)

all: clean test $(LIB) gcov_report

$(LIB): $(COMMON_SRC)
	$(CC) $(CFLAGS) -c $(COMMON_SRC)
	ar rcs $(LIB) *.o
	rm -f *.o

test: $(LIB)
	$(CC) $(CFLAGS) $(ALL_TESTS) $(LIB) -o test $(TEST_FLAGS)
	./test || true

gcov_report:
	$(CC) $(CFLAGS) --coverage -c $(COMMON_SRC)
	ar rcs $(LIB) *.o
	rm *.o
	$(CC) $(CFLAGS) --coverage $(ALL_TESTS) $(LIB) -o test_gcov $(TEST_FLAGS)
	./test_gcov || true
	lcov -t "s21_decimal_test_report" -o s21_decimal.info -c -d .
	genhtml -o report s21_decimal.info
	open report/index.html
	rm -rf *.gcda *.gcno

style:
	clang-format -style=google $(COMMON_SRC) tests/tests.c s21_decimal.h -n
	clang-format -style=google $(COMMON_SRC) tests/tests.c s21_decimal.h -i

clean:
	rm -f *.o *.a *.gcno *.gcda *.info
	rm -f test
	rm -f test_gcov
	rm -rf report

.PHONY: all clean test gcov_report
