#include "cradle.h"
#include "parse.h"
#include "math.h"
#include "function.h"
#include "dops.h"
#include <stdio.h>

void emit_globals() {
  // Bitmask array
  for (int i = 1; i < 16385; i=i*2) {
    // Get constant into D
    emit_constant_to_d(i);
    // Define a label
    char symbol[14];
    sprintf(symbol, "@bitmask%d", i);
    tab_emit_ln(symbol);
    // Update memory with constant
    tab_emit_ln("M=D");
  }
  // Cannot specify a negative constant via assembler.
  // Largest possible 16-bit signed int is 32767.
  // But we need binary mask 0b1000000000000000, which is -32768.
  // Put in largest positive int to D and add 1.
  emit_constant_to_d(32767);
  tab_emit_ln("D=D+1");
  tab_emit_ln("@bitmask32768");
    // Update memory with constant
  tab_emit_ln("M=D");
}

int main (void) {
  init();
  emit_globals();

/*
  tab_emit_constant(9);
  tab_emit_ln("D=A");
  emit_push_d_to_stack(); 
  tab_emit_constant(3);
  tab_emit_ln("D=A");
  emit_push_d_to_stack(); 
  emit_call("bit16", 1);

  emit_constant_to_d(12);
  emit_push_d_to_stack(); 
  emit_constant_to_d(30);
  emit_push_d_to_stack(); 
  emit_call_mult16();
*/
  expression();
  emit_spin("end");
  emit_add16_function();
  emit_bit16_function();
  emit_lshift16_function();
  emit_mult16_function();
  emit_div16_function();
}