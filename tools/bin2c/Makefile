CC ?= gcc
CFLAGS ?= -O2 -Wall

all: bin2c

bin2c: bin2c.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f bin2c
