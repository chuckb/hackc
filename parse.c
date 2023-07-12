#include "parse.h"
#include "cradle.h"
#include "dops.h"
#include "math.h"
#include "function.h"

void factor() {
  if (look.c == '(') {
    match('(');
    expression();
    match(')');
  } else {
    // Push single digit onto stack
    tab_emit("@");
    char num[2];
    num[0] = get_num();
    num[1] = 0;
    emit(num);
    emit("\n");
    tab_emit_ln("D=A");
    emit_push_d_to_stack();
  }
}

void multiply() {
  match('*');
  factor();
  emit_call_mult16();
}

void divide() {
  match('/');
  factor();
  emit_call_div16();
}

void add() {
  match('+');
  term();
  emit_call_add16();
}

void subtract() {
  match('-');
  term();
  // Negate y
  emit_pop_stack_to_d();
  emit_negate_d();
  emit_push_d_to_stack();
  emit_call_add16();
}

void term() {
  factor();
  while(look.c == '*' || look.c == '/') {
    switch (look.c) {
      case '*':
        multiply();
        break;
      case '/':
        divide();
        break;
      default:
        expected("Multop");
    }
  }
}

void expression() {
  if (is_add_op(look.c)) {
    // Push a zero to the stack (deal with unary values)
    emit_constant_to_d(0);
    emit_push_d_to_stack();
  } else {
    term();
  }
  while(is_add_op(look.c)) {
    switch (look.c) {
      case '+':
        add();
        break;
      case '-':
        subtract();
        break;
      default:
        expected("Addop");
    }
  }
}