CC = gcc -std=c17 -I../
BUILD_FLAGS = -O3 -w -s
DEBUG_FLAGS = -Wall -g -DDEBUG
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
exe = test.out

$(exe): ../*.c test.c
	$(CC) $(BUILD_FLAGS) ../*.c test.c -o $(exe)

debug: ../*.c test.c
	$(CC) $(DEBUG_FLAGS) ../*.c test.c -o $(exe)

coverage: ../*.c test.c
	$(CC) $(COVERAGE_FLAGS) ../*.c test.c -o $(exe)

check:
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction -I../ ../

clean:
	rm -f *.o *.out *.gcno *.gcov *.gcda
