#include <check.h>

#include "../s21_decimal.h"

// Объявления тестовых сьютов
Suite *arithmetic_suite(void);
Suite *other_suite(void);
Suite *comparsion_suite(void);

int main(void) {
  int number_failed = 0;
  Suite *s;
  SRunner *sr;

  // Запуск арифметических тестов
  s = arithmetic_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Запуск тестов other операций
  s = other_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Запуск тестов сравнения
  s = comparsion_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}