#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define MAX_SIZE 8192
#define OPTION "eivlcnfhos"

regex_t regex;
struct options {
    int e;
    int i;
    int v;
    int l;
    int c;
    int n;
    int f;
    int h;
    int o;
    int s;
} option;

void option_case(char opt);
void null_option();
void search(FILE *file, char search_str[100][MAX_SIZE],
char *name_file, int count_files, int search_str_count);
void print_name_file(char *name_file, int count_files);

#endif  // SRC_GREP_S21_GREP_H_
