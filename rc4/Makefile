CC = aarch64-poky-linux-gcc
CFLAGS = -O2 -Wall -Wextra -fPIC

INCDIR = /usr/include/
LIBDIR = /usr/lib/
LIB = librc4.so

all: $(LIB) example

$(LIB): rc4.c rc4.h
	$(CC) $(CFLAGS) -shared rc4.c -o $(LIB)

install: $(LIB)
	cp rc4.h $(INCDIR)
	cp $(LIB) $(LIBDIR)

example:
	$(CC) $(CFLAGS) example.c -lrc4 -o example

clean:
	rm -f *.so example

.PHONY: all install example clean
