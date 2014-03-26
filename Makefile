CFLAGS=-std=c99 -pedantic -Wall -Wextra -g

.PHONY: all clean debug
all: sasl.o test

test: test.o sasl.o base64.o
	gcc -o $@ -lm test.o sasl.o base64.o

clean:
	rm -f *.o test
debug:
	gdb tester tester.core

.SUFFIXES: .o .c
.c.o:
	gcc ${CFLAGS} -c -o $@ $<

sasl.o: base64.o
