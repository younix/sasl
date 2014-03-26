CFLAGS := -std=c99 -pedantic -Wall -Wextra -g

include Makefile.inc

.PHONY: all clean debug
.SUFFIXES: .o .c

.c.o:
	gcc ${CFLAGS} -c -o $@ $<

clean:
	rm -f *.o test

debug:
	gdb tester tester.core
