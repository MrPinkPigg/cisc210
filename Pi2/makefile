CC=gcc
CFLAGS=-I. -lsense -lm
OBJ = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pi2: $(OBJ)
$(CC) -o $@ $^ $(CFLAGS)