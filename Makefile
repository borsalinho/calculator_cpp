.PHONY: test

FLAGS = -Wall -Werror -Wextra -std=c++17
OS := $(shell uname)
CHECK_FLAGS = -lgtest -lgmock -pthread

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	MEM_CHECK = valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full
else
	OPEN_CMD = open
	MEM_CHECK = leaks --atExit -- ./test
endif

all: clean install

install:
	make clean
	mkdir build
ifeq ($(OS), Linux)
	cd qt && qmake6 && make && make clean && rm Makefile && mv  myCalc ../build/	
else
	cd qt && qmake && make && make clean && rm Makefile && mv myCalc.app/Contents/MacOS/myCalc ../build/
endif

uninstall:
	rm -rf build

clean:
	rm -rf a.out test *.o *.a report report.info gcov *.tgz *.gcno *gcda *.gcov .*.stash
	cd qt && rm -rf *.o *.app

dvi:
	open index.html

dist:
	tar cvzf archive_myCalc.tgz build/ 

test:
	g++ $(FLAGS) ./model/calculate/calcCalculate.cc ./model/calculate/calcCalculate.h ./model/validator/calcValidator.cc ./model/validator/calcValidator.h ./model/parser/calcParser.cc ./model/parser/calcParser.h ./model/common/calcCommon.h ./model/calcModel.cc ./model/calcModel.h test.cc -o test $(CHECK_FLAGS)
	./test

gcov_report:
	g++ --coverage -lgtest -lgmock -pthread ./model/calculate/calcCalculate.cc ./model/calculate/calcCalculate.h ./model/validator/calcValidator.cc ./model/validator/calcValidator.h ./model/parser/calcParser.cc ./model/parser/calcParser.h ./model/common/calcCommon.h ./model/calcModel.cc ./model/calcModel.h test.cc -o ./gcov
	./gcov
	lcov -t "./gcov" -o report.info --no-external -ignore-errors mismatch -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov

leaks:
	make test
	CK_FORK=no $(MEM_CHECK) ./test

open:
	open build/myCalc

clang:
	cp ../../materials/linters/.clang-format ./
	clang-format -n *.cpp controller/*.* model/*.* view/*.* plot/*.*
	rm .clang-format

clang_check:
	cp ../../materials/linters/.clang-format ./
	clang-format -i *.cpp controller/*.* model/*.* view/*.* plot/*.*
	rm .clang-format	
	
main:
	g++ -Wall -Werror -Wextra -std=c++17 ./model/calcModel.cc ./model/calcModel.h main2.cc
	./a.out