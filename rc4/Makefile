CC = aarch64-poky-linux-gcc
CFLAGS = -O2 -Wall -Wextra -fPIC

INCDIR = /usr/include/
LIBDIR = /usr/lib/
LIB = librc4.so

all: librc4 example

librc4: rc4.c rc4.h
	$(CC) $(CFLAGS) -I. -shared rc4.c -o $(LIB)

install: $(LIB)
	cp rc4.h $(INCDIR)
	cp $(LIB) $(LIBDIR)
	chmod 644 $(INCDIR)/rc4.h
	chmod 755 $(LIBDIR)/$(LIB)

example: install
	$(CC) $(CFLAGS) example.c -lrc4 -o example

clean:
	rm -f *.so example

.PHONY: all install example clean
