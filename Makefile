CC = gcc
CFLAGS = -Wall -Werror -Wextra -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS = -lcheck -lm -lpthread
LIB = s21_decimal.a

ARITHMETIC_SRC = $(wildcard arithmeticOps/*.c)
OTHER_SRC = $(wildcard other/*.c)
COMPARSION_SRC = $(wildcard comparsionOps/*.c)
BIT_SRC = $(wildcard bitOps/*.c)
SUPPORT_SRC = support/support_func.c
CONVERSION_SRC = $(wildcard converseOps/*.c)

ARITHMETIC_TEST = tests/arithmetic_test.c
OTHER_TEST = tests/other_test.c
COMPARSION_TEST = tests/comparsion_test.c
CONVERSION_TEST = tests/conversion_test.c
ALL_TESTS = tests/tests.c

COMMON_SRC = $(ARITHMETIC_SRC) $(OTHER_SRC) $(COMPARSION_SRC) $(BIT_SRC) $(SUPPORT_SRC) $(CONVERSION_SRC)

all: clean test $(LIB) gcov_report valgrind_test

$(LIB): $(COMMON_SRC)
	$(CC) $(CFLAGS) -c $(COMMON_SRC)
	ar rcs $(LIB) *.o
	rm -f *.o

valgrind_test: $(LIB)
	$(CC) $(CFLAGS) -g $(ALL_TESTS) $(LIB) -o test_valgrind $(TEST_FLAGS)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./test_valgrind

test_arithmetic: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(ARITHMETIC_TEST) $(LIB) -o test_arithmetic $(TEST_FLAGS)
	./test_arithmetic || true

test_other: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(OTHER_TEST) $(LIB) -o test_other $(TEST_FLAGS)
	./test_other || true

test_comparsion: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(COMPARSION_TEST) $(LIB) -o test_comparsion $(TEST_FLAGS)
	./test_comparsion || true

test_conversion: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(CONVERSION_TEST) $(LIB) -o test_conversion $(TEST_FLAGS)
	./test_conversion || true

test: $(LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(ALL_TESTS) $(LIB) -o test $(TEST_FLAGS)
	./test || true

gcov_report: test
	lcov --no-checksum --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info || true
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html

clean:
	rm -f *.o *.a *.gcno *.gcda *.info
	rm -f test_arithmetic test_other test_comparsion test_conversion test
	rm -f test_*_valgrind test_valgrind
	rm -rf gcov_report

.PHONY: all test_arithmetic test_other test_comparsion test_conversion test clean gcov_report valgrind_test
