GCC = g++ -std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest
LINUX = -lsubunit -lrt -lpthread -lm
DEBUG = -fsanitize=address
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
GCOV_KEEP = --keep-going
GCOV_ERR = --ignore-errors inconsistent
OS = $(shell uname -s)

FULL_VAL_LEAK_CHECK = --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck --show-reachable=yes

TEST_SRC = all_tests/*.cc
OBJ = $(SRC:.cc=.o)

.PHONY: all test valgrind gcov_report clang clean

ifeq ($(OS), Linux)
	LIBS += -lgmock -pthread
endif

all: clean test

test: clean
	$(GCC) $(TEST_SRC) -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure

# Только для линукс
valgrind_linux: clean
	$(GCC) $(TEST_SRC) -o test $(LIBS) $(LINUX)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

docker_build:
	docker build . -t s21_containers
	docker container create -v $(PWD):/usr/src --name s21_container_check s21_containers

docker_start:
	docker start -a s21_container_check

valgrind: test
	valgrind $(FULL_VAL_LEAK_CHECK) ./test


gcov_report: clean
	$(GCC) --coverage $(TEST_SRC) -o test $(LIBS)
	chmod +x test
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info

	open ./report/index.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i all_tests/*.cc
	clang-format -style=Google -i *.h
	clang-format -style=Google -i containers/*.h
	clang-format -style=Google -i containers/tree/*.h
	clang-format -style=Google -n all_tests/*.cc
	clang-format -style=Google -n *.h
	clang-format -style=Google -n containers/*.h
	rm .clang-format

clean:
	rm -rf a.out*
	rm -rf gtest.*o
	rm -rf report
	rm -rf test*
	rm -rf *.gcda
	rm -rf *.dSYM
	rm -rf *.gcno
	rm -rf RESULT_VALGRIND.txt
	rm -rf main
