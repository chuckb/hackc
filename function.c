#include "function.h"
#include "stack.h"
#include "cradle.h"
#include "dops.h"
#include <stdio.h>

void emit_function(char * name, int local_ct) {
  emit_label(name);
  for(int i = 0; i < local_ct; i++) {
    tab_emit_ln("D=0");
    emit_push_d_to_stack();
  }
}

void emit_label(char * name) {
  emit("(");
  emit(name);
  emit_ln(")");
}

void emit_goto(char * label) {
  // Unconditional jump to address represented by label
  tab_emit("@");
  emit_ln(label);
  tab_emit_ln("0;JMP");
}

void emit_call(char * name, int arg_ct) {
  static int counter = 0;
  char ret_address_label[10];
  sprintf(ret_address_label, "R_%d", counter++);
  // Push return address to stack
  tab_emit("@");
  emit_ln(ret_address_label);
  tab_emit_ln("D=A");
  emit_push_d_to_stack();
  for(int i = 0; i < arg_ct; i++) {
    tab_emit_ln("D=0");
    emit_push_d_to_stack();
  }
  // Jump
  emit_goto(name);
  // Add label for return from jump
  emit_label(ret_address_label);
}

void emit_spin(char * label) {
  emit_label(label);
  emit_goto(label);
}
