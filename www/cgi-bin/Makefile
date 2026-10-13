CC = gcc
CFLAGS = -O2 -Wall -I ..

all: adder spin

adder: adder.c
	$(CC) $(CFLAGS) -o adder adder.c

spin: spin.c
	$(CC) $(CFLAGS) -o spin spin.c

clean:
	rm -f adder 
	rm spin
