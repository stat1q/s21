#include "s21_matrix.h"

int is_correct(matrix_t* A, matrix_t* B);
int is_correct_one(matrix_t* A);
int get_type(matrix_t* A);
matrix_t get_minor(matrix_t* A, int n, int m);

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t result;
  result.columns = columns;
  result.rows = rows;
  if (rows > 0 && columns > 0) {
    result.matrix = (double**)calloc(rows, sizeof(double*));
    for (int i = 0; i < result.rows; i++) {
      result.matrix[i] = (double*)calloc(result.columns, sizeof(double));
    }
    result.matrix_type = ZERO_MATRIX;
  } else {
    result.matrix_type = INCORRECT_MATRIX;
    result.columns = 0;
    result.rows = 0;
    result.matrix = NULL;
  }
  return result;
}

void s21_remove_matrix(matrix_t* A) {
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
      A->columns = 0;
      A->rows = 0;
      A->matrix_type = INCORRECT_MATRIX;
    }
  }
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int result = FAILURE;
  if (is_correct(A, B) == SUCCESS) {
    result = SUCCESS;
    for (int i = 0; i < A->rows && result == SUCCESS; i++) {
      for (int j = 0; j < A->columns && result == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

matrix_t s21_sum_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (is_correct(A, B) == SUCCESS) {
    result = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_sub_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (is_correct(A, B) == SUCCESS) {
    result = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_mult_number(matrix_t* A, double number) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS) {
    result = s21_create_matrix(A->rows, A->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_mult_matrix(matrix_t* A, matrix_t* B) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && is_correct_one(B) == SUCCESS &&
      A->columns == B->rows) {
    result = s21_create_matrix(A->rows, B->columns);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

int is_correct(matrix_t* A, matrix_t* B) {
  int result = FAILURE;
  if (A != NULL && B != NULL) {
    if ((A->rows > 0 && A->columns > 0 && A->matrix_type != INCORRECT_MATRIX) &&
        (B->rows > 0 && B->columns > 0 && B->matrix_type != INCORRECT_MATRIX) &&
        (A->rows == B->rows && A->columns == B->columns)) {
      result = SUCCESS;
    }
  }
  return result;
}

int is_correct_one(matrix_t* A) {
  int result = FAILURE;
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0 && A->matrix_type != INCORRECT_MATRIX) {
      result = SUCCESS;
    }
  }
  return result;
}

int get_type(matrix_t* A) {
  int result = INCORRECT_MATRIX;
  if (is_correct_one(A)) {
    int is_zero_diagonal = 1;
    int is_zero = 1;
    int is_idenity = 1;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (i == j) {
          if (fabs(A->matrix[i][j] - 1.0) > EPS) is_idenity = 0;
          if (fabs(A->matrix[i][j]) > EPS) is_zero_diagonal = 0;
        } else {
          if (fabs(A->matrix[i][j]) > EPS) is_zero = 0;
        }
      }
    }
    if (is_zero && is_zero_diagonal)
      result = ZERO_MATRIX;
    else if (is_zero && is_zero_diagonal)
      result = ZERO_MATRIX;
    else if (is_zero && is_idenity)
      result = IDENTITY_MATRIX;
    else
      result = CORRECT_MATRIX;
  }
  return result;
}

matrix_t s21_transpose(matrix_t* A) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS) {
    result = s21_create_matrix(A->columns, A->rows);
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[j][i];
      }
    }
    result.matrix_type = get_type(&result);
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

double s21_determinant(matrix_t* A) {
  double result = 0.0;
  if (is_correct_one(A) == SUCCESS && A->columns == A->rows) {
    if (A->columns == 1) {
      result = A->matrix[0][0];
    } else {
      for (int i = 0; i < A->columns; i++) {
        matrix_t t = get_minor(A, 0, i);
        int z = (i % 2) == 0 ? 1 : -1;
        result += z * A->matrix[0][i] * s21_determinant(&t);
        s21_remove_matrix(&t);
      }
    }
  } else {
    result = NAN;
  }
  return result;
}

matrix_t s21_calc_complements(matrix_t* A) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && A->columns == A->rows) {
    result = s21_create_matrix(A->columns, A->rows);
    if (A->columns == 1) {
      result.matrix[0][0] = 1;
    } else {
      for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.columns; j++) {
          matrix_t t = get_minor(A, i, j);
          int z = ((i + j) % 2) == 0 ? 1 : -1;
          result.matrix[i][j] = z * s21_determinant(&t);
          s21_remove_matrix(&t);
        }
      }
      result.matrix_type = get_type(&result);
    }
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t s21_inverse_matrix(matrix_t* A) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && A->columns == A->rows) {
    double det = s21_determinant(A);
    if (det != 0) {
      matrix_t B = s21_calc_complements(A);
      matrix_t C = s21_transpose(&B);
      result = s21_mult_number(&C, (1.0 / det));
      s21_remove_matrix(&B);
      s21_remove_matrix(&C);
    } else {
      result = s21_create_matrix(0, 0);
    }
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}

matrix_t get_minor(matrix_t* A, int n, int m) {
  matrix_t result;
  if (is_correct_one(A) == SUCCESS && A->columns > 1 && A->rows > 1) {
    result = s21_create_matrix(A->rows - 1, A->columns - 1);
    for (int i = 0; i < result.rows; i++) {
      int ii = (i >= n) ? i + 1 : i;
      for (int j = 0; j < result.columns; j++) {
        int jj = (j >= m) ? j + 1 : j;
        result.matrix[i][j] = A->matrix[ii][jj];
      }
    }
    result.matrix_type = CORRECT_MATRIX;
  } else {
    result = s21_create_matrix(0, 0);
  }
  return result;
}
