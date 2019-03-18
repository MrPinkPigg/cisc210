CC=gcc
CFLAGS=-I.
DEPS = game.h
OBJ = main.c game.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab3: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
