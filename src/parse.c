#include "parse.h"
#include "cradle.h"
#include "dops.h"
#include "math.h"
#include "function.h"
#include "stack.h"
#include <ctype.h>

// <identifier> ::= <variable> | <function>
void identifier() {
  char name = get_name();
  if (look.c == '(') {
    match('(');
    match(')');
    // Since there is not a def function mechanism yet, just treat as a return of zero.
    emit_constant_to_d(0);
    emit_push_d_to_stack();
  } else {
    // Set address of variable 
    tab_emit("@");
    char var[2];
    var[0] = name;
    var[1] = 0;
    emit_ln(var);
    // Push value at address onto stack
    tab_emit_ln("D=M");
    emit_push_d_to_stack();
  }
}

// <factor> ::= <number> | (<expression>) | <identifier>
void factor() {
  if (look.c == '(') {
    match('(');
    expression();
    match(')');
  } else if (isalpha(look.c)) {
    identifier();
  } else {
    // Push single digit onto stack
    tab_emit("@");
    char num[2];
    num[0] = get_num();
    num[1] = 0;
    emit_ln(num);
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

// <assignment> ::= <variable>=<expression>
void assignment() {
  char name;
  name = get_name();
  if (look.c == '=') {
    match('=');
    expression();
    // Get return value
    emit_peek_stack_to_d(1);
    // Set address of lhs variable 
    tab_emit("@");
    char var[2];
    var[0] = name;
    var[1] = 0;
    emit_ln(var);
    // Set lhs variable
    tab_emit_ln("M=D");
    // If at EOL, remove return value from stack.
    if (look.c == '\n') {
      emit_pop_stack();
    }
  }
}
