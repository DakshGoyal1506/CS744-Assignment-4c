CC = gcc
CFLAGS = -I. -pthread

all: cflask

cflask: cflask.c functions.c url_map.c
	$(CC) $(CFLAGS) cflask.c functions.c url_map.c libcivetweb.a -o cflask

clean:
	rm -f cflask