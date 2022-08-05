CC=gcc
CAR=ar
CRANLIB=ranlib
FLAGS =-std=c11

.PHONY: all clean rebuild test check
default: all

all: clean s21_grep check test
	
s21_grep: s21_grep.c
	$(CC) $(FLAGS1) s21_grep.c -o s21_grep

clean:
	rm -rf *.o *.out *.a
test:
	bash test_grep.sh

rebuild:
	$(MAKE) clean
	$(MAKE) all

check:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	cppcheck ../../src/
	CK_FORK=no leaks --atExit -- ./s21_grep