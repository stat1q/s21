#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

#define EPS_TEST 1e-3

#define TEST_CASE_INTEGER                                                      \
  {                                                                            \
    0, 1, -1, 7, 64, 128, -128, 2147483647, -2147483647, 1073741823, 16777215, \
        -1073741824, -16777216, -16, 32, -64, 0xFFFFFFFF, 0x8FFFFFFF           \
  }
#define TEST_CASE_FLOAT                                                        \
  {                                                                            \
    0.0, -0.0, 1.1234, -1.1234, 0.187654321, -0.113452624, 1e-10, -1e-10,      \
        1e10, -1e10, 1e20, -1e20, 1.234534e-20, -1e-20, -3.0, 3.0, -4.034454,  \
        4.0345365, 1.0654634, -1.0345634562, 0.1, 0.8, 0.2, 70, 10, 10000, -1, \
        -10.247, 0.25, 0.000001, 7.9228162514264337593543950336, 2147483648.0, \
        -1.23456e-27, 1.23456e-27, 79228142643.0, 1.33333333333333333333333,   \
  }

//  79228162514264337593543950335.0

void print_test(char *name);

void print_result(int bad, int good);
void print_error(float a, float b, float f, float p, char *s);
int get_eq(float a, float b);
int get_not_eq(float a, float b);
int get_less(float a, float b);
int get_le_or_eq(float a, float b);
int get_greater(float a, float b);
int get_gr_or_eq(float a, float b);
double neagate(double d);
void all_test(double (*func)(double), s21_decimal (*func_dec)(s21_decimal),
              char *name);
void compare_all_test(int (*funk_res)(float, float),
                      int (*func)(s21_decimal, s21_decimal), char *name);

START_TEST(test_from_decimal_to_int) {
  print_test("#TEST1: int->decimal->int");
  int good = 0;
  int bad = 0;
  int arr[] = TEST_CASE_INTEGER;
  int n = sizeof(arr) / sizeof(int);
  for (int i = 0; i < n; i++) {
    s21_decimal tmp;
    s21_from_int_to_decimal(arr[i], &tmp);
    int p = 0;
    s21_from_decimal_to_int(tmp, &p);
    if (arr[i] == p) {
      good++;
    } else {
      bad++;
      printf("-");
    }
    ck_assert_int_eq(arr[i], p);
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_from_int_to_float) {
  print_test("#TEST2: int->decimal->float");
  int good = 0;
  int bad = 0;
  int arr[] = TEST_CASE_INTEGER;
  int n = sizeof(arr) / sizeof(int);
  for (int i = 0; i < n; i++) {
    s21_decimal tmp;
    s21_from_int_to_decimal(arr[i], &tmp);
    float p = 0.0;
    s21_from_decimal_to_float(tmp, &p);
    if (fabs(p - (float)arr[i]) > EPS_TEST) {
      printf("-\tERROR: p=%f\ttest=%f \n", p, (float)arr[i]);
      bad++;
    } else {
      good++;
    }
    ck_assert(fabs(arr[i] - p) < EPS_TEST);
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_from_decimal_to_float) {
  print_test("#TEST3: float->decimal->float");
  int good = 0;
  int bad = 0;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    s21_decimal tmp;
    s21_from_float_to_decimal(arr[i], &tmp);
    float p = 0.0;
    s21_from_decimal_to_float(tmp, &p);
    if (fabs(p - arr[i]) > EPS_TEST) {
      printf("-\tERROR: p=%f\ttest=%f \n", p, arr[i]);
      bad++;
    } else {
      good++;
      ck_assert(fabs(arr[i] - p) < EPS_TEST);
    }
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_from_float_to_int) {
  print_test("#TEST4: float->decimal->int");
  int good = 0;
  int bad = 0;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    s21_decimal tmp;
    s21_from_float_to_decimal(arr[i], &tmp);
    int p = 0;
    if (s21_from_decimal_to_int(tmp, &p) == 0) {
      if (p != (int)arr[i] && (int)arr[i] != -2147483648) {
        bad++;
      } else {
        good++;
      }
      ck_assert_int_eq((int)arr[i], p);
    }
  }
  print_result(bad, good);
  printf("\n");
}
END_TEST

START_TEST(test_compare) {
  print_test("#TEST5: compare functions");
  compare_all_test(get_eq, s21_is_equal, "    TEST is_equal");
  compare_all_test(get_not_eq, s21_is_not_equal, "    TEST is_not_eq");
  compare_all_test(get_less, s21_is_less, "    TEST is_less");
  compare_all_test(get_le_or_eq, s21_is_less_or_equal, "    TEST is_le_or_eq");
  compare_all_test(get_greater, s21_is_greater, "    TEST is_greater");
  compare_all_test(get_gr_or_eq, s21_is_greater_or_equal,
                   "    TEST is_gr_or_eq");
}
END_TEST

START_TEST(test_s21add) {
  printf("\n");
  print_test("#TEST6: add");
  int good = 0;
  int bad = 0;
  s21_decimal src1;
  s21_decimal src2;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s21_from_float_to_decimal(arr[i], &src1);
      s21_from_float_to_decimal(arr[j], &src2);
      s21_decimal tmp = s21_add(src1, src2);
      float p = 0;
      s21_from_decimal_to_float(tmp, &p);
      if (tmp.value_type == s21_NORMAL_VALUE) {
        if (fabs(p) > 10e17) {
          if (fabs(p - (arr[i] + arr[j])) > EPS_TEST * fabs(arr[i] + arr[j])) {
            print_error(arr[i], arr[j], arr[i] + arr[j], p, "+");
            bad++;
          } else {
            good++;
          }
        } else {
          if (fabs(p - (arr[i] + arr[j])) > EPS_TEST) {
            print_error(arr[i], arr[j], arr[i] + arr[j], p, "+");
            bad++;
          } else {
            good++;
          }
          ck_assert(fabs(p - (arr[i] + arr[j])) < EPS_TEST);
        }
      }
    }
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_s21sub) {
  print_test("#TEST7: sub");
  int good = 0;
  int bad = 0;
  s21_decimal src1;
  s21_decimal src2;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s21_from_float_to_decimal(arr[i], &src1);
      s21_from_float_to_decimal(arr[j], &src2);
      s21_decimal tmp = s21_sub(src1, src2);
      float p = 0;
      s21_from_decimal_to_float(tmp, &p);
      if (tmp.value_type == s21_NORMAL_VALUE) {
        if (fabs(p) > 10e17) {
          if (fabs(p - (arr[i] - arr[j])) > EPS_TEST * fabs(arr[i] - arr[j])) {
            print_error(arr[i], arr[j], arr[i] - arr[j], p, "-");
            bad++;
          } else {
            good++;
          }
        } else {
          if (fabs(p - (arr[i] - arr[j])) > EPS_TEST) {
            print_error(arr[i], arr[j], arr[i] - arr[j], p, "-");
            bad++;
          } else {
            good++;
          }
          ck_assert(fabs(p - (arr[i] - arr[j])) < EPS_TEST);
        }
      }
    }
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_s21mul) {
  int good = 0;
  int bad = 0;
  print_test("#TEST8: mul");
  s21_decimal src1;
  s21_decimal src2;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (fabs(arr[i]) > 1e29 || fabs(arr[j]) > 1e29) continue;
      s21_from_float_to_decimal(arr[i], &src1);
      s21_from_float_to_decimal(arr[j], &src2);
      s21_decimal tmp = s21_mul(src1, src2);
      float p = 0;
      float t1 = 0;
      float t2 = 0;
      double summ = (arr[i] * arr[j]);
      double summ_abs = fabs(summ);
      s21_from_decimal_to_float(tmp, &p);
      s21_from_decimal_to_float(src1, &t1);
      s21_from_decimal_to_float(src2, &t2);
      if (summ_abs < 7.9228163e+28) {
        if (tmp.value_type == s21_NORMAL_VALUE) {
          if (summ_abs > 1000) {
            if (fabs(summ - p) > 0.001 * summ_abs) {
              print_error(arr[i], arr[j], arr[i] * arr[j], p, "*");
              bad++;
            } else {
              good++;
            }
          } else {
            if (fabs(p - (arr[i] * arr[j])) > EPS_TEST * 100) {
              print_error(arr[i], arr[j], arr[i] * arr[j], p, "*");
              bad++;
            } else {
              good++;
            }
          }
        } else {
          bad++;
        }
      } else {
        if (tmp.value_type != s21_NORMAL_VALUE) {
          good++;
        } else {
          print_error(arr[i], arr[j], arr[i] * arr[j], p, "*");
          bad++;
        }
      }
    }
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_s21div) {
  print_test("#TEST9: div");
  s21_decimal src1;
  s21_decimal src2;
  int good = 0;
  int bad = 0;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s21_from_float_to_decimal(arr[i], &src1);
      s21_from_float_to_decimal(arr[j], &src2);
      s21_decimal tmp = s21_div(src1, src2);
      float p = 0;
      s21_from_decimal_to_float(tmp, &p);
      if (tmp.value_type == s21_NORMAL_VALUE) {
        if (fabs(arr[j]) < 1e-19) {
          good++;
        } else if (fabs(arr[i] / arr[j]) > 1000) {
          if (fabs(p - (arr[i] / arr[j])) >
              EPS_TEST * fabs((arr[i] / arr[j]))) {
            print_error(arr[i], arr[j], arr[i] / arr[j], p, "/");
            bad++;
          } else {
            good++;
          }
        } else if (fabs(p - (arr[i] / arr[j])) > EPS_TEST) {
          print_error(arr[i], arr[j], arr[i] / arr[j], p, "/");
          bad++;
        } else {
          good++;
        }
      } else {
        if (tmp.value_type != s21_NORMAL_VALUE) {
          good++;

        } else {
          print_error(arr[i], arr[j], arr[i] / arr[j], p, "/");
          bad++;
        }
      }
    }
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_s21mod) {
  print_test("#TEST10: mod");
  s21_decimal src1;
  s21_decimal src2;
  int good = 0;
  int bad = 0;
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s21_from_float_to_decimal(arr[i], &src1);
      s21_from_float_to_decimal(arr[j], &src2);
      s21_decimal tmp = s21_mod(src1, src2);
      float p = 0;
      s21_from_decimal_to_float(tmp, &p);
      float fm = fmod(arr[i], arr[j]);
      if (tmp.value_type == s21_NORMAL_VALUE) {
        if (fabs(p - fm) > EPS_TEST) {
          if (fabs(arr[i] / arr[j]) < 100000000 && p != 0) {
            bad++;
            print_error(arr[i], arr[j], fmod(arr[i], arr[j]), p, "mod");
          } else {
            good++;
          }
        } else {
          good++;
          ck_assert(fabs(p - fm) < EPS_TEST);
        }
      } else {
        if (isnan(fm) && (tmp.value_type == s21_NAN)) {
          good++;
        } else {
          print_error(arr[i], arr[j], fmod(arr[i], arr[j]), p, "mod");
        }
      }
    }
  }
  print_result(bad, good);
  printf("\n");
}
END_TEST

START_TEST(test_floor) { all_test(floor, s21_floor, "#TEST11: floor"); }
END_TEST

START_TEST(test_round) { all_test(round, s21_round, "#TEST12: round"); }
END_TEST

START_TEST(test_truncate) {
  int good = 0;
  int bad = 0;
  print_test("#TEST13: trunc");
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    s21_decimal tmp;
    s21_from_float_to_decimal(arr[i], &tmp);
    tmp = s21_truncate(tmp);
    float p = 0.0;
    s21_from_decimal_to_float(tmp, &p);
    if (fabs(arr[i]) < LLONG_MAX) {
      if (fabs(p - ((long long int)arr[i])) > 1) {
        printf("-\tERROR: p=%f\n\t    test=%f \n", p,
               (float)((long long int)arr[i]));
        bad++;
      } else {
        good++;
      }
      ck_assert(fabs(p - ((long long int)arr[i])) < 1);
    } else {
      good++;
    }
  }
  print_result(bad, good);
}
END_TEST

START_TEST(test_negate) {
  all_test(neagate, s21_negate, "#TEST14: negat");
  printf("\n\n");
}
END_TEST

START_TEST(test_other) {
  print_test("#TEST15: other");
  // битовое представление различает отрицательные и положительные нули. Эти
  // значения могут считаться эквивалентными во всех операциях.
  s21_decimal tmp1;
  s21_from_float_to_decimal(-0.0, &tmp1);
  tmp1.bits[3] += 0x80000000;
  // tmp1.value_type = s21_NAN;
  s21_decimal tmp2;
  s21_from_int_to_decimal(0, &tmp2);
  printf("%s", (((s21_is_less(tmp1, tmp2) == 1) &&
                 (s21_is_less_or_equal(tmp1, tmp2) == 0) &&
                 (s21_is_equal(tmp1, tmp2) == 0) &&
                 (s21_is_not_equal(tmp1, tmp2) == 1) &&
                 (s21_is_greater(tmp1, tmp2) == 1) &&
                 (s21_is_greater_or_equal(tmp1, tmp2) == 0)) == 1)
                   ? "+"
                   : "-");

  //  Если числа слишком малы (0 < |x| < 1e-28), вернуть ошибку и значение,
  //  равное 0, value_type = 0
  int err = s21_from_float_to_decimal(1e-29, &tmp1);
  printf("%s", tmp1.value_type == 0 && err == 1 ? "+" : "-");
  err = s21_from_float_to_decimal(-1e-29, &tmp1);
  printf("%s", tmp1.value_type == 0 && err == 1 ? "+" : "-");
  // Если числа слишком велики(| x | >   79228162514264337593543950335) или
  // равны бесконечности, вернуть ошибку и  value_type бесконечности с
  // соответствующим знаком При обработке числа с   типом float
  // преобразовывать все содержащиеся в нём цифры
  err = s21_from_float_to_decimal(1.0 / 0.0, &tmp1);
  printf("%s", tmp1.value_type == 1 && err == 1 ? "+" : "-");
  err = s21_from_float_to_decimal(-1.0 / 0.0, &tmp1);
  printf("%s", tmp1.value_type == 2 && err == 1 ? "+" : "-");
  err = s21_from_float_to_decimal(0.0 / 0.0, &tmp1);
  printf("%s", tmp1.value_type == 3 && err == 1 ? "+" : "-");
  err = s21_from_float_to_decimal(-792281625142643375935439503350.0, &tmp1);
  printf("%s", tmp1.value_type == 2 && err == 1 ? "+" : "-");
  err = s21_from_float_to_decimal(792281625142643375935439503350.0, &tmp1);
  printf("%s", tmp1.value_type == 1 && err == 1 ? "+" : "-");

  s21_decimal result = s21_sub(tmp1, tmp2);
  err = err && result.value_type != 0;
  result = s21_add(tmp1, tmp2);
  err = err && result.value_type != 0;
  result = s21_div(tmp1, tmp2);
  err = err && result.value_type != 0;
  result = s21_mul(tmp1, tmp2);
  err = err && result.value_type != 0;
  result = s21_mod(tmp1, tmp2);
  err = err && result.value_type != 0;
  result = s21_sub(tmp2, tmp1);
  result = s21_add(tmp2, tmp1);
  err = err && result.value_type != 0;
  result = s21_div(tmp2, tmp1);
  err = err && result.value_type == 0;
  result = s21_mul(tmp2, tmp1);
  err = err && result.value_type != 0;
  result = s21_mod(tmp2, tmp1);
  printf("%s", err == 1 ? "+" : "-");

  s21_decimal a = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}, 0};
  s21_decimal b = (s21_decimal){{6, 0, 0, 0x80010000}, 0};    // -0.6
  s21_decimal c = (s21_decimal){{60, 0, 0, 0x00020000}, 0};   // +0.6
  s21_decimal d = (s21_decimal){{400, 0, 0, 0x00030000}, 0};  // +0.4

  result = s21_add(a, b);
  printf("%s", s21_is_equal(result, (s21_decimal){{0xFFFFFFFE, 0xFFFFFFFF,
                                                   0xFFFFFFFF, 0},
                                                  0}) == S21_TRUE
                   ? "+"
                   : "-");
  result = s21_add(a, c);

  printf("%s", s21_is_equal(result, (s21_decimal){{0, 0, 0, 0}, 1}) == S21_TRUE
                   ? "+"
                   : "-");

  result = s21_sub(a, c);
  printf("%s", s21_is_equal(result, (s21_decimal){{0xFFFFFFFE, 0xFFFFFFFF,
                                                   0xFFFFFFFF, 0},
                                                  0}) == S21_TRUE
                   ? "+"
                   : "-");
  result = s21_sub(a, b);
  printf("%s", s21_is_equal(result, (s21_decimal){{0, 0, 0, 0}, 1}) == S21_TRUE
                   ? "+"
                   : "-");

  result = s21_sub(a, d);
  printf("%s", s21_is_equal(result, (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF,
                                                   0xFFFFFFFF, 0},
                                                  0}) == S21_TRUE
                   ? "+"
                   : "-");
  a = (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}, 0};
  b = (s21_decimal){{0xFFFFFFFF, 0, 0, 0x8000000}, 0};
  result = s21_mul(a, b);
  printf("%s", s21_is_equal(result,
                            (s21_decimal){{1, 0xFFFFFFFF, 0xFFFFFFFE, 0}, 0}) ==
                       S21_TRUE
                   ? "+"
                   : "-");

  a = (s21_decimal){{0xFFFFFFFF, 0, 0, 0}, 0};
  b = (s21_decimal){{1, 1, 1, 0x80000000}, 0};
  result = s21_mul(a, b);
  printf("%s", s21_is_equal(result, (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF,
                                                   0xFFFFFFFF, 0x80000000},
                                                  0}) == S21_TRUE
                   ? "+"
                   : "-");
  // print_bit(result);
  printf("\n");
}

END_TEST

int test_rdontos() {
  Suite *s = suite_create("All Part");
  TCase *tc = tcase_create("Test1");
  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);

  tcase_add_test(tc, test_from_decimal_to_int);
  tcase_add_test(tc, test_from_int_to_float);
  tcase_add_test(tc, test_from_decimal_to_float);
  tcase_add_test(tc, test_from_float_to_int);
  tcase_add_test(tc, test_compare);

  tcase_add_test(tc, test_s21add);
  tcase_add_test(tc, test_s21sub);
  tcase_add_test(tc, test_s21mul);
  tcase_add_test(tc, test_s21div);
  tcase_add_test(tc, test_s21mod);

  tcase_add_test(tc, test_floor);
  tcase_add_test(tc, test_round);
  tcase_add_test(tc, test_truncate);
  tcase_add_test(tc, test_negate);

  tcase_add_test(tc, test_other);

  srunner_run_all(sr, CK_ENV);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf;
}

int main(void) {
  int nf = 0;
  nf += test_rdontos();
  return 0;
}

void print_test(char *name) { printf("\n%s:\t", name); }

void print_result(int bad, int good) {
  printf("\tbad=[%d], good=[%d]", bad, good);
}

void print_error(float a, float b, float f, float p, char *s) {
  printf("-\tERROR: %.28f (%s) %.28f = %.28f [%.28f]\n", a, s, b, f, p);
}

int get_eq(float a, float b) { return !(a == b); }
int get_not_eq(float a, float b) { return !(a != b); }
int get_less(float a, float b) { return !(a < b); }
int get_le_or_eq(float a, float b) { return !(a <= b); }
int get_greater(float a, float b) { return !(a > b); }
int get_gr_or_eq(float a, float b) { return !(a >= b); }
double neagate(double d) { return -d; }

void all_test(double (*func)(double), s21_decimal (*func_dec)(s21_decimal),
              char *name) {
  int good = 0;
  int bad = 0;
  print_test(name);
  float arr[] = TEST_CASE_FLOAT;
  int n = sizeof(arr) / sizeof(float);
  for (int i = 0; i < n; i++) {
    s21_decimal tmp;
    s21_from_float_to_decimal(arr[i], &tmp);
    tmp = func_dec(tmp);
    float p = 0.0;
    s21_from_decimal_to_float(tmp, &p);
    if (fabs(func(arr[i]) - p) > EPS_TEST) {
      printf("-\tERROR: p=%f\n\t    test=%f \n", p, func(arr[i]));
      bad++;
    } else {
      good++;
    }
    ck_assert(fabs(func(arr[i]) - p) < EPS_TEST);
  }
  print_result(bad, good);
}

void compare_all_test(int (*funk_res)(float, float),
                      int (*func)(s21_decimal, s21_decimal), char *name) {
  int bad = 0;
  int good = 0;
  s21_decimal src1;
  s21_decimal src2;
  float arr[] = TEST_CASE_FLOAT;
  float n = sizeof(arr) / sizeof(float);
  printf("\n%s", name);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s21_from_float_to_decimal(arr[i], &src1);
      s21_from_float_to_decimal(arr[j], &src2);
      int result = funk_res(arr[i], arr[j]);
      if (func(src1, src2) == result) {
        good++;
      } else {
        print_error(arr[i], arr[j], result, func(src1, src2), "cmp");
        bad++;
      }
      ck_assert(func(src1, src2) == result);
    }
  }
  print_result(bad, good);
}
