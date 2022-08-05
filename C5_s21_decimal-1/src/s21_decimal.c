#include "s21_decimal.h"

void s21_set_zero_decimal(s21_decimal *dst);
void s21_set_degree(s21_decimal *dst, int degree);
void s21_set_sign(s21_decimal *dst, int sign);
void s21_set_degree_sign(s21_decimal *dst, int degree, int sign);

int s21_get_degree(s21_decimal src);
int s21_get_sign(s21_decimal src);
int s21_get_exp_float(float src);
int s21_get_i_max_bit(s21_decimal src);
int s21_get_i_bit(s21_decimal src, int num);
int s21_get_round_mod(s21_decimal src);

s21_decimal s21_shift_bit_left(s21_decimal src);
s21_decimal s21_shift_bit_right(s21_decimal src);
int s21_shift_multiply_by_10(s21_decimal *dst);
int s21_shift_divide_by_10(s21_decimal *dst);
int s21_shift_leveling_degree(s21_decimal *dst1, s21_decimal *dst2);

int s21_is_overflow(s21_decimal src);
int s21_is_less_abs_with_degree(s21_decimal src1, s21_decimal src2);
int s21_is_less_abs(s21_decimal src1, s21_decimal src2);
int s21_is_null(s21_decimal *dst);

void s21_float_decimal(float src, s21_decimal *dst);

s21_decimal s21_add_t(s21_decimal src1, s21_decimal src2);
s21_decimal s21_sub_t(s21_decimal src1, s21_decimal src2);
s21_decimal s21_mul_t(s21_decimal src1, s21_decimal src2);
s21_decimal s21_mul_not_inf(s21_decimal src1, s21_decimal src2);
s21_decimal s21_div_t(s21_decimal src1, s21_decimal src2);
s21_decimal s21_mod_t(s21_decimal src1, s21_decimal src2);

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = S21_CONVERTING_ERROR;
  if (dst != NULL) {
    s21_set_zero_decimal(dst);
    if (src < 0) {
      s21_set_sign(dst, S21_NEGATIVE);
      src *= -1;
    }
    dst->bits[S21_LOW] = src;
    dst->value_type = s21_NORMAL_VALUE;
    flag = S21_SUCCESS;
  }
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = S21_SUCCESS;
  if (src.value_type == s21_NORMAL_VALUE && dst != NULL) {
    int degree = s21_get_degree(src);
    if (degree > 0) {
      while (degree > 0) {
        s21_shift_divide_by_10(&src);
        degree--;
      }
      s21_set_degree(&src, 0);
    }
    if (src.bits[S21_MID] == 0 && src.bits[S21_HIG] == 0 &&
        (src.bits[S21_LOW] & 0x80000000) == 0) {
      *dst = src.bits[S21_LOW];
      if (s21_get_sign(src) != S21_POSITIVE) {
        *dst *= -1;
      }
    } else if (src.bits[S21_MID] == 0 && src.bits[S21_HIG] == 0 &&
               (unsigned int)src.bits[S21_LOW] == 0x80000000 &&
               s21_get_sign(src) != S21_POSITIVE) {
      *dst = -2147483648;
    } else {
      flag = S21_CONVERTING_ERROR;
      *dst = 0;
    }
  } else {
    flag = S21_CONVERTING_ERROR;
  }
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = S21_CONVERTING_ERROR;
  if (dst != NULL) {
    s21_set_zero_decimal(dst);
    if (isnan(src)) {
      dst->value_type = s21_NAN;
    } else if (src > 79228162514264337593543950335.0) {
      dst->value_type = s21_INFINITY;
    } else if (src < -79228162514264337593543950335.0) {
      dst->value_type = s21_NEGATIVE_INFINITY;
    } else if (!(src < 1e-28 && src > -1e-28 && src != 0.0)) {
      if (src != 0.0) {
        s21_float_decimal(src, dst);
      }
      flag = S21_SUCCESS;
    }
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = S21_CONVERTING_ERROR;
  if (dst != NULL) {
    flag = S21_SUCCESS;
    if (src.value_type == s21_NORMAL_VALUE) {
      *dst = 0.0;
      long double t =
          ((double)(unsigned int)src.bits[S21_LOW] +
           ((double)(unsigned int)src.bits[S21_MID] * 4294967295.0) +
           ((double)(unsigned int)src.bits[S21_HIG] * 4294967295.0 *
            4294967295.0)) /
          powl(10, s21_get_degree(src));

      *dst = (float)t;
      if (s21_get_sign(src) == S21_NEGATIVE) {
        *dst *= -1;
      }
    } else if (src.value_type == s21_INFINITY) {
      *dst = 1.0 / 0.0;
    } else if (src.value_type == s21_NEGATIVE_INFINITY) {
      *dst = -1.0 / 0.0;
    } else if (src.value_type == s21_NAN) {
      *dst = 0.0 / 0.0;
    }
  }
  return flag;
}

s21_decimal s21_add(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  if ((src1.value_type == s21_NAN || src2.value_type == s21_NAN) ||
      (src1.value_type == s21_INFINITY &&
       src2.value_type == s21_NEGATIVE_INFINITY) ||
      (src2.value_type == s21_INFINITY &&
       src1.value_type == s21_NEGATIVE_INFINITY)) {
    result.value_type = s21_NAN;
  } else if (src1.value_type == s21_INFINITY ||
             src2.value_type == s21_INFINITY) {
    result.value_type = s21_INFINITY;
  } else if (src1.value_type == s21_NEGATIVE_INFINITY ||
             src2.value_type == s21_NEGATIVE_INFINITY) {
    result.value_type = s21_NEGATIVE_INFINITY;
  } else {
    s21_shift_leveling_degree(&src1, &src2);
    if (s21_get_sign(src1) == s21_get_sign(src2)) {
      result = s21_add_t(src1, src2);
    } else {
      result = s21_sub(src1, s21_negate(src2));
    }
  }
  return result;
}

s21_decimal s21_sub(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  if ((src1.value_type == s21_NAN || src2.value_type == s21_NAN) ||
      (src1.value_type == s21_INFINITY && src2.value_type == s21_INFINITY) ||
      (src2.value_type == s21_NEGATIVE_INFINITY &&
       src1.value_type == s21_NEGATIVE_INFINITY)) {
    result.value_type = s21_NAN;
  } else if (src1.value_type == s21_INFINITY ||
             src2.value_type == s21_NEGATIVE_INFINITY) {
    result.value_type = s21_INFINITY;
  } else if (src1.value_type == s21_NEGATIVE_INFINITY ||
             src2.value_type == s21_INFINITY) {
    result.value_type = s21_NEGATIVE_INFINITY;
  } else {
    s21_shift_leveling_degree(&src1, &src2);
    if (s21_get_sign(src1) != s21_get_sign(src2)) {
      result = s21_add(src1, s21_negate(src2));
    } else {
      if (s21_is_less_abs(src1, src2) == S21_TRUE) {
        result = s21_sub_t(src2, src1);
        s21_set_sign(&result, !s21_get_sign(src1));
      } else {
        result = s21_sub_t(src1, src2);
        s21_set_sign(&result, s21_get_sign(src1));
      }
    }
    s21_set_degree(&result, s21_get_degree(src1));
  }
  return result;
}

s21_decimal s21_mul(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  if (src1.value_type == s21_NAN || src2.value_type == s21_NAN) {
    result.value_type = s21_NAN;
  } else if (src1.value_type != s21_NORMAL_VALUE ||
             src2.value_type != s21_NORMAL_VALUE) {
    if (s21_is_null(&src1) == S21_TRUE || s21_is_null(&src2) == S21_TRUE) {
      result.value_type = s21_NAN;
    } else {
      int t1 = ((s21_get_sign(src1) == S21_NEGATIVE) ||
                src1.value_type == s21_NEGATIVE_INFINITY);
      int t2 = ((s21_get_sign(src2) == S21_NEGATIVE) ||
                src2.value_type == s21_NEGATIVE_INFINITY);
      result.value_type =
          ((t1 ^ t2) == S21_NEGATIVE) ? s21_NEGATIVE_INFINITY : s21_INFINITY;
    }
  } else if (s21_is_null(&src1) == S21_TRUE || s21_is_null(&src2) == S21_TRUE) {
    result.value_type = s21_NORMAL_VALUE;
  } else {
    result = s21_mul_t(src1, src2);
  }
  return result;
}

s21_decimal s21_div(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  if ((src1.value_type == s21_NAN || src2.value_type == s21_NAN) ||
      (s21_is_null(&src1) == S21_TRUE && s21_is_null(&src2) == S21_TRUE) ||
      (src1.value_type != s21_NORMAL_VALUE &&
       src2.value_type != s21_NORMAL_VALUE)) {
    result.value_type = s21_NAN;
  } else if (src1.value_type == s21_NORMAL_VALUE &&
             src2.value_type != s21_NORMAL_VALUE) {
    result.value_type = s21_NORMAL_VALUE;
  } else if ((src2.value_type == s21_NORMAL_VALUE &&
              src1.value_type != s21_NORMAL_VALUE) ||
             (s21_is_null(&src2) == S21_TRUE)) {
    int t1 = ((s21_get_sign(src1) == S21_NEGATIVE) ||
              src1.value_type == s21_NEGATIVE_INFINITY);
    int t2 = ((s21_get_sign(src2) == S21_NEGATIVE) ||
              src2.value_type == s21_NEGATIVE_INFINITY);
    result.value_type =
        ((t1 ^ t2) == S21_NEGATIVE) ? s21_NEGATIVE_INFINITY : s21_INFINITY;
  } else {
    if (src1.value_type != s21_NORMAL_VALUE ||
        src2.value_type != s21_NORMAL_VALUE) {
      result.value_type = s21_NAN;
    } else if (s21_is_null(&src2) == S21_TRUE) {
      result.value_type = s21_NAN;
    } else if (s21_is_null(&src1) == S21_TRUE) {
      result.value_type = s21_NORMAL_VALUE;
    } else {
      result = s21_div_t(src1, src2);
    }
  }
  return result;
}

s21_decimal s21_mod(s21_decimal src1, s21_decimal src2) {
  s21_decimal result_mod;
  s21_set_zero_decimal(&result_mod);
  if (src1.value_type != s21_NORMAL_VALUE || src2.value_type == s21_NAN) {
    result_mod.value_type = s21_NAN;
  } else if (s21_is_null(&src2) == S21_TRUE) {
    result_mod.value_type = s21_NAN;
  } else if (s21_is_null(&src1) == S21_TRUE) {
    result_mod.value_type = s21_NORMAL_VALUE;
  } else if (s21_is_less_abs_with_degree(src1, src2) == S21_TRUE ||
             (src2.value_type == s21_INFINITY ||
              src2.value_type == s21_NEGATIVE_INFINITY)) {
    result_mod = src1;
  } else {
    result_mod = s21_mod_t(src1, src2);
  }
  return result_mod;
}

s21_decimal s21_negate(s21_decimal src) {
  if (src.value_type == s21_NORMAL_VALUE) {
    s21_set_sign(&src, !s21_get_sign(src));
  } else {
    s21_set_zero_decimal(&src);
  }
  return src;
}

int s21_is_less(s21_decimal src1, s21_decimal src2) {
  int result = S21_FALSE;
  s21_is_null(&src1);
  s21_is_null(&src2);
  int sign1 = s21_get_sign(src1);
  int sign2 = s21_get_sign(src2);
  if (src1.value_type == s21_NORMAL_VALUE &&
      src2.value_type == s21_NORMAL_VALUE) {
    if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
      result = S21_FALSE;
    } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
      result = S21_TRUE;
    } else if (sign1 == sign2) {
      if (s21_get_degree(src1) != s21_get_degree(src2)) {
        s21_shift_leveling_degree(&src1, &src2);
      }
      int i = 2;
      while (i > 0 &&
             (unsigned int)src1.bits[i] == (unsigned int)src2.bits[i]) {
        i--;
      }
      if (((unsigned int)src1.bits[i] < (unsigned int)src2.bits[i] &&
           sign1 == S21_POSITIVE) ||
          ((unsigned int)src1.bits[i] > (unsigned int)src2.bits[i] &&
           sign1 == S21_NEGATIVE)) {
        result = S21_TRUE;
      } else {
        result = S21_FALSE;
      }
    }
  } else if ((src1.value_type == s21_NEGATIVE_INFINITY &&
              src2.value_type == s21_NORMAL_VALUE) ||
             (src1.value_type == s21_NORMAL_VALUE &&
              src2.value_type == s21_INFINITY) ||
             (src1.value_type == s21_NEGATIVE_INFINITY &&
              src2.value_type == s21_INFINITY)) {
    result = S21_TRUE;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal src1, s21_decimal src2) {
  return s21_is_less(src1, src2) && s21_is_equal(src1, src2);
}

int s21_is_greater(s21_decimal src1, s21_decimal src2) {
  return s21_is_less(src2, src1);
}

int s21_is_greater_or_equal(s21_decimal src1, s21_decimal src2) {
  return !s21_is_less(src1, src2);
}

int s21_is_equal(s21_decimal src1, s21_decimal src2) {
  int result = S21_FALSE;
  if (src1.value_type == s21_NORMAL_VALUE &&
      src2.value_type == s21_NORMAL_VALUE) {
    s21_is_null(&src1);
    s21_is_null(&src2);
    int sign1 = s21_get_sign(src1);
    int sign2 = s21_get_sign(src2);
    if (sign1 == sign2) {
      s21_shift_leveling_degree(&src1, &src2);
      for (int i = 2; i >= 0; i--) {
        int tmp_result = (unsigned)src1.bits[i] != (unsigned)src2.bits[i];
        if (tmp_result == S21_TRUE) {
          result = S21_TRUE;
        } else {
          result = S21_FALSE;
          break;
        }
      }
    }
  } else if ((src1.value_type == s21_NEGATIVE_INFINITY &&
              src2.value_type == s21_NEGATIVE_INFINITY) ||
             (src1.value_type == s21_INFINITY &&
              src2.value_type == s21_INFINITY)) {
    result = S21_TRUE;
  }
  return result;
}

int s21_is_not_equal(s21_decimal src1, s21_decimal src2) {
  return !s21_is_equal(src1, src2);
}

s21_decimal s21_truncate(s21_decimal src) {
  if (src.value_type == s21_NORMAL_VALUE) {
    int degree = s21_get_degree(src);
    if (degree > 0) {
      while (degree > 0) {
        s21_shift_divide_by_10(&src);
        degree--;
      }
      s21_set_degree(&src, 0);
    }
  } else {
    int t = src.value_type;
    s21_set_zero_decimal(&src);
    src.value_type = t;
  }
  return src;
}

s21_decimal s21_floor(s21_decimal src) {
  if (src.value_type == s21_NORMAL_VALUE) {
    int degree = s21_get_degree(src);
    if (degree > 0) {
      while (degree > 0) {
        s21_shift_divide_by_10(&src);
        degree--;
      }
      s21_set_degree(&src, 0);
      if (s21_get_sign(src) == S21_NEGATIVE) {
        s21_decimal tmp;
        s21_from_int_to_decimal(1, &tmp);
        src = s21_sub(src, tmp);
      }
    }
  } else {
    int t = src.value_type;
    s21_set_zero_decimal(&src);
    src.value_type = t;
  }
  return src;
}

s21_decimal s21_round(s21_decimal src) {
  if (src.value_type == s21_NORMAL_VALUE) {
    int degree = s21_get_degree(src);
    if (degree > 0) {
      while (degree > 1) {
        s21_shift_divide_by_10(&src);
        degree--;
      }
      int round_mod = s21_get_round_mod(src);
      s21_shift_divide_by_10(&src);
      s21_set_degree(&src, 0);
      if (round_mod == 1) {
        s21_decimal tmp;
        s21_from_int_to_decimal(1, &tmp);
        if (s21_get_sign(src) == S21_POSITIVE) {
          src = s21_add(src, tmp);
        } else {
          src = s21_sub(src, tmp);
        }
      }
    }
  } else {
    int t = src.value_type;
    s21_set_zero_decimal(&src);
    src.value_type = t;
  }
  return src;
}

void s21_set_zero_decimal(s21_decimal *dst) {
  dst->value_type = s21_NORMAL_VALUE;
  dst->bits[S21_LOW] = dst->bits[S21_MID] = dst->bits[S21_HIG] =
      dst->bits[S21_DEG] = 0;
}

void s21_set_degree(s21_decimal *dst, int degree) {
  if (degree > 28 || degree < 0) {
  } else {
    degree = degree << 16;
    int sign = 0x80000000 & dst->bits[S21_DEG];
    dst->bits[S21_DEG] = degree + sign;
  }
}

void s21_set_sign(s21_decimal *dst, int sign) {
  unsigned int degree = 0xFF0000 & dst->bits[S21_DEG];
  dst->bits[S21_DEG] = (sign == S21_POSITIVE) ? 0 : 0x80000000;
  dst->bits[S21_DEG] += degree;
}

void s21_set_degree_sign(s21_decimal *dst, int degree, int sign) {
  degree = degree << 16;
  sign = sign << 31;
  dst->bits[S21_DEG] = degree + sign;
}

int s21_get_degree(s21_decimal src) {
  return (0xFF0000 & src.bits[S21_DEG]) >> 16;
}

int s21_get_sign(s21_decimal src) {
  return (0x80000000 & src.bits[S21_DEG]) > 0;
}

int s21_shift_multiply_by_10(s21_decimal *dst) {
  int flag = S21_SUCCESS;
  if (s21_is_overflow(*dst)) {
    flag = S21_CONVERTING_ERROR;
  } else {
    unsigned long int transfer = 0;
    for (int i = 0; i < 3; i++) {
      unsigned long int long_int = 0;
      long_int = (unsigned long int)(dst->bits[i] & 0xFFFFFFFF);
      long_int = long_int * 10 + transfer;
      dst->bits[i] = long_int & 0xFFFFFFFF;
      transfer = long_int >> 32 & 0xFFFFFFFF;
    }
    if (transfer > 0) {
      s21_set_zero_decimal(dst);
      dst->value_type = (s21_get_sign(*dst) == S21_POSITIVE)
                            ? s21_INFINITY
                            : s21_NEGATIVE_INFINITY;
      flag = S21_CONVERTING_ERROR;
    }
  }
  return flag;
}

int s21_shift_divide_by_10(s21_decimal *dst) {
  unsigned long long int transfer = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned long long int long_int = 0;
    long_int = (unsigned long long int)(dst->bits[i] & 0xFFFFFFFF) + transfer;
    dst->bits[i] = (unsigned int)((long_int / 10) & 0xFFFFFFFF);
    transfer = 0;
    transfer = ((long_int % 10) & 0xFFFFFFFF) << 32;
  }
  return S21_SUCCESS;
}

int s21_shift_leveling_degree(s21_decimal *dst1, s21_decimal *dst2) {
  int degree1 = s21_get_degree(*dst1);
  int degree2 = s21_get_degree(*dst2);
  int max_degree = fmax(degree1, degree2);
  while (degree1 < max_degree &&
         s21_is_overflow(*dst1) != S21_CONVERTING_ERROR) {
    degree1++;
    s21_shift_multiply_by_10(dst1);
    s21_set_degree(dst1, degree1);
  }
  max_degree = degree1;
  while (degree2 < max_degree &&
         s21_is_overflow(*dst2) != S21_CONVERTING_ERROR) {
    degree2++;
    s21_shift_multiply_by_10(dst2);
    s21_set_degree(dst2, degree2);
  }
  max_degree = degree1;
  while (degree2 > max_degree) {
    int round_mod = s21_get_round_mod(*dst2);
    degree2--;
    s21_shift_divide_by_10(dst2);
    s21_set_degree(dst2, degree2);
    if (round_mod == 1) {
      s21_decimal tmp;
      s21_from_int_to_decimal(1, &tmp);
      s21_set_degree(&tmp, degree2);
      *dst2 = (s21_get_sign(*dst2) == S21_POSITIVE) ? s21_add(*dst2, tmp)
                                                    : s21_sub(*dst2, tmp);
    }
  }
  max_degree = degree2;
  while (degree1 > max_degree) {
    int round_mod = s21_get_round_mod(*dst1);
    degree1--;
    s21_shift_divide_by_10(dst1);
    s21_set_degree(dst1, degree1);
    if (round_mod == 1) {
      s21_decimal tmp;
      s21_from_int_to_decimal(1, &tmp);
      s21_set_degree(&tmp, degree1);

      *dst1 = (s21_get_sign(*dst1) == S21_POSITIVE) ? s21_add(*dst1, tmp)
                                                    : s21_sub(*dst1, tmp);
    }
  }

  return S21_SUCCESS;
}

int s21_is_overflow(s21_decimal src) {
  return ((unsigned long int)src.bits[S21_HIG] >= (unsigned long int)0x19999999)
             ? S21_CONVERTING_ERROR
             : S21_SUCCESS;
}

s21_decimal s21_mul_not_inf(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  for (int i = 0; i <= s21_get_i_max_bit(src2); i++) {
    if (src1.value_type != s21_NORMAL_VALUE) {
      result.value_type = src1.value_type;
      break;
    }
    if (s21_get_i_bit(src2, i)) {
      result = s21_add(result, src1);
    }
    if (result.value_type != s21_NORMAL_VALUE) {
      break;
    }
    src1 = s21_shift_bit_left(src1);
  }
  s21_set_sign(&result, s21_get_sign(src1) ^ s21_get_sign(src2));
  int degree = s21_get_degree(src1) + s21_get_degree(src2);
  if (degree >= 28) {
    while (degree >= 28) {
      s21_shift_divide_by_10(&result);
      degree--;
    }
  }
  s21_set_degree(&result, degree);
  return result;
}

int s21_is_less_abs_with_degree(s21_decimal src1, s21_decimal src2) {
  s21_set_sign(&src1, S21_POSITIVE);
  s21_set_sign(&src2, S21_POSITIVE);
  return s21_is_less(src1, src2);
}

int s21_is_less_abs(s21_decimal src1, s21_decimal src2) {
  int result = 0;
  if (s21_get_degree(src1) != s21_get_degree(src2)) {
    s21_shift_leveling_degree(&src1, &src2);
  }
  int i = 2;
  while (i > 0 && (unsigned int)src1.bits[i] == (unsigned int)src2.bits[i]) {
    i--;
  }
  if ((unsigned int)src1.bits[i] < (unsigned int)src2.bits[i]) {
    result = S21_TRUE;
  } else {
    result = S21_FALSE;
  }
  return result;
}

int s21_get_i_bit(s21_decimal src, int num) {
  return ((unsigned int)src.bits[num / 32] & 0x1 << (num % 32)) > 0;
}

s21_decimal s21_shift_bit_left(s21_decimal src) {
  unsigned long long int transfer = 0;
  s21_decimal result;
  s21_set_zero_decimal(&result);
  for (int i = 0; i < 3; i++) {
    unsigned long long int long_int = 0;
    long_int = (unsigned long long int)(src.bits[i] & 0xFFFFFFFF);
    result.bits[i] = (unsigned int)((long_int << 1) & 0xFFFFFFFF) + transfer;
    transfer = ((long_int >> 31) & 0xFFFFFFFF);
  }
  result.bits[S21_DEG] = src.bits[S21_DEG];
  if (transfer > 0) {
    s21_set_zero_decimal(&result);
    result.value_type = (s21_get_sign(src) == S21_POSITIVE)
                            ? s21_INFINITY
                            : s21_NEGATIVE_INFINITY;
  }
  return result;
}

s21_decimal s21_shift_bit_right(s21_decimal src) {
  unsigned int transfer = 0;
  s21_decimal result;
  s21_set_zero_decimal(&result);
  for (int i = 2; i >= 0; i--) {
    unsigned int long_int = 0;
    long_int = (unsigned int)(src.bits[i] & 0xFFFFFFFF);

    result.bits[i] = (unsigned int)((long_int >> 1) & 0xFFFFFFFF) + transfer;
    transfer = (long_int & 0x1) << 31;
  }
  result.bits[S21_DEG] = src.bits[S21_DEG];
  return result;
}

int s21_get_i_max_bit(s21_decimal src) {
  int t = 95;
  while (!s21_get_i_bit(src, t) && t >= 0) t--;
  return t;
}

int s21_get_round_mod(s21_decimal src) {
  int result = 0;
  unsigned int long_int = 0;
  long_int = (unsigned int)(src.bits[S21_LOW] & 0xFFFFFFFF);
  if (long_int % 10 >= 5)
    result = 1;
  else
    result = 0;
  return result;
}

int s21_is_null(s21_decimal *dst) {
  int result = S21_FALSE;
  if (dst->value_type == s21_NORMAL_VALUE) {
    if (dst->bits[S21_LOW] == 0 && dst->bits[S21_MID] == 0 &&
        dst->bits[S21_HIG] == 0) {
      dst->bits[S21_DEG] = 0;
      result = S21_TRUE;
    }
  }
  return result;
}

int s21_get_exp_float(float src) {
  int t = *(int *)&src;
  return ((t >> 23) & 0xFF) - 127;
}

void s21_float_decimal(float src, s21_decimal *dst) {
  int sign = S21_POSITIVE;
  if (src < 0) {
    sign = S21_NEGATIVE;
    src *= -1;
  }
  int exp = s21_get_exp_float(src);
  double tmp = (double)src;
  int degree = 0;
  while (degree < 28 && (int)tmp / (int)powl(2, 21) == 0) {
    tmp *= 10;
    degree++;
  }
  tmp = round(tmp);
  while (fmod(tmp, 10) == 0 && degree > 0) {
    degree--;
    tmp /= 10;
  }
  float fl = tmp;
  exp = s21_get_exp_float(fl);
  if (exp < 96) {
    dst->bits[exp / 32] = 1 << exp % 32;
    for (int i = exp - 1, j = 22; j >= 0; i--, j--)
      if ((*(int *)&fl & (0x1 << j)) != 0) dst->bits[i / 32] |= 0x1 << i % 32;
  } else {
    dst->bits[S21_HIG] = dst->bits[S21_MID] = dst->bits[S21_LOW] = 0xFFFFFFFF;
  }
  s21_set_degree_sign(dst, degree, sign);
}

s21_decimal s21_add_t(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  s21_set_degree_sign(&result, s21_get_degree(src1), s21_get_sign(src1));
  unsigned int transfer = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long int long_int = 0;
    long_int = (unsigned long int)(src1.bits[i] & 0xFFFFFFFF) +
               (unsigned long int)(src2.bits[i] & 0xFFFFFFFF) + transfer;
    result.bits[i] = (unsigned int)(long_int & 0xFFFFFFFF);
    transfer = 0;
    transfer = (unsigned int)((long_int >> 32) & 0xFFFFFFFF);
  }
  if (transfer > 0) {
    s21_set_zero_decimal(&result);
    result.value_type = (s21_get_sign(src1) == S21_POSITIVE)
                            ? s21_INFINITY
                            : s21_NEGATIVE_INFINITY;
  }
  return result;
}

s21_decimal s21_sub_t(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  if (src1.value_type != s21_NORMAL_VALUE ||
      src2.value_type != s21_NORMAL_VALUE) {
    result.value_type = s21_NAN;
  } else {
    unsigned int transfer = 0;
    for (int i = 0; i < 3; i++) {
      unsigned long int long_int = 0x100000000;
      long_int += (unsigned long int)(src1.bits[i] & 0xFFFFFFFF) -
                  (unsigned long int)(src2.bits[i] & 0xFFFFFFFF) - transfer;
      result.bits[i] = (unsigned int)(long_int & 0xFFFFFFFF);
      if (((long_int >> 32) & 0xFFFFFFFF) != 1) {
        transfer = 1;
      } else {
        transfer = 0;
      }
    }
    if (transfer > 0) {
      s21_set_zero_decimal(&result);
      result.value_type = (s21_get_sign(src1) == S21_POSITIVE)
                              ? s21_INFINITY
                              : s21_NEGATIVE_INFINITY;
    }
  }
  return result;
}

s21_decimal s21_mul_t(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  result = s21_mul_not_inf(src1, src2);
  int degree1 = s21_get_degree(src1);
  int degree2 = s21_get_degree(src2);
  int max_degree = fmax(degree1, degree2);
  while (result.value_type != s21_NORMAL_VALUE && max_degree > 0) {
    if (degree1 > degree2) {
      degree1--;
      s21_shift_divide_by_10(&src1);
      s21_set_degree(&src1, degree1);
    } else {
      degree2--;
      s21_shift_divide_by_10(&src2);
      s21_set_degree(&src2, degree2);
    }
    result = s21_mul_not_inf(src2, src1);
    max_degree = fmax(degree1, degree2);
  }
  if (result.value_type != s21_NORMAL_VALUE) {
    int sign = s21_get_sign(result);
    s21_set_zero_decimal(&result);
    result.value_type =
        (sign == S21_NEGATIVE) ? s21_NEGATIVE_INFINITY : s21_INFINITY;
  }
  return result;
}

s21_decimal s21_div_t(s21_decimal src1, s21_decimal src2) {
  s21_decimal result;
  s21_set_zero_decimal(&result);
  int degree1 = s21_get_degree(src1);
  while (degree1 < 28 && s21_is_overflow(src1) != S21_CONVERTING_ERROR) {
    degree1++;
    s21_shift_multiply_by_10(&src1);
    s21_set_degree(&src1, degree1);
  }
  s21_decimal tmp2 = src2;
  s21_decimal tmp1 = src1;
  tmp1.bits[S21_DEG] = tmp2.bits[S21_DEG] = 0;
  s21_decimal one;

  s21_set_zero_decimal(&one);
  one.bits[S21_LOW] = 0x1;
  int i = 1;
  while (s21_is_less_or_equal(tmp2, tmp1) == S21_TRUE &&
         s21_get_i_bit(tmp2, 95) != 1) {
    tmp2 = s21_shift_bit_left(tmp2);
    i++;
  }
  if (i != 0) {
    if (s21_is_greater(tmp2, tmp1) == S21_TRUE) {
      tmp2 = s21_shift_bit_right(tmp2);
      i--;
    }
    while (i > 0) {
      result = s21_shift_bit_left(result);
      if (s21_is_less_or_equal(tmp2, tmp1) == S21_TRUE) {
        result = s21_add(result, one);
        tmp1 = s21_sub(tmp1, tmp2);
      }
      tmp2 = s21_shift_bit_right(tmp2);
      i--;
    }
    s21_set_sign(&result, s21_get_sign(src1) ^ s21_get_sign(src2));
    int degree = s21_get_degree(src1) - s21_get_degree(src2);
    if (degree < 0) {
      while (degree < 0) {
        if (s21_shift_multiply_by_10(&result) == S21_CONVERTING_ERROR) {
          s21_set_zero_decimal(&result);
          result.value_type =
              ((s21_get_sign(src1) ^ s21_get_sign(src2)) == S21_POSITIVE)
                  ? s21_INFINITY
                  : s21_NEGATIVE_INFINITY;
          degree = 0;
          break;
        }
        degree++;
      }
    }
    s21_set_degree(&result, degree);
  }
  return result;
}

s21_decimal s21_mod_t(s21_decimal src1, s21_decimal src2) {
  s21_decimal result_mod;
  s21_set_zero_decimal(&result_mod);
  int sign = s21_get_sign(src1);
  s21_set_sign(&src1, S21_POSITIVE);
  s21_set_sign(&src2, S21_POSITIVE);
  if (s21_is_equal(src1, src2) != S21_TRUE) {
    result_mod =
        s21_sub(src1, s21_mul(s21_truncate(s21_div(src1, src2)), src2));
    if (result_mod.value_type != s21_NORMAL_VALUE) {
      src2 = s21_truncate(src2);
      result_mod =
          s21_sub(src1, s21_mul(s21_truncate(s21_div(src1, src2)), src2));
      if (result_mod.value_type != s21_NORMAL_VALUE) {
        s21_set_zero_decimal(&result_mod);
      } else {
        s21_set_sign(&result_mod, sign);
      }
    } else if (s21_is_greater_or_equal(result_mod, src2) == S21_TRUE) {
      s21_set_zero_decimal(&result_mod);
    } else {
      s21_set_sign(&result_mod, sign);
    }
  }
  return result_mod;
}
