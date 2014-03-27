test: test.o sasl.o
	gcc -o $@ -lm test.o sasl.o base64.o

sasl.o: base64.o
