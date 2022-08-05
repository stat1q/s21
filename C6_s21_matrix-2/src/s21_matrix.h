#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define EPS 1e-8
// Сравнение должно происходить вплоть до 7 знака после запятой включительно.

#define SUCCESS 1
#define FAILURE 0

typedef enum {
  CORRECT_MATRIX = 0,
  INCORRECT_MATRIX = 1,
  IDENTITY_MATRIX = 2,
  ZERO_MATRIX = 3
} matrix_type_t;

// CORRECT_MATRIX - корректная матрица,
// INCORRECT_MATRIX - при ошибках в действиях с матрицами,
// IDENTITY_MATRIX - единичная матрица,
// ZERO_MATRIX - нулевая матрица.

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
  matrix_type_t matrix_type;
} matrix_t;

/*
Поле matrix_type определяет тип матрицы, CORRECT_MATRIX - корректная матрица,
INCORRECT_MATRIX - при ошибках в действиях с матрицами, IDENTITY_MATRIX -
единичная матрица, ZERO_MATRIX - нулевая матрица. Заполнение матрицы в случае
типа INCORRECT_MATRIX не определено.
*/
matrix_t s21_create_matrix(int rows, int columns);
// Поле matrix_type должно инициализироваться значением ZERO_MATRIX.

// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t* A);

// Две матрицы A, B совпадают |A = B|, если совпадают их размеры и
// соответствующие элементы равны, то есть при всех i, j A(i,j) = B(i,j).
// Сравнение должно происходить вплоть до 7 знака после запятой включительно.
int s21_eq_matrix(matrix_t* A, matrix_t* B);

matrix_t s21_sum_matrix(matrix_t* A, matrix_t* B);
matrix_t s21_sub_matrix(matrix_t* A, matrix_t* B);
/*
Суммой двух матриц A = m × n и B = m × n одинаковых размеров называется
матрица C = m × n = A + B тех же размеров, элементы которой определяются
равенствами C(i,j) = A(i,j) + B(i,j).
Разностью двух матриц A = m × n и B = m × n одинаковых размеров называется
матрица C = m × n = A - B тех же размеров, элементы которой определяются
равенствами C(i,j) = A(i,j) - B(i,j). */

// Произведением матрицы A = m × n на число λ называется матрица B = m × n = λ ×
// A, элементы которой определяются равенствами B = λ × A(i,j).
matrix_t s21_mult_number(matrix_t* A, double number);

// Произведением матрицы A = m × k на матрицу B = k × n называется матрица C = m
// × n = A × B размера m × n, элементы которой определяются равенством C(i,j) =
// A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) × B(k,j).
matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B);

// Транспонирование матрицы А заключается в замене строк этой матрицы ее
// столбцами с сохранением их номеров.
matrix_t s21_transpose(matrix_t* A);

// Минором M(i,j) называется определитель (n-1)-го порядка, полученный
// вычёркиванием из матрицы A i-й строки и j-го столбца.
matrix_t s21_calc_complements(matrix_t* A);

// Определитель матрицы (determinant)
double s21_determinant(matrix_t* A);

// Матрицу A в степени -1 называют обратной к квадратной матрице А, если
// произведение этих матриц равняется единичной матрице.
matrix_t s21_inverse_matrix(matrix_t* A);

#endif  // SRC_S21_MATRIX_H_
