CC=gcc
CFLAGS=-I.
DEPS = framebuffer.h
OBJ = main.c framebuffer.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pi1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
