#include "parser.h"

char check_trigfunc(char *func, int *flag_err) {
  int i = 0;
  char func_symb = '\0';
  if (func[i] == 'c' && func[i + 1] == 'o' && func[i + 2] == 's') {
    func_symb = 'c';
  } else if (func[i] == 's' && func[i + 1] == 'i' && func[i + 2] == 'n') {
    func_symb = 's';
  } else if (func[i] == 't' && func[i + 1] == 'a' && func[i + 2] == 'n') {
    func_symb = 't';
  } else if (func[i] == 'a' && func[i + 1] == 'c' && func[i + 2] == 'o' &&
             func[i + 3] == 's') {
    func_symb = 'o';
  } else if (func[i] == 'a' && func[i + 1] == 's' && func[i + 2] == 'i' &&
             func[i + 3] == 'n') {
    func_symb = 'i';
  } else if (func[i] == 'a' && func[i + 1] == 't' && func[i + 2] == 'a' &&
             func[i + 3] == 'n') {
    func_symb = 'a';
  } else if (func[i] == 's' && func[i + 1] == 'q' && func[i + 2] == 'r' &&
             func[i + 3] == 't') {
    func_symb = 'q';
  } else if (func[i] == 'l' && func[i + 1] == 'n') {
    func_symb = 'n';
  } else if (func[i] == 'l' && func[i + 1] == 'o' && func[i + 2] == 'g') {
    func_symb = 'g';
  } else {
    printf("non-existent function: %s\n", func);
    *flag_err = ERROR;
  }
  return func_symb;
}

void parse_number(char *str, int *i, int flag_unary, symb_st **head) {
  expr tmp;
  char buff[256] = {"\0"};
  int j = 0;
  if (flag_unary == 1) {
    buff[j] = str[(*i) - 1];
    j++;
  }
  while (strchr(NUMBER, str[*i]) != NULL) {
    buff[j] = str[*i];
    j++;
    (*i)++;
  }
  double res = 0;
  sscanf(buff, "%lf", &res);
  tmp.symb_type = VALUE;
  tmp.value = res;
  tmp.priority = 0;
  tmp.operation = 'd';
  add_toend(head, tmp);
}

int parse_operation(const char *str, int *i, int *bracket, symb_st **head,
                    int flag_err) {
  char sign = 0;
  expr tmp;
  if (str[*i] == '(') (*bracket)++;
  if (str[*i] == ')') (*bracket)--;
  if (*bracket < 0) {
    printf("BRACKET ARE INCORRECTLY PLACED\n");
    flag_err = ERROR;
  }
  sign = str[*i];
  (*i)++;
  tmp.symb_type = OPERATION;
  tmp.operation = sign;
  tmp.value = 0;
  tmp.priority = get_priority(tmp.operation);
  add_toend(head, tmp);
  return flag_err;
}

int parse_function(char *str, int *i, symb_st **head, int flag_err,
                   int flag_unary) {
  char func[256] = {"\0"};
  int k = 0;
  expr tmp;
  if (flag_unary == 1) {
    tmp.symb_type = VALUE;
    tmp.value = -1;
    tmp.priority = 0;
    tmp.operation = '\0';
    add_toend(head, tmp);
    tmp.symb_type = OPERATION;
    tmp.operation = '*';
    tmp.priority = 2;
    add_toend(head, tmp);
  }
  while (strchr(TRIGFUNC, str[*i]) != NULL) {
    func[k] = str[*i];
    (*i)++;
    k++;
  }
  tmp.symb_type = FUNCTION;
  tmp.operation = check_trigfunc(func, &flag_err);
  tmp.priority = 4;
  tmp.value = 0;
  if (str[*i] == '(') {
    add_toend(head, tmp);
  } else {
    flag_err = ERROR;
    printf(
        "MISSING "
        "("
        ": %s\n",
        func);
  }
  return flag_err;
}

void parse_x(int *i, symb_st **head, int flag_unary) {
  expr tmp;
  if (flag_unary == 1) {
    tmp.symb_type = VALUE;
    tmp.value = -1;
    tmp.priority = 0;
    tmp.operation = '\0';
    add_toend(head, tmp);
    tmp.symb_type = OPERATION;
    tmp.operation = '*';
    tmp.priority = 2;
    add_toend(head, tmp);
  }
  tmp.symb_type = UNKNOWN_X;
  tmp.operation = 'x';
  tmp.priority = 0;
  tmp.value = 0;
  add_toend(head, tmp);
  (*i)++;
}

void parse_mod(int *i, symb_st **head) {
  expr tmp;
  (*i) += 3;
  tmp.symb_type = OPERATION;
  tmp.operation = 'm';
  tmp.priority = 3;
  tmp.value = 0;
  add_toend(head, tmp);
}

int parser(symb_st **head, char *str) {
  int len = strlen(str) - 1;
  int i = 0;

  int bracket = 0;
  int flag_err = 0;

  while (i <= len && flag_err == 0) {
    int flag_unary = 0;
    if (strchr(" ", str[i]) != NULL) {
      i++;
    }
    if ((i == 0 && str[i] == '-') ||
        (i > 0 && str[i - 1] == '(' && str[i] == '-')) {
      i++;
      flag_unary = 1;
    }
    if ((i == 0 && str[i] == '+') ||
        (i > 0 && str[i - 1] == '(' && str[i] == '+')) {
      i++;
    }
    if (strchr(NUMBER, str[i]) != NULL) {
      parse_number(str, &i, flag_unary, head);
    } else if (strchr(SIGN, str[i]) != NULL) {
      flag_err = parse_operation(str, &i, &bracket, head, flag_err);
    } else if (strchr(TRIGFUNC, str[i]) != NULL) {
      flag_err = parse_function(str, &i, head, flag_err, flag_unary);
    } else if (strchr("x", str[i]) != NULL) {
      parse_x(&i, head, flag_unary);
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      parse_mod(&i, head);
    } else {
      flag_err = ERROR;
      printf("WRONG EXPRESSION\n");
    }
  }
  if (bracket != 0) {
    printf("BRACKET ARE INCORRECTLY PLACED\n");
    flag_err = ERROR;
  }
  return flag_err;
}
