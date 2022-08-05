.PHONY: all clean test s21_decimal.a check gcov_report valgrind_check
CC=gcc
CFLAGS=-c
LDFLAGS= -Wall -Wextra -Werror

default: clean all

all: s21_decimal.a test  

test: s21_decimal.a
	$(CC)  $(LDFLAGS) test.c s21_decimal.a -o test  `pkg-config --cflags --libs check`
	./test

s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a s21_decimal.o
	ranlib $@
	cp $@ lib$@
	ranlib lib$@

s21_decimal.o: s21_decimal.c 
	$(CC) $(LDFLAGS) $(CFLAGS) -o s21_decimal.o s21_decimal.c

clean:
	rm -rf test *.a *.o *.out *.cfg fizz *.gc* *.info report CPPLINT.cfg

rebuild: clean all

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck *.h *.c
	CK_FORK=no leaks --atExit -- ./test

gcov_report: 
	$(CC) --coverage $(LDFLAGS) test.c s21_decimal.c -o test `pkg-config --cflags --libs check`
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

valgrind_check:
	gcc -O0 -g  test.c s21_decimal.c -o test `pkg-config --cflags --libs check`
	valgrind --leak-check=full --track-origins=yes ./test -n file
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./test -n file
