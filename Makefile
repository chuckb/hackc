CC=gcc
CFLAGS=-I. -g
DEPS = cradle.h parse.h dops.h stack.h function.h math.h
OBJ = cradle.o parse.o dops.o stack.o function.o math.o main.o 
RM      = rm -f

default: all

all: hackc

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hackc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean veryclean:
	$(RM) hackc
	$(RM) *.o
