CC=gcc
CFLAGS=-I.
DEPS = cradle.h
OBJ = cradle.o main.o 
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
