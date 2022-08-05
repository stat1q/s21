#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define OPTION "AbeEnstTuv"

struct options {
    int b;  // -number_nonblank
    int E;  // -show_ends
    int n;  // -number
    int s;  // -squeeze_blank
    int T;  // -show_tabs
    int v;  // -show_nonprinting
} option;

void option_case(char opt);
void to_null();
int printfile(FILE *file, int number);
char opt_s(FILE *file, char ch, char next_ch);
int opt_n_b(char ch, char next_ch, int number);
void opt_E(char next_ch);
char opt_T(FILE *file, char next_ch);

#endif  // SRC_CAT_S21_CAT_H_
