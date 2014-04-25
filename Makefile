CC ?= cc
CFLAGS := -std=c99 -pedantic -Wall -Wextra -g

.PHONY: all clean debug
.SUFFIXES: .o .c

test: test.o sasl.o
	$(CC) -o $@ -lm test.o sasl.o base64.o

sasl.o: base64.o
.c.o:
	$(CC) ${CFLAGS} -c -o $@ $<

clean:
	rm -f *.o test

debug:
	gdb tester tester.core
