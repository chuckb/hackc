#include "stack.h"
#include "cradle.h"
#include "dops.h"

void emit_push_d_to_stack() {
  // Copy D to location pointed to be SP
  tab_emit_ln("@SP");
  emit_set_value_from_d();
  // Increment stack pointer
  emit_push_stack();
}

void emit_pop_stack_to_d() {
  // Decrement stack pointer
  emit_pop_stack();
  // Copy value pointed to by SP to D
  emit_dereference_to_d();
}

void emit_dereference_to_d() {
  tab_emit_ln("A=M");
  tab_emit_ln("D=M");
}

void emit_set_value_from_d() {
  tab_emit_ln("A=M");
  tab_emit_ln("M=D");
}

void emit_constant_to_d(int c) {
  tab_emit_constant(c);
  tab_emit_ln("D=A");
}

void emit_negate_d() {
  // Take twos compliment
  tab_emit_ln("D=!D");
  tab_emit_ln("D=D+1");
}

void emit_peek_stack_to_d(int offset) {
  // Get offset into D
  tab_emit_constant(offset);
  tab_emit_ln("D=A");
  // Set address to sum value at stack pointer minus offset
  tab_emit_ln("@SP");
  tab_emit_ln("A=M-D");
  // Get value at address
  tab_emit_ln("D=M");
}

void emit_poke_d_to_stack(int offset) {
  // Save off D to a temp var
  tab_emit_ln("@R13");
  tab_emit_ln("M=D");
  // Get offset into D
  tab_emit_constant(offset);
  tab_emit_ln("D=A");
  // Compute address to poke value at stack pointer minus offset
  tab_emit_ln("@SP");
  tab_emit_ln("D=M-D");
  // Save off stack address to a temp var
  tab_emit_ln("@R14");
  tab_emit_ln("M=D");
  // Get update value into D
  tab_emit_ln("@R13");
  tab_emit_ln("D=M");
  // Get stack address and position to value of address
  tab_emit_ln("@R14");
  tab_emit_ln("A=M");
  // Finally update stack with d
  tab_emit_ln("M=D");
}