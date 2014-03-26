CFLAGS=-std=c99 -pedantic -Wall -Wextra -g

.PHONY: all clean debug
.SUFFIXES: .o .c

all: sasl.o test
sasl.o: base64.o

test: test.o sasl.o base64.o
	gcc -o $@ -lm test.o sasl.o base64.o

.c.o:
	gcc ${CFLAGS} -c -o $@ $<

clean:
	rm -f *.o test

debug:
	gdb tester tester.core
