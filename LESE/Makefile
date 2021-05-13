# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -03 gcc version
CFLAGS  = -g -Wall -O3

default: main

lista.o: Lista.c Lista_publica.h Lista_privado.h
	$(CC) $(CFLAGS) -c Lista.c -o lista.o

main: main.c lista.o
	$(CC) $(CFLAGS) main.c lista.o -o main

run: clean main
	./main

clean:
	rm -f main *.o core a.out *.*~ Makefile~

all: main