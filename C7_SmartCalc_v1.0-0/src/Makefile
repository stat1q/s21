CC=gcc
FLAGS =-std=c11
LDFLAGS=-Wall -Wextra -Werror 
LIBFLAGS=`pkg-config --cflags --libs check` -lm
CFILES= test.c stack.c parser.c polish.c calc.c
QDIR= SmartCalc
DDIR= SmartCalc_1.0
.PHONY: install clean all

all: clean install
	./$(QDIR)/s21_calc.app/Contents/MacOS/s21_calc
	
tests:
	$(CC) $(LDFLAGS) $(CFLAGS) $(CFILES) -o calc.o $(LIBFLAGS)
	./calc.o

clean:
	rm -rf *.o *.out *.cfg *.tar report manual

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf *.o *.out *.cfg

leaks:
	$(CC) $(LDFLAGS) $(CFLAGS) $(CFILES) -o calc.o $(LIBFLAGS)
	./calc.o
	CK_FORK=no leaks --atExit -- ./calc.o
	
valgrind_check:  
	$(CC) -O0 -g $(CFILES) -o $(LIBFLAGS)
	valgrind --leak-check=full --track-origins=yes ./parser.o -n file
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./parser.o -n file

install:
	mkdir $(QDIR)
	cd $(QDIR); qmake ../qt/s21_calc/s21_calc.pro
	cd $(QDIR); make
	cd $(QDIR); make clean

uninstall: 
	rm -r $(QDIR)

dist:
	mkdir $(DDIR)
	mkdir $(DDIR)/qt
	cp *.c *.h Makefile $(DDIR)	
	cp -R qt $(DDIR)
	tar --totals -cvf $(DDIR).tar $(DDIR)
	rm -rf $(DDIR)

gcov_report: 
	$(CC) --coverage $(LDFLAGS) $(CFILES) -o calc.o $(LIBFLAGS)
	./calc.o
	lcov -o calc.info -c -d ./ --no-external
	genhtml -o report calc.info
	open report/index.html
	rm -rf *.gcno *.gcda *.info

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html