#include "stack.h"
#include "cradle.h"
#include "dops.h"

void emit_pop_stack() {
  // Decrement stack pointer
  tab_emit_ln("@SP");
  tab_emit_ln("M=M-1");
}

void emit_push_stack() {
  // Increment stack pointer
  tab_emit_ln("@SP");
  tab_emit_ln("M=M+1");
}

void emit_address_at_stack_offset(int offset) {
  // Save off existing D so we don't clobber it on the way out
  tab_emit_ln("@R13");
  tab_emit_ln("M=D");
  // Compute offset and store in temp
  tab_emit_constant(offset);
  tab_emit_ln("D=A");
  tab_emit_ln("@SP");
  tab_emit_ln("D=M-D");
  tab_emit_ln("@R14");
  tab_emit_ln("M=D");
  // Restore existing D
  tab_emit_ln("@R13");
  tab_emit_ln("D=M");
  // Set address
  tab_emit_ln("@R14");
  tab_emit_ln("A=M");
}

void emit_move_stack_value(int source_offset, int dest_offset) {
  emit_peek_stack_to_d(source_offset);
  emit_poke_d_to_stack(dest_offset);
}