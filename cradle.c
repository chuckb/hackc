#include "cradle.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

look_t look;

void get_char() {
  look.i = fgetc(stdin);
}

void error(char* message) {
  printf("\n");
  printf("Error: %s.\n", message);
}

void bail(char* message) {
  error(message);
  exit(1);
}

void expected(char* message) {
  printf("\n");
  printf("Error: %s expected.\n", message);
  exit(1);
}

void match(char c) {
  if (look.c == c) {
    get_char();
  } else {
    expected(&c);
  }
}

char get_name() {
  if (isalpha(look.c) == 0) {
    expected("Name");
  }
  char uc;
  uc = toupper(look.c);
  get_char();
  return uc;
}

char get_num() {
  if (isdigit(look.c) == 0) {
    expected("Integer");
  }
  char c;
  c = look.c;
  get_char();
  return c;
}

void emit(char* s) {
  printf("%s", s);
}

void emit_ln(char* s) {
  emit(s);
  printf("\n");
}

void tab_emit(char* s) {
  printf("\t%s", s);
}

void tab_emit_ln(char* s) {
  tab_emit(s);
  printf("\n");
}

int is_add_op(char c) {
  if (c == '+' || c == '-') {
    return -1;
  } else {
    return 0;
  }
}

void tab_emit_constant(int c) {
  if (c < 0 || c > 32767) {
    expected("Constant [0, 32767]");
  }
  // Output the constant
  tab_emit("@");
  char digits[6];
  sprintf(digits, "%d", c);
  emit(digits);
  emit_ln("");
}

void init() {
  get_char();
  // Init the stack pointer
  // Stack grows down
  tab_emit_ln("@256");
  tab_emit_ln("D=A");
  tab_emit_ln("@SP");
  tab_emit_ln("M=D");
}
