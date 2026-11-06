all: rc4 example

rc4: rc4.o
	gcc rc4.o -o rc4.so -O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE

rc4.o: rc4.c
	gcc -c -O2 -Wall rc4.c

example: example.o
	gcc rc4.o example.o -o example -Wall -O2

example.o: example.c
	gcc -c -O2 -Wall example.c

clean:
	rm -f *.o *.so example