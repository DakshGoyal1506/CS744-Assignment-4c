CC = gcc
CFLAGS = -I. -pthread
LDFLAGS = -lm

all: cflask

cflask: cflask.c functions.c url_map.c libcivetweb.a
	$(CC) $(CFLAGS) cflask.c functions.c url_map.c libcivetweb.a -o cflask $(LDFLAGS)

clean:
	rm -f cflask