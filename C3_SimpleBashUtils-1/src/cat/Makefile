CC=gcc
CAR=ar
CRANLIB=ranlib
FLAGS =-std=c11

.PHONY: all clean rebuild test check
default: all

all: clean s21_cat check test
	
s21_cat: s21_cat.c
	$(CC) $(FLAGS) s21_cat.c -o s21_cat

clean:
	rm -rf *.o *.out *.a
test:
	bash test_cat.sh

rebuild:
	$(MAKE) clean
	$(MAKE) all

check:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	cppcheck ../../src/
	CK_FORK=no leaks --atExit -- ./s21_cat
