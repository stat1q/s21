#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER "0123456789."
#define SIGN "+-*/^()"
#define TRIGFUNC "sincotaqrlg"

#define ERROR 1
#define STR_MAX 256

typedef enum {
  VALUE = 0,
  OPERATION = 1,
  FUNCTION = 2,
  UNKNOWN_X = 3
} symbol_type;

typedef struct expr {
  double value;
  char operation;
  int priority;
  symbol_type symb_type;
} expr;

typedef struct symbol_stack {
  expr value;
  struct symbol_stack *next;
} symb_st;

char check_trigfunc(char *func, int *flag_err);
void parse_number(char *str, int *i, int flag_unary, symb_st **head);
int parse_operation(const char *str, int *i, int *bracket, symb_st **head,
                    int flag_err);
int parse_function(char *str, int *i, symb_st **head, int flag_err,
                   int flag_unary);
void parse_x(int *i, symb_st **head, int flag_unary);
void parse_mod(int *i, symb_st **head);
int parser(symb_st **head, char *str);

void add_toend(symb_st **head, expr value);
expr pop(symb_st **head);
void push(symb_st **head, expr value);
symb_st *reverse(symb_st *input_stack);
symb_st *free_stack(symb_st **head);
void printStack(const symb_st *head);

int get_priority(char oper);
symb_st *get_polish(symb_st *input_stack);
double expression_calc(symb_st *input_stack, double x, int *flag_err);
double get_result(char *str, double x);

#endif  // SRC_PARSER_H_
