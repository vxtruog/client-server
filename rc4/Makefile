CC = aarch64-poky-linux-gcc

CFLAGS = -O2 -Wall -Wextra -fPIC

all: rc4 example

rc4.o: rc4.c rc4.h
	$(CC) $(CFLAGS) -c rc4.c -o rc4.o

rc4: rc4.o
	$(CC) -shared rc4.o -o rc4.so

example.o: example.c rc4.h
	$(CC) $(CFLAGS) -c example.c -o example.o

example: example.o rc4
	$(CC) example.o -L. -l:rc4.so -o example \
		-Wall -Wextra -O2 -Wl,-rpath,'$$ORIGIN'

clean:
	rm -f *.o *.so example

.PHONY: all clean