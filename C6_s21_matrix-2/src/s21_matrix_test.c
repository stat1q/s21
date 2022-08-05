#include "s21_matrix.h"

#include <check.h>

// Заполнение матрицы.
void __filling_matrix(matrix_t *A, float value);
// Заполнение корректной матрицы из массива
void __filling_from_array(matrix_t *A, const double *value);
// Создание нулевой матрицы
matrix_t __create_identity_matrix(int rows, int columns);

char *matrix_type_arr[] = {"CORRECT_MATRIX", "INCORRECT_MATRIX",
                           "IDENTITY_MATRIX", "ZERO_MATRIX"};

START_TEST(create_matrix) {
  // CREATE_MATRIX Test №1

  // Создание матриц при положительных rows and columns
  // Проверяем, что rows != 0 and columns != 0
  // Проверяем тип матрицы на ZERO_MATRIX

  matrix_t test_matrix[] = {s21_create_matrix(2, 2), s21_create_matrix(5, 10),
                            s21_create_matrix(10, 5)};
  {
    for (int number = 0; number < 3; number++) {
      ck_assert_msg(test_matrix[number].rows != 0,
                    "\n\ncreate_matrix test №1, matrix №%d\n rows %d == 0\n",
                    number, test_matrix[number].rows);
      ck_assert_msg(test_matrix[number].columns != 0,
                    "\n\nreate_matrix test №1, matrix №%d\n columns %d == 0\n",
                    number, test_matrix[number].columns);
      ck_assert_msg(test_matrix[number].matrix_type == ZERO_MATRIX,
                    "\n\ncreate_matrix test №1, matrix №%d\n %s != %s\n",
                    number, matrix_type_arr[test_matrix[number].matrix_type],
                    matrix_type_arr[ZERO_MATRIX]);

      s21_remove_matrix(&test_matrix[number]);
    }
  }
  // CREATE_MATRIX Test №2

  // Создание матриц при 0 и отрицытельных rows and columns
  // Проверяем, что rows == 0 and columns == 0
  // Проверяем тип матрицы на INCORRECT_MATRIX
  {
    matrix_t test_matrix[] = {s21_create_matrix(0, 0),
                              s21_create_matrix(-5, -9)};
    {
      for (int number = 0; number < 2; number++) {
        ck_assert_msg(test_matrix[number].rows == 0,
                      "\n\ncreate_matrix test №2, matrix №%d\n rows %d != 0\n",
                      number, test_matrix[number].rows);
        ck_assert_msg(
            test_matrix[number].columns == 0,
            "\n\ncreate_matrix test №2, matrix №%d\n columns %d != 0\n", number,
            test_matrix[number].columns);
        ck_assert_msg(test_matrix[number].matrix_type == INCORRECT_MATRIX,
                      "\n\ncreate_matrix test №2, matrix №%d\n %s != %s\n",
                      number, matrix_type_arr[test_matrix[number].matrix_type],
                      matrix_type_arr[INCORRECT_MATRIX]);
        s21_remove_matrix(&test_matrix[number]);
      }
    }
  }
}
END_TEST

START_TEST(remove_matrix) {
  // REMOVE_MATRIX Test №1

  // Удаление матриц
  // Проверяем, что rows == 0 and columns == 0
  // Проверяем тип матрицы на INCORRECT_MATRIX
  matrix_t test_matrix[] = {s21_create_matrix(2, 2), s21_create_matrix(5, 10),
                            s21_create_matrix(10, 5), s21_create_matrix(0, 0),
                            s21_create_matrix(-5, -9)};
  {
    for (int number = 0; number < 5; number++) {
      s21_remove_matrix(&test_matrix[number]);
      ck_assert_msg(test_matrix[number].rows == 0,
                    "\n\nremove_matrix( test №1, matrix №%d\n rows %d != 0\n",
                    number, test_matrix[number].rows);
      ck_assert_msg(
          test_matrix[number].columns == 0,
          "\n\nremove_matrix( test №1, matrix №%d\n columns %d != 0\n", number,
          test_matrix[number].columns);
      ck_assert_msg(test_matrix[number].matrix_type == INCORRECT_MATRIX,
                    "\n\nremove_matrix( test №1, matrix №%d\n %s != %s\n",
                    number, matrix_type_arr[test_matrix[number].matrix_type],
                    matrix_type_arr[INCORRECT_MATRIX]);
      s21_remove_matrix(&test_matrix[number]);
    }
  }
}
END_TEST

START_TEST(eq_matrix) {
  matrix_t test_matrix_1[] = {s21_create_matrix(2, 2), s21_create_matrix(4, 9),
                              s21_create_matrix(3, 6)};
  matrix_t test_matrix_2[] = {s21_create_matrix(2, 2), s21_create_matrix(4, 9),
                              s21_create_matrix(3, 6)};
  matrix_t test_matrix_3[] = {s21_create_matrix(8, 2), s21_create_matrix(9, 4),
                              s21_create_matrix(4, 3)};
  matrix_t test_matrix_4[] = {s21_create_matrix(0, 0),
                              s21_create_matrix(-5, -9)};
  int result = 0;

  for (int number = 0; number < 3; number++) {
    __filling_matrix(&test_matrix_1[number], number + 0.1234);
    __filling_matrix(&test_matrix_2[number], number + 0.1234);
    __filling_matrix(&test_matrix_3[number], number + 0.1234);
  }

  // EQ_MATRIX Test №1
  // Матрицы равны
  {
    for (int number = 0; number < 3; number++) {
      result = s21_eq_matrix(&test_matrix_1[number], &test_matrix_2[number]);
      ck_assert_msg(result == SUCCESS,
                    "\n\neq_matrix test №1, matrix №%d\nexpected = "
                    "SUCCESS\nresult = FAILURE\n",
                    number);
    }
  }
  // EQ_MATRIX Test №2
  // Матрицы разной размерности
  {
    for (int number = 0; number < 3; number++) {
      result = s21_eq_matrix(&test_matrix_1[number], &test_matrix_3[number]);
      ck_assert_msg(result == FAILURE,
                    "\n\neq_matrix test №2, matrix №%d\nexpected = "
                    "FAILURE\nresult = SUCCESS\n",
                    number);
    }
  }
  // EQ_MATRIX Test №3
  // Матрицы одного размера, но с разными значениями
  for (int number = 0; number < 3; number++) {
    __filling_matrix(&test_matrix_1[number], 0.1234567);
    __filling_matrix(&test_matrix_2[number], 0.1234568);
    result = s21_eq_matrix(&test_matrix_1[number], &test_matrix_2[number]);
    ck_assert_msg(result == FAILURE,
                  "\n\neq_matrix test №3, matrix №%d\nexpected = "
                  "FAILURE\nresult = %d\n",
                  number, result);
  }
  // EQ_MATRIX Test №4
  // Матрицы одного размера, но с разными значениями
  // которые выходят за точность 7 знаков
  {
    for (int number = 0; number < 3; number++) {
      __filling_matrix(&test_matrix_1[number], 0.12345678);
      __filling_matrix(&test_matrix_2[number], 0.12345679);
      result = s21_eq_matrix(&test_matrix_1[number], &test_matrix_2[number]);
      ck_assert_msg(result == SUCCESS,
                    "\n\neq_matrix test №4, matrix №%d\nexpected = "
                    "SUCCESS\nresult = FAILURE\n",
                    number);
    }
  }
  // EQ_MATRIX Test №5
  // Некорректные матрицы
  {
    result = s21_eq_matrix(&test_matrix_4[0], &test_matrix_4[1]);
    ck_assert_msg(result == FAILURE,
                  "\n\neq_matrix test №5, matrix №%d\nexpected = "
                  "FAILURE\nresult = SUCCESS\n",
                  0);
  }
  // EQ_MATRIX Test №6
  // Матрицы с одинаковыми значениями, но разным типом.
  {
    __filling_matrix(&test_matrix_1[0], 5.5);
    __filling_matrix(&test_matrix_2[0], 5.5);
    test_matrix_1[0].matrix_type = INCORRECT_MATRIX;
    result = s21_eq_matrix(&test_matrix_1[0], &test_matrix_2[0]);
    ck_assert_msg(result == FAILURE,
                  "\n\neq_matrix test №6, matrix №%d\nexpected = "
                  "FAILURE\nresult = SUCCESS\n",
                  0);
  }
  for (int number = 0; number < 3; number++) {
    s21_remove_matrix(&test_matrix_1[number]);
    s21_remove_matrix(&test_matrix_2[number]);
    s21_remove_matrix(&test_matrix_3[number]);
  }
  s21_remove_matrix(&test_matrix_4[0]);
  s21_remove_matrix(&test_matrix_4[1]);
}
END_TEST

// Разных размеров
// С некорректной матрицей
// Нулевая + корретная

START_TEST(sum_matrix) {
  // Корректная матрица с числами
  matrix_t test_matrix_1 = s21_create_matrix(5, 5);
  __filling_matrix(&test_matrix_1, 5.2);
  // Единичная матрица
  matrix_t test_matrix_2 = __create_identity_matrix(3, 3);

  // Отрицательная "единичная" матрица
  matrix_t test_matrix_3 = __create_identity_matrix(3, 3);
  double value_3[] = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
  __filling_from_array(&test_matrix_3, value_3);
  // Некорректная матрица
  matrix_t test_matrix_4 = __create_identity_matrix(3, 7);

  // Результат сложения корректных матрицы
  matrix_t expected_result_1 = s21_create_matrix(5, 5);
  __filling_matrix(&expected_result_1, 5.2 + 5.2);
  // Нулевая матрица
  matrix_t expected_result_2 = s21_create_matrix(3, 3);
  // Единичная матрица
  matrix_t expected_result_3 = __create_identity_matrix(3, 3);
  // Некорректная матрицы
  matrix_t expected_result_4 = s21_create_matrix(-1, 0);

  matrix_t expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_3,
                                expected_result_4};
  // SUM_MATRIX
  {
    // Test №1 Две корректные матрицы
    matrix_t test_1_result = s21_sum_matrix(&test_matrix_1, &test_matrix_1);
    // Test №2 Единичная + -(единичная)
    matrix_t test_2_result = s21_sum_matrix(&test_matrix_2, &test_matrix_3);
    // Test №3 Нулевая + единичная
    matrix_t test_3_result = s21_sum_matrix(&expected_result_2, &test_matrix_2);
    // Test №4 Сложение с некорректной
    matrix_t test_4_result = s21_sum_matrix(&test_matrix_1, &test_matrix_4);
    // Test №5 Разных размеров
    matrix_t test_5_result = s21_sum_matrix(&test_matrix_1, &test_matrix_2);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result,
                              test_4_result, test_5_result};

    for (int number = 0; number < 5; number++) {
      if (number < 3) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\nsum_matrix test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\nsum_matrix test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }

    for (int number = 0; number < 5; number++) {
      s21_remove_matrix(&test_result[number]);
      if (number != 2) s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
  }
}
END_TEST

START_TEST(sub_matrix) {
  // Корректная матрица с числами
  matrix_t test_matrix_1 = s21_create_matrix(5, 5);
  __filling_matrix(&test_matrix_1, 5.2);
  // Единичная матрица
  matrix_t test_matrix_2 = __create_identity_matrix(3, 3);
  // Отрицательная "единичная" матрица
  matrix_t test_matrix_3 = __create_identity_matrix(3, 3);
  double value_3[] = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
  __filling_from_array(&test_matrix_3, value_3);
  // Некорректная матрица
  matrix_t test_matrix_4 = s21_create_matrix(-3, -7);
  // Нулевая матрица
  matrix_t test_matrix_5 = s21_create_matrix(3, 3);

  // Нулевая матрица
  matrix_t expected_result_1 = s21_create_matrix(5, 5);
  // Единичная + 1
  matrix_t expected_result_2 = __create_identity_matrix(3, 3);
  double exp_value_2[] = {2, 0, 0, 0, 2, 0, 0, 0, 2};
  __filling_from_array(&expected_result_2, exp_value_2);
  // Некорректная матрицы
  matrix_t expected_result_3 = s21_create_matrix(-1, 0);
  // Единичная матрица
  matrix_t expected_result_4 = __create_identity_matrix(3, 3);

  matrix_t expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_3,
                                expected_result_4};
  // SUB_MATRIX
  {
    // Test №1 Две корректные матрицы = 0
    matrix_t test_1_result = s21_sub_matrix(&test_matrix_1, &test_matrix_1);
    // Test №2 Единичная - (-единичная) = 2
    matrix_t test_2_result = s21_sub_matrix(&test_matrix_2, &test_matrix_3);
    // Test №3 Разных размеров = некорректная
    matrix_t test_3_result = s21_sub_matrix(&test_matrix_1, &test_matrix_2);
    // Test №4 Вычитание некорректной = некорректная
    matrix_t test_4_result = s21_sub_matrix(&test_matrix_1, &test_matrix_4);
    // Test №5 Единичная - нулевая = единичная
    matrix_t test_5_result = s21_sub_matrix(&test_matrix_2, &test_matrix_5);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result,
                              test_4_result, test_5_result};

    for (int number = 0; number < 5; number++) {
      if (number != 2 && number != 3) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\nsub_matrix test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\nsub_matrix test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }
    for (int number = 0; number < 5; number++) {
      s21_remove_matrix(&test_result[number]);
      s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
    s21_remove_matrix(&test_matrix_5);
  }
}
END_TEST

START_TEST(mult_number) {
  // Корректная матрица с числами
  matrix_t test_matrix_1 = s21_create_matrix(5, 5);
  __filling_matrix(&test_matrix_1, 5.2);
  // Единичная матрица
  matrix_t test_matrix_2 = __create_identity_matrix(3, 3);
  // Некорректная матрица
  matrix_t test_matrix_3 = s21_create_matrix(-3, -7);
  // Нулевая матрица
  matrix_t test_matrix_4 = s21_create_matrix(5, 5);

  matrix_t expected_result[] = {test_matrix_4, test_matrix_2, test_matrix_3};

  // MULT_NUMBER
  {
    // Test №1 Корректная * 0 = нулевая
    matrix_t test_1_result = s21_mult_number(&test_matrix_1, 0.);
    // Test №2 Единичная * 1 = единичная
    matrix_t test_2_result = s21_mult_number(&test_matrix_2, 1.0);
    // Test №3 некорректная * 5.5 = некорректная
    matrix_t test_3_result = s21_mult_number(&test_matrix_3, 5.5);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result};

    for (int number = 0; number < 3; number++) {
      if (number != 2) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\nmult_number test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\nmult_number test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }

    for (int number = 0; number < 3; number++) {
      s21_remove_matrix(&test_result[number]);
      s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
  }
}
END_TEST

START_TEST(mult_matrix) {
  // Корректная матрица 3
  matrix_t test_matrix_1 = s21_create_matrix(3, 5);
  __filling_matrix(&test_matrix_1, 3);
  // Корректная матрица 5
  matrix_t test_matrix_2 = s21_create_matrix(5, 3);
  __filling_matrix(&test_matrix_2, 5);
  // Некорректная матрица
  matrix_t test_matrix_3 = s21_create_matrix(-3, -7);
  // Нулевая матрица
  matrix_t test_matrix_4 = s21_create_matrix(6, 6);
  // Единичная матрица
  matrix_t test_matrix_5 = __create_identity_matrix(6, 6);

  // Корректная матрица 75
  matrix_t expected_result_1 = s21_create_matrix(3, 3);
  __filling_matrix(&expected_result_1, 75);
  // Нулевая
  matrix_t expected_result_2 = s21_create_matrix(6, 6);
  // Некорректная
  matrix_t expected_result_3 = s21_create_matrix(-3, 0);

  matrix_t expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_3};

  // MULT_MATRIX
  {
    // Test №1 Корректная * корректную = корректная
    matrix_t test_1_result = s21_mult_matrix(&test_matrix_1, &test_matrix_2);
    // Test №2 Единичная * нулевую = нулевая
    matrix_t test_2_result = s21_mult_matrix(&test_matrix_4, &test_matrix_5);
    // Test №3 Не подходящих размеров = некорректная
    matrix_t test_3_result = s21_mult_matrix(&test_matrix_5, &test_matrix_1);
    // Test №4 Корректная * некорректная = некорректная
    matrix_t test_4_result = s21_mult_matrix(&test_matrix_1, &test_matrix_3);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result,
                              test_4_result};

    for (int number = 0; number < 4; number++) {
      if (number < 2) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\nmult_matrix test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\nmult_matrix test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }

    for (int number = 0; number < 4; number++) {
      s21_remove_matrix(&test_result[number]);
      s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
    s21_remove_matrix(&test_matrix_5);
  }
}
END_TEST

START_TEST(transpose) {
  // Корректная матрица
  matrix_t test_matrix_1 = s21_create_matrix(3, 5);
  double value_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  __filling_from_array(&test_matrix_1, value_1);
  // Единичная матрица
  matrix_t test_matrix_2 = __create_identity_matrix(3, 3);
  // Нулевая матрица
  matrix_t test_matrix_3 = s21_create_matrix(3, 5);
  // Некорректная матрица
  matrix_t test_matrix_4 = s21_create_matrix(-3, -7);

  // Корректная матрица
  matrix_t expected_result_1 = s21_create_matrix(3, 5);
  double exp_value_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  __filling_from_array(&expected_result_1, exp_value_1);
  // Единичная матрица
  matrix_t expected_result_2 = __create_identity_matrix(3, 3);
  // Нулевая
  matrix_t expected_result_3 = s21_create_matrix(5, 3);
  // Некорректная
  matrix_t expected_result_4 = s21_create_matrix(-3, 0);

  matrix_t expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_4};

  // TRANSPOSE_MATRIX
  {
    // Test №1 (AT)T = A
    matrix_t temp_result = s21_transpose(&test_matrix_1);
    matrix_t test_1_result = s21_transpose(&temp_result);
    // Test №2 Единичная = Единичная
    matrix_t test_2_result = s21_transpose(&test_matrix_2);
    // Test №3 Нулевая = Т(нулевя)
    matrix_t test_3_result = s21_transpose(&test_matrix_3);
    // Test №4 Некорректная = некорректная
    matrix_t test_4_result = s21_transpose(&test_matrix_4);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result,
                              test_4_result};

    for (int number = 0; number < 4; number++) {
      if (number < 3) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\ntranspose test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\ntranspose test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }
    for (int number = 0; number < 4; number++) {
      s21_remove_matrix(&test_result[number]);
      s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
    s21_remove_matrix(&temp_result);
  }
}
END_TEST

START_TEST(calc_complements) {
  // Примеры
  // Нулевая матрица
  matrix_t test_matrix_1 = s21_create_matrix(3, 3);
  // Матрица из примера в редми
  matrix_t test_matrix_2 = s21_create_matrix(3, 3);
  double value_2[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  __filling_from_array(&test_matrix_2, value_2);
  // Единичная матрица
  matrix_t test_matrix_3 = __create_identity_matrix(4, 4);
  // Матрица не равного размера
  matrix_t test_matrix_4 = s21_create_matrix(2, 5);

  // Ожидаемый результат
  // Нулевая матрица
  matrix_t expected_result_1 = s21_create_matrix(3, 3);
  // Матрица из примера в редми
  matrix_t expected_result_2 = s21_create_matrix(3, 3);
  double exp_value_2[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  __filling_from_array(&expected_result_2, exp_value_2);
  // Единичная матрица
  matrix_t expected_result_3 = __create_identity_matrix(4, 4);
  // Некорректная
  matrix_t expected_result_4 = s21_create_matrix(-3, 0);

  matrix_t expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_4};

  // CALC_COMPLEMENTS
  {
    // Test №1 Нулевая = нулевая
    matrix_t test_1_result = s21_calc_complements(&test_matrix_1);
    // Test №2 Пример из редми
    matrix_t test_2_result = s21_calc_complements(&test_matrix_2);
    // Test №3 Единичная = Единичная
    matrix_t test_3_result = s21_calc_complements(&test_matrix_3);
    // Test №4 Некорректная = некорректная
    matrix_t test_4_result = s21_calc_complements(&test_matrix_4);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result,
                              test_4_result};

    for (int number = 0; number < 4; number++) {
      if (number < 3) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\ncalc_complements test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\ncalc_complements test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }

    for (int number = 0; number < 4; number++) {
      s21_remove_matrix(&test_result[number]);
      s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
  }
}
END_TEST

START_TEST(determinant) {
  // Примеры
  // Нулевая матрица
  matrix_t test_matrix_1 = s21_create_matrix(3, 3);
  // Матрица 123..789
  matrix_t test_matrix_2 = s21_create_matrix(3, 3);
  double value_2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  __filling_from_array(&test_matrix_2, value_2);
  // Единичная матрица
  matrix_t test_matrix_3 = __create_identity_matrix(4, 4);
  // Матрица не равного размера
  matrix_t test_matrix_4 = s21_create_matrix(2, 5);
  // Матрица 5х5
  matrix_t test_matrix_5 = s21_create_matrix(5, 5);
  double value_5[] = {4, 9, -3, 2, 0, -2, -1, 0,  4, 5, 11, 2, -4,
                      5, 8, 9,  0, 1, -4, 8,  -2, 3, 4, 1,  0};
  __filling_from_array(&test_matrix_5, value_5);
  // Матрица 1х1
  matrix_t test_matrix_6 = s21_create_matrix(1, 1);
  test_matrix_6.matrix[0][0] = 234.567;

  // DETERMINANT
  {
    // Ожидаемый результат
    // Нулевая = 0
    double expected_result_1 = 0.;
    // Нулевой определитель
    double expected_result_2 = 0.;
    // Единичная матрица = 1
    double expected_result_3 = 1.;
    // Некорректная = NAN
    double expected_result_4 = NAN;
    // Матрица 5х5
    double expected_result_5 = 20554.;
    // Матрица 5х5
    double expected_result_6 = 234.567;

    // Test №1 Нулевая = 0
    double test_1_result = s21_determinant(&test_matrix_1);
    // Test №2 Пример из редми
    double test_2_result = s21_determinant(&test_matrix_2);
    // Test №3 Единичная = Единичная
    double test_3_result = s21_determinant(&test_matrix_3);
    // Test №4 Некорректная = некорректная
    double test_4_result = s21_determinant(&test_matrix_4);
    // Test №5 Корректная 5х5
    double test_5_result = s21_determinant(&test_matrix_5);
    // Test №6 Корректная 5х5
    double test_6_result = s21_determinant(&test_matrix_6);

    double test_result[] = {test_1_result, test_2_result, test_3_result,
                            test_4_result, test_5_result, test_6_result};

    double expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_4,
                                expected_result_5, expected_result_6};

    for (int number = 0; number < 6; number++) {
      if (number != 3) {
        ck_assert_msg(
            test_result[number] == expected_result[number],
            "\n\ndeterminant test №%d, \nexpected = %f\nresult = %f\n",
            number + 1, expected_result[number], test_result[number]);
      } else {
        ck_assert_msg(
            test_result[number] != expected_result[number],
            "\n\ndeterminant test №%d, \nexpected = %f\nresult = %f\n",
            number + 1, expected_result[number], test_result[number]);
      }
    }

    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
    s21_remove_matrix(&test_matrix_5);
    s21_remove_matrix(&test_matrix_6);
  }
}
END_TEST

START_TEST(inverse_matrix) {
  // Примеры
  // Нулевая матрица
  matrix_t test_matrix_1 = s21_create_matrix(3, 3);
  double value_1[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  __filling_from_array(&test_matrix_1, value_1);
  // Матрица из примера в редми
  matrix_t test_matrix_2 = s21_create_matrix(5, 5);
  double value_2[] = {4,  9, -3, 2, 0, -2,    -1, 0,  4, 5, 11, 2,
                      -4, 5, 8,  9, 0, 1 - 4, 8,  -2, 3, 4, 1,  0};
  __filling_from_array(&test_matrix_2, value_2);
  // Матрица с нулевым det
  matrix_t test_matrix_3 = __create_identity_matrix(3, 3);
  double value_3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  __filling_from_array(&test_matrix_3, value_3);
  // Матрица не равного размера
  matrix_t test_matrix_4 = s21_create_matrix(2, 5);

  // Ожидаемый результат
  // Единичная матрица
  matrix_t expected_result_1 = __create_identity_matrix(3, 3);
  // Единичная матрица
  matrix_t expected_result_2 = __create_identity_matrix(5, 5);
  // Некорректная
  matrix_t expected_result_3 = s21_create_matrix(-5, 4);
  // Некорректная
  matrix_t expected_result_4 = s21_create_matrix(-2, 5);

  matrix_t expected_result[] = {expected_result_1, expected_result_2,
                                expected_result_3, expected_result_4};

  // INVERSE_MATRIX
  {
    // Test №1 Корректная * инверсию = 1
    matrix_t temp_1_result = s21_inverse_matrix(&test_matrix_1);
    matrix_t test_1_result = s21_mult_matrix(&test_matrix_1, &temp_1_result);
    // Test №2 Корректная * инверсию = 1
    matrix_t temp_2_result = s21_inverse_matrix(&test_matrix_2);
    matrix_t test_2_result = s21_mult_matrix(&test_matrix_2, &temp_2_result);
    // Test №3 Детерминант = 0 = NULL
    matrix_t test_3_result = s21_inverse_matrix(&test_matrix_3);
    // Test №4 Некорректная = NULL
    matrix_t test_4_result = s21_inverse_matrix(&test_matrix_4);

    matrix_t test_result[] = {test_1_result, test_2_result, test_3_result,
                              test_4_result};

    for (int number = 0; number < 4; number++) {
      if (number < 2) {
        int eq_result =
            s21_eq_matrix(&test_result[number], &expected_result[number]);
        ck_assert_msg(eq_result == SUCCESS,
                      "\n\ninverse_matrix test №%d, \nexpected = "
                      "SUCCESS\nresult = %d\n",
                      number + 1, eq_result);
      } else {
        ck_assert_msg(test_result[number].matrix_type == INCORRECT_MATRIX,
                      "\n\ninverse_matrix test №%d, \nexpected = "
                      "INCORRECT\nresult = %d\n",
                      number + 1, test_result[number].matrix_type);
      }
    }

    for (int number = 0; number < 4; number++) {
      s21_remove_matrix(&test_result[number]);
      s21_remove_matrix(&expected_result[number]);
    }
    s21_remove_matrix(&test_matrix_1);
    s21_remove_matrix(&test_matrix_2);
    s21_remove_matrix(&test_matrix_3);
    s21_remove_matrix(&test_matrix_4);
    s21_remove_matrix(&temp_1_result);
    s21_remove_matrix(&temp_2_result);
  }
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf = 0;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, create_matrix);
  tcase_add_test(tc1_1, remove_matrix);
  tcase_add_test(tc1_1, eq_matrix);
  tcase_add_test(tc1_1, sum_matrix);
  tcase_add_test(tc1_1, sub_matrix);
  tcase_add_test(tc1_1, mult_number);
  tcase_add_test(tc1_1, mult_matrix);
  tcase_add_test(tc1_1, transpose);
  tcase_add_test(tc1_1, calc_complements);
  tcase_add_test(tc1_1, determinant);
  tcase_add_test(tc1_1, inverse_matrix);

  srunner_run_all(sr, CK_VERBOSE);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf != 0;
}

// ADDITIONAL FUNCTIONS

// Заполнение корректной матрицы 1-м значением
void __filling_matrix(matrix_t *A, float value) {
  if (A->rows > 0 && A->columns > 0) {
    A->matrix_type = CORRECT_MATRIX;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value;
      }
    }
  }
}

// Заполнение корректной матрицы из массива
void __filling_from_array(matrix_t *A, const double *value) {
  if (A->rows > 0 && A->columns > 0) {
    A->matrix_type = CORRECT_MATRIX;
    int k = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value[k];
        k++;
      }
    }
  }
}

// Создание единичной матрицы
matrix_t __create_identity_matrix(int rows, int columns) {
  matrix_t identity_matrix = s21_create_matrix(rows, columns);
  if (rows > 0 && columns > 0 && rows == columns) {
    identity_matrix.matrix_type = IDENTITY_MATRIX;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (i == j) {
          identity_matrix.matrix[i][j] = 1;
        }
      }
    }
  } else {
    s21_remove_matrix(&identity_matrix);
  }
  return identity_matrix;
}
