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
  return look.c;
}

void tab_emit(char* s) {
  printf("\t%s", s);
}

void tab_emit_ln(char* s) {
  tab_emit(s);
  printf("\n");
}

void init() {
  get_char();
}