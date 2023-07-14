IDIR =./include
SDIR =./src
ODIR =./obj
TDIR =./test

TARGET=$(ODIR)/hackc
CC=gcc
CFLAGS=-I$(IDIR) -g
EMU=/Users/chuck_benedict/Desktop/nand2tetris/tools/CPUEmulator.sh

_DEPS = cradle.h parse.h dops.h stack.h function.h math.h
_OBJ = cradle.o parse.o dops.o stack.o function.o math.o main.o 
_TRES = add.out addmult.out addmultdiv.out negparen.out paren.out singleint.out subtract.out threesum.out unaryminus.out vars.out undecf.out

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
TRES = $(patsubst %,$(TDIR)/%,$(_TRES))

RM = rm -f

default: all

all: $(TARGET)

test: $(TRES)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/%.out: $(TDIR)/%.tst $(TDIR)/%.asm
	$(EMU) $<

$(TDIR)/%.asm: $(TDIR)/%.txt $(TARGET)
	$(TARGET) < $< > $@

.PRECIOUS: $(TDIR)/%.asm

clean veryclean:
	$(RM) $(ODIR)/*
	$(RM) $(TDIR)/*.asm
	$(RM) $(TDIR)/*.out
