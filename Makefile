CC = gcc
CFLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lcheck -lm -lpthread

SRC_DIR = .
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

all: s21_decimal.a test

s21_decimal.a: $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	ar rcs s21_decimal.a *.o
	rm -f *.o

test: s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_FILES) s21_decimal.a -o test $(TEST_FLAGS)
	./test

clean:
	rm -f *.o *.a test

.PHONY: all test clean
