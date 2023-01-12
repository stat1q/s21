.PHONY: all install uninstall clean dvi dist tests cpplint cppcheck leaks gcov_report rebuild

CC = g++
LDFLAGS = -std=c++17 -Wall -Wextra -Werror
GCOV_FLAG = -fprofile-arcs -ftest-coverage 
TARGET= tests
CFILES= tests.cpp
TESTFILES= tests.cpp Model/parser.cpp Model/vertex.cpp Model/normal.cpp Model/texture.cpp
OFILES=$(CFILES:.cpp=.o)
QDIR= 3DViewer
DDIR= 3DViewer_v2.1_dist

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

default: rebuild

rebuild: clean all

check: cpplint cppcheck gcov_report

all: $(TARGET)
# check

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
	cp ../materials/linters/.clang-format Controller/
	cp ../materials/linters/.clang-format Model/ 
	cp ../materials/linters/.clang-format View/ 
	clang-format -i  *.cpp *.h
	clang-format -i Controller/*.cpp Controller/*.h
	clang-format -i Model/*.cpp Model/*.h
	clang-format -i View/*.cpp View/*.h
	clang-format -n *.cpp *.h
	clang-format -n Model/*.cpp Model/*.h
	clang-format -n Controller/*.cpp Controller/*.h
	clang-format -n View/*.cpp View/*.h

cppcheck:
	@echo "****** cppcheck start ******"
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unmatchedSuppression  --suppress=unusedFunction --suppress=cppcheckError --language=c++ --std=c++17 Model/*.h Model/*.cpp

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.tar $(TARGET)
	rm -rf report/
	rm -f .clang-format
	rm -f Controller/.clang-format
	rm -f Model/.clang-format
	rm -f View/.clang-format
	rm -rf build*
	rm -rf etc/manual/
	rm -rf $(DDIR)

leaks:
ifeq ($(OS), Linux)
	CK_FORK=no valgrind  --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TARGET)
else
	CK_FORK=no leaks -atExit -- ./$(TARGET)
endif

install:
	mkdir $(QDIR)
	cd $(QDIR); qmake ../3DViewer_v2.pro
	cd $(QDIR); make
	cd $(QDIR); make clean
ifneq ($(OS), Linux)
	open 3DViewer
endif	

uninstall: 
	rm -r $(QDIR)

dist:	install
	mkdir -p $(DDIR)
	cp -r $(QDIR)/ $(DDIR)/
	tar --totals -cvf $(DDIR).tar $(DDIR)
	rm -rf $(DDIR)


dvi:
	cd etc/; makeinfo manual.texi --html
	open etc/manual/index.html