CC = gcc -std=c17 -I../
BUILD_FLAGS = -O3 -w -s
DEBUG_FLAGS = -Wall -g -DDEBUG
exe = test.out

$(exe): ../*.c test.c
	$(CC) $(BUILD_FLAGS) ../*.c test.c -o $(exe)

debug: ../*.c
	$(CC) $(DEBUG_FLAGS) ../*.c test.c -o $(exe)

clean:
	rm -f *.o $(exe)
