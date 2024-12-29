CC = gcc
CFLAGS = -Wall
LDFLAGS = -lgpiod

all: blink

blink: blink.c
	$(cc) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f blink