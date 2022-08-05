#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "s21_cat.h"

int main(int argc, char *argv[]) {
  char GPU[6][20] = {"--show-all", \
"--number-nonblank", \
"--show-ends", \
"--number", \
"--squeeze-blank", \
"--show-nonprinting"};
    FILE *file;
    to_null();
    int argnum = 1;
    int GPU_SUCESS = 0;
    int flag_err = 0;
    int flag_file = 0;

while (argnum < argc && flag_err == 0) {
  int len = strlen(argv[argnum]);
    if ((argv[argnum][0] == '-') && (flag_file == 0)) {
    if (argv[argnum][1] == '-') {
      int i = 0;
      while (i < 6) {
        if (strcmp(argv[argnum], "--show-all") == 0) option_case('A');
        if (strcmp(argv[argnum], "--number-nonblank") == 0) option_case('b');
        if (strcmp(argv[argnum], "--show-ends") == 0) option_case('E');
        if (strcmp(argv[argnum], "--number") == 0) option_case('n');
        if (strcmp(argv[argnum], "--squeeze-blank") == 0) option_case('s');
        if (strcmp(argv[argnum], "--show-nonprinting") == 0) option_case('v');
        if (strcmp(argv[argnum], GPU[i]) == 0) {
            GPU_SUCESS = 1;
            break;
         }
        i++;
      }
      if (!GPU_SUCESS) {
         flag_err = 2;
             fprintf(stderr, "s21_cat: unrecognized option '%s'\n", argv[argnum]);
      }
    } else {
            char *tmp;
            int count = 1;
         while (count < len) {
            if ((tmp = strchr(OPTION, argv[argnum][count])) != NULL) {
                option_case(*tmp);
            } else {
                fprintf(stderr, "s21_cat: invalid option -- '%c'\n", argv[argnum][count]);
                flag_err = 1;
                break;
            }
            count++;
         }
    }
    memset(argv[argnum], '\0', len);
    } else {
      flag_file = 1;
    }
    argnum++;
    GPU_SUCESS = 0;
    }
    argnum = 1;
    int number = 2;
    if (flag_err == 0) {
      while (argnum < argc) {
        char *name_file = argv[argnum];
        if (argv[argnum][0] != '\0') {
          if (file = fopen(name_file, "r")) {
            number = printfile(file, number);
            number++;
            fclose(file);
            } else {
              fprintf(stderr, "%s: No such file or directory\n", argv[argnum]);
              }
              }
    argnum++;
  }
  }
    return 0;
}

int printfile(FILE *file, int number) {
    char ch = getc(file);
    char next_ch = '\0';
      if (ch != EOF) {
        if (option.b && ch == '\n') number = 1;
        if (((option.n && !option.b) || (option.b && ch != '\n'))) printf("%6d\t", number - 1);
        if (option.E && ch == '\n') printf("$");
        if (option.T && ch == '\t') printf("^I");
     while ((next_ch = getc(file)) != EOF) {
          next_ch = opt_s(file, ch, next_ch);
          printf("%c", ch);
          number = opt_n_b(ch, next_ch, number);
          next_ch = opt_T(file, next_ch);
          opt_E(next_ch);
          ch = next_ch;
     }
     printf("%c", ch);
  }
  return number;
}

char opt_s(FILE *file, char ch, char next_ch) {
  if (option.s) {
    int flag_first = 0;
    if (ch == '\n' && next_ch == '\n') {
       long int i = ftell(file);
      if (i == 2) {
        flag_first = 1;
      }
    while (next_ch == '\n') {
      i = ftell(file);
      next_ch = getc(file);
  }
    if (!flag_first) {
       fseek(file, i - 1, SEEK_SET);
        next_ch = getc(file);
    }
}
}
return next_ch;
}

int opt_n_b(char ch, char next_ch, int number) {
  if (option.b) {
      if (ch == '\n' && next_ch != '\n') {
        printf("%6d\t", number);
      number++;
      }
  } else if (option.n && !option.b) {
  if (ch == '\n') {
    printf("%6d\t", number);
    number++;
  }
  }
  return number;
}

void opt_E(char next_ch) {
  if (option.E && next_ch == '\n') {
    printf("$");
  }
}

char opt_T(FILE *file, char next_ch) {
  if (option.T && next_ch == '\t') {
    printf("^I");
    next_ch = getc(file);
  }
  return next_ch;
}

void option_case(char opt) {
    switch (opt) {
        case 'b':
          option.n = 1;
          option.b = 1;
          break;
        case 'e':
          option.E = 1;
          option.v = 1;
          break;
        case 'n':
          option.n = 1;
          break;
        case 's':
          option.s = 1;
          break;
        case 't':
          option.T = 1;
          option.v = 1;
          break;
        case 'v':
          option.v = 1;
          break;
        case 'A':
          option.v = 1;
          option.E = 1;
          option.T = 1;
          break;
        case 'E':
          option.E = 1;
          break;
        case 'T':
          option.T = 1;
          break;
        case 'u':
          break;
    }
}

void to_null() {
    option.b = 0;
    option.E = 0;
    option.n = 0;
    option.s = 0;
    option.T = 0;
    option.v = 0;
}
