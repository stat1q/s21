#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "s21_grep.h"

int main(int argc, char *argv[]) {
  FILE *file;
  FILE *search_file;
  null_option();
  int argnum = 1;
  int flag_err = 0;
  int flag_sample = 0;
  char SEARCH_STRING[100][MAX_SIZE] = {'\0'};
  char name_search_file[40][1024] = {'\0'};
  int count_files = 0;
  int ecount = 0;
  int fcount = 0;

while (argnum < argc && flag_err == 0) {
  int len = strlen(argv[argnum]);
  if (argv[argnum][0] == '-') {
    char *tmp;
    int count = 1;
    while (count < len) {
      if ((tmp = strchr(OPTION, argv[argnum][count])) != NULL) {
        option_case(*tmp);
        if (*tmp == 'e' || *tmp == 'f') {
          int i = 0;
          int nextsymb = count + 1;
          flag_sample = 1;
          while (argv[argnum][count] != '\0') {
            count++;
            if (argv[argnum][nextsymb] == '\0') {
              flag_sample = 2;
              memset(argv[argnum], '\0', len);
              argnum++;
              }
              if (option.e && flag_sample == 1) {
                SEARCH_STRING[ecount][i] = argv[argnum][count];
                } else if (option.f && flag_sample == 1) {
                  name_search_file[fcount][i] = argv[argnum][count];
                  }
                  i++;
                  }
          if (option.e && flag_sample == 1) ecount++;
          if (option.f && flag_sample == 1) fcount++;
        }
      } else {
        fprintf(stderr, "s21_grep: invalid option -- '%c'\n", argv[argnum][count]);
        flag_err = 1;
        break;
      }
        count++;
    }
    if (flag_sample == 2) {
      int search_len = strlen(argv[argnum]);
      if (option.e) {
        strncpy(SEARCH_STRING[ecount], argv[argnum], search_len);
        ecount++;
        } else if (option.f) {
          strncpy(name_search_file[fcount], argv[argnum], search_len);
          fcount++;
          }
          }
          memset(argv[argnum], '\0', len);
          }
      if (argv[argnum][0] != '\0') {
        count_files++;
      }
      argnum++;
}

  argnum = 1;
  if (flag_err == 0) {
    int i = 0;
    fcount--;
    while (i <= fcount && flag_err != 2) {
      if (search_file = fopen(name_search_file[i], "r")) {
        i++;
        fclose(search_file);
      } else {
        fprintf(stderr, "%s: No such file or directory\n", name_search_file[i]);
        flag_err = 2;
        i++;
      }
    }
    while (argnum < argc) {
      if (flag_sample == 0 && argv[argnum][0] != '\0') {
        int length = strlen(argv[argnum]);
        strncpy(SEARCH_STRING[ecount], argv[argnum], length);
        memset(argv[argnum], '\0', length);
        argnum++;
        count_files--;
        flag_sample = 3;
        }
      char *name_file = argv[argnum];
      if (argv[argnum][0] != '\0') {
        if (file = fopen(name_file, "r")) {
          int i = 0;
          if (option.f) {
            if (flag_err != 2) {
              i = 0;
              int str_count = 0;
              while (i <= fcount) {
                search_file = fopen(name_search_file[i], "r");
                int res_getline = 0;
                char *tmp_str = NULL;
                size_t len = 0;
                int lentmp = 0;
                while ((res_getline = getline(&tmp_str, &len, search_file)) != EOF) {
                  lentmp = strlen(tmp_str);
                   if (tmp_str[strlen(tmp_str) - 1] == '\n') {
                     lentmp--;
                     }
                  strncpy(SEARCH_STRING[str_count], tmp_str, lentmp);
                  str_count++;
                }
                free(tmp_str);
                i++;
              }
               search(file, SEARCH_STRING, name_file, count_files, str_count);
            }
          } else {
            search(file, SEARCH_STRING, name_file, count_files, ecount);
          }
          fclose(file);
        } else if (!option.s) {
          fprintf(stderr, "%s: No such file or directory\n", argv[argnum]);
        }
      }
    argnum++;
    }
  }
  return 0;
}

void search(FILE *file, char search_str[100][MAX_SIZE],
char *name_file, int count_files, int search_str_count) {
  int flag_reg = 0;
  char *tmp_str = NULL;
  int res_getline = 0;
  size_t len = 0;
  int res_regex = 0;
  int cmp = 0;
  int num_str = 1;
  int flag_l = 0;
  int match = 0;
  if (option.v) {
    cmp = REG_NOMATCH;
  }
  if (option.i) {
    flag_reg = REG_ICASE;
  }
  if (option.e) search_str_count--;
  while (((res_getline = getline(&tmp_str, &len, file)) != EOF) && !flag_l) {
    int flag_success = 0;
    int i = 0;
    while (i <= search_str_count && !flag_success) {
    regcomp(&regex, search_str[i], flag_reg);
    if (tmp_str[strlen(tmp_str) - 1] != '\n') {
      tmp_str[strlen(tmp_str)] = '\n';
    }
    if (tmp_str) {
      res_regex = regexec(&regex, tmp_str, 0, NULL, 0);
      if (option.l && !flag_l) {
        if (res_regex == cmp) {
          printf("%s\n", name_file);
           flag_l = 1;
        }
      }
      if (!flag_l) {
        if (res_regex == cmp) {
          if (!option.c) {
            if (!option.h) {
              print_name_file(name_file, count_files);
            }
            if (option.n) {
              printf("%d:", num_str);
            }
            if (!option.o) {
              printf("%s", tmp_str);
               flag_success = 1;
             } else {
              int len = strlen(search_str[search_str_count]);
              int count = 0;
               while (tmp_str[count] != '\0') {
                if (strspn(&tmp_str[count], search_str[i]) > 0) {
                  int i = 0;
                  while (i < len) {
                    printf("%c", tmp_str[count + i]);
                    i++;
                  }
                  count += len - 1;
                  printf("\n");
                }
                count++;
              }
            }
          }
          match++;
        }
      }
    }
       i++;
       }
      num_str++;
      regfree(&regex);
  }
  free(tmp_str);
  if (option.c && !option.l) {
    printf("%d\n", match);
  }
}

void print_name_file(char *name_file, int count_files) {
  if (count_files > 1) {
    printf("%s:", name_file);
  }
}

void option_case(char opt) {
  switch (opt) {
    case 'e':
      option.e = 1;
      break;
    case 'i':
      option.i = 1;
      break;
    case 'v':
      option.v = 1;
      break;
    case 'l':
      option.l = 1;
      break;
    case 'c':
      option.c = 1;
      break;
    case 'n':
      option.n = 1;
      break;
    case 'f':
      option.f = 1;
      break;
    case 'h':
      option.h = 1;
      break;
    case 'o':
      option.o = 1;
      break;
    case 's':
      option.s = 1;
      break;
    }
}

void null_option() {
  option.e = 0;
  option.i = 0;
  option.v = 0;
  option.l = 0;
  option.c = 0;
  option.n = 0;
  option.f = 0;
  option.h = 0;
  option.o = 0;
  option.s = 0;
}
