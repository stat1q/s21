#include "parser.h"

int get_priority(char oper) {
  int priority = 0;
  switch (oper) {
    case '^':
      priority = 3;
      break;
    case '*':
    case '/':
      priority = 2;
      break;
    case '+':
    case '-':
      priority = 1;
      break;
    case '(':
      priority = -1;
      break;
    case ')':
      priority = -2;
      break;
  }
  return priority;
}

symb_st *get_polish(symb_st *input_stack) {
  symb_st *output_stack = NULL;
  symb_st *operation_stack = NULL;
  symb_st *reversed_stack = NULL;
  while (input_stack != NULL) {
    expr last = pop(&input_stack);
    if (last.symb_type == VALUE || last.symb_type == UNKNOWN_X) {
      push(&output_stack, last);
    } else if (last.symb_type == FUNCTION) {
      push(&operation_stack, last);
    } else if (last.symb_type == OPERATION && last.priority >= 0) {
      if (operation_stack != NULL) {
        while (operation_stack != NULL &&
               operation_stack->value.priority >= last.priority) {
          push(&output_stack, pop(&operation_stack));
        }
        push(&operation_stack, last);
      } else {
        push(&operation_stack, last);
      }
    } else if (last.operation == '(') {
      push(&operation_stack, last);
    } else if (last.operation == ')') {
      if (operation_stack != NULL) {
        while (operation_stack != NULL &&
               operation_stack->value.operation != '(') {
          push(&output_stack, pop(&operation_stack));
        }
        if (operation_stack != NULL &&
            operation_stack->value.operation == '(') {
          pop(&operation_stack);
        }
        if (operation_stack != NULL &&
            operation_stack->value.symb_type == FUNCTION) {
          push(&output_stack, pop(&operation_stack));
        }
      }
    }
  }
  while (operation_stack != NULL) {
    if (operation_stack->value.operation == '(') {
      printf("MISSING BRACKET\n");
    }
    push(&output_stack, pop(&operation_stack));
  }
  reversed_stack = reverse(output_stack);
  return reversed_stack;
}
