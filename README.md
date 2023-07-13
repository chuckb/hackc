# C Compiler for Hack CPU Computer

## Description

This project is an attempt to build a C compiler for the Hack CPU-based computer described in the [Elements of Computing Systems][ElementsOfComputingSystems]. It will compile into hack assembly language.

It will start out as a C implementation of the Turbo Pascal program presented by Jack Crenshaw [Let's Build A Compiler][LetsBuildACompiler].

A tag in github will be created at the conclusion of each part of Crenshaw's tutorial. I will diverge from his KISS language parsing in order to parse C instead, but I do intend to follow the tutorial progression. At some point, I will branch off and attempt to parse the [C BNF][CBNF] and/or perhaps a BASIC dialect.

## Requirements
- gcc
- make
- [Nand2Tetris Software][Nand2Tetris] CPUEmulator 

## Building
- `make`
- Clean with `make clean`.

## Testing
- Set Makefile location of CPUEmulator in EMU variable
- `make test`

[ElementsOfComputingSystems]: https://mitpress.mit.edu/9780262539807/the-elements-of-computing-systems/
[LetsBuildACompiler]: https://compilers.iecc.com/crenshaw/
[CBNF]: https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm
[Nand2Tetris]: https://www.nand2tetris.org/