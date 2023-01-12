.PHONY: all install uninstall clean dvi dist tests cpplint cppcheck leaks gcov_report rebuild

CC = g++
LDFLAGS =  -Wall -Wextra -Werror -std=c++17

GCOV_FLAG = -fprofile-arcs -ftest-coverage 

TARGET = tests
CFILES= tests.cpp
TESTFILES= tests.cpp token.cpp model.cpp
OFILES=$(CFILES:.cpp=.o)

QDIR= SmartCalc
DDIR= SmartCalc_2.0

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

default: rebuild

rebuild: clean all

check: cpplint cppcheck gcov_report

all: $(TARGET) check

$(TARGET):
	$(CC) $(LDFLAGS) $(GCOV_FLAG) $(TESTFILES) -o $(TARGET) $(LIBFLAGS)
	./$(TARGET)

%.o: %.cpp
	$(CC) -c $(LDFLAGS) $(GCOV_FLAG)  $<

gcov_report: $(TARGET)
	lcov --no-external -t "$(TARGET)" -o $(TARGET).info -c -d ./
	genhtml -o report $(TARGET).info
ifneq ($(OS), Linux)
	open report/index.html
endif

cpplint:
	cp ../materials/linters/.clang-format . 
	cp ../materials/linters/.clang-format qt/ 
	clang-format -i  *.cpp *.h
	clang-format -i qt/calc_v2/*.cpp qt/calc_v2/*.h
	clang-format -n *.cpp *.h
	clang-format -n qt/calc_v2/*.cpp qt/calc_v2/*.h

cppcheck:
	@echo "****** cppcheck start ******"
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --language=c++ --std=c++17 *.h *.cpp
	cppcheck --enable=all --force  --suppress=unusedFunction --suppress=missingInclude --suppress=unknownMacro --suppress=unusedStructMember --suppress=unmatchedSuppression --language=c++ --std=c++17 qt/calc_v2/*.h qt/calc_v2/*.cpp  	

clean:
	rm -f *.o *.a *.gcno *.gcda *.info a.out $(TARGET)
	rm -rf report/
	rm -f .clang-format
	rm -f qt/.clang-format
	rm -rf build*
	rm -rf manual/

leaks:
ifeq ($(OS), Linux)
	CK_FORK=no valgrind  --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TARGET)
else
	CK_FORK=no leaks -atExit -- ./$(TARGET)
endif

install:
	mkdir $(QDIR)
	cd $(QDIR); qmake ../qt/calc_v2/calc_v2.pro
	cd $(QDIR); make
	cd $(QDIR); make clean
ifneq ($(OS), Linux)
	open SmartCalc 
endif	

uninstall: 
	rm -r $(QDIR)

dist:
	mkdir $(DDIR)
	cp *.cpp *.h Makefile $(DDIR)	
	cp -R qt $(DDIR)
	tar --totals -cvf $(DDIR).tar $(DDIR)
	rm -rf $(DDIR)

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html