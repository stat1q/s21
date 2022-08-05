#include "parser.h"

double get_result(char *str, double x) {
  symb_st *input_stack = NULL;
  int flag_err = parser(&input_stack, str);
  symb_st *result_stack = get_polish(input_stack);
  double result = expression_calc(result_stack, x, &flag_err);
  if (flag_err == ERROR) {
    result = NAN;
  }
  free_stack(&result_stack);
  return result;
}

double calc_operation(double n1, double n2, char oper) {
  double res = 0;

  switch (oper) {
    case '+':
      res = n2 + n1;
      break;
    case '-':
      res = n2 - n1;
      break;
    case '*':
      res = n2 * n1;
      break;
    case '/':
      res = n2 / n1;
      break;
    case '^':
      res = pow(n2, n1);
      break;
    case 'm':
      res = fmod(n2, n1);
      break;
  }
  return res;
}

double calc_function(double n, char func) {
  double res = 0;

  switch (func) {
    case 'c':
      res = cos(n);
      break;
    case 's':
      res = sin(n);
      break;
    case 't':
      res = tan(n);
      break;
    case 'o':
      res = acos(n);
      break;
    case 'i':
      res = asin(n);
      break;
    case 'a':
      res = atan(n);
      break;
    case 'q':
      res = sqrt(n);
      break;
    case 'n':
      res = log(n);
      break;
    case 'g':
      res = log10(n);
      break;
  }
  return res;
}

double expression_calc(symb_st *input_stack, double x, int *flag_err) {
  symb_st *calc_stack = NULL;
  symb_st *ptr = input_stack;
  expr res;
  double result = 0, num1 = 0, num2 = 0;

  while (ptr != NULL && *flag_err != ERROR) {
    switch (ptr->value.symb_type) {
      case VALUE:
        push(&calc_stack, ptr->value);
        break;
      case UNKNOWN_X:
        ptr->value.value = x;
        ptr->value.symb_type = VALUE;
        push(&calc_stack, ptr->value);
        break;
      case OPERATION:
        if (calc_stack != NULL && calc_stack->value.symb_type == VALUE) {
          num1 = pop(&calc_stack).value;
          if (calc_stack != NULL && calc_stack->value.symb_type == VALUE) {
            num2 = pop(&calc_stack).value;
            res.symb_type = VALUE;
            res.value = calc_operation(num1, num2, ptr->value.operation);
            push(&calc_stack, res);
          } else {
            *flag_err = ERROR;
            break;
          }
        } else {
          *flag_err = ERROR;
          break;
        }
        break;
      case FUNCTION:
        if (calc_stack != NULL && calc_stack->value.symb_type == VALUE) {
          num1 = pop(&calc_stack).value;
        } else {
          *flag_err = ERROR;
          break;
        }
        res.symb_type = VALUE;
        res.value = calc_function(num1, ptr->value.operation);
        push(&calc_stack, res);
        break;
    }
    ptr = ptr->next;
  }
  if (calc_stack != NULL && *flag_err != ERROR &&
      calc_stack->value.symb_type == VALUE) {
    result = pop(&calc_stack).value;
    if (calc_stack != NULL) {
      printf("ERRORRRRR1111\n");
      *flag_err = ERROR;
    }
  } else {
    *flag_err = ERROR;
    printf("ERRORRRRR\n");
  }
  return result;
}
