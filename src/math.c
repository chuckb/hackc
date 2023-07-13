#include "cradle.h"
#include "stack.h"
#include "dops.h"
#include "math.h"
#include "function.h"

void emit_call_add16() {
  emit_call("add16", 0);
}

void emit_add16_function() {
  // stack
  // args
  // 16 bit x
  static const int X_OFFSET = 3;
  // 16 bit y
  static const int Y_OFFSET = 2;
  // locals
  static const int RETURN_ADDRESS = 1;

  emit_ln("(add16)");
  // Get y value into D
  emit_peek_stack_to_d(Y_OFFSET);
  // Position to x - relies on peek positioning A to Y upon leaving
  tab_emit_ln("A=A-1");
  // Do math in place into x
  tab_emit_ln("M=D+M");
  // Get the return address into D
  emit_pop_stack_to_d();
  // Pop y
  emit_pop_stack();
  // Return
  tab_emit_ln("A=D");
  tab_emit_ln("0;JMP");
}

void emit_call_lshift16() {
  emit_call("lshift16", 1);
}

void emit_lshift16_function() {
  // stack
  // args
  // 16 bit x
  static const int X_OFFSET = 3;
  // locals
  static const int RETURN_ADDRESS = 2;
  // 16 bit temp
  static const int TEMP_OFFSET = 1;

  emit_ln("(lshift16)");
  // Get val to shift into D
  emit_peek_stack_to_d(X_OFFSET);
  // Set address to last local variable
  tab_emit_ln("@SP");
  tab_emit_ln("A=M-1");
  // Init D into temp
  tab_emit_ln("M=D+M");
  // Double temp for shift
  tab_emit_ln("MD=D+M");
  // Put shifted value into X
  emit_poke_d_to_stack(X_OFFSET);
  // Pop temp
  emit_pop_stack();
  // Get the return address into D
  emit_pop_stack_to_d();
  // Return
  tab_emit_ln("A=D");
  tab_emit_ln("0;JMP");
}

void emit_call_bit16() {
  emit_call("bit16", 1);
}

void emit_bit16_function() {
  // stack
  // args
  // 16 bit x
  static const int X_OFFSET = 4;
  // 16 bit j (the bit to get)
  static const int J_OFFSET = 3;
  // locals
  static const int RETURN_ADDRESS = 2;
  // 16 bit mask
  static const int MASK_OFFSET = 1;

  emit_ln("(bit16)");
  // Get bit offset into D
  emit_peek_stack_to_d(J_OFFSET);
  // Position to address within bitmask array of offset desired
  tab_emit_ln("@bitmask1");
  tab_emit_ln("A=D+A");
  // Get mask into D
  tab_emit_ln("D=M");
  // Position to X
  emit_address_at_stack_offset(X_OFFSET);
  // Apply mask to X
  tab_emit_ln("MD=D&M");
  // If zero, move along
  tab_emit_ln("@bit16.if.0");
  tab_emit_ln("D;JEQ");
  // Set X to 1
  emit_address_at_stack_offset(X_OFFSET);
  tab_emit_ln("M=1");
  // Fix up stack for return
  emit_ln("(bit16.if.0)");
  // Pop mask
  emit_pop_stack();
  // Get the return address into D
  emit_pop_stack_to_d();
  // Pop J
  emit_pop_stack();
  // Return
  tab_emit_ln("A=D");
  tab_emit_ln("0;JMP");
}

void emit_call_mult16() {
  emit_call("mult16", 3);
}

void emit_mult16_function() {
  // stack
  // args
  // 16 bit x
  static const int X_OFFSET = 6;
  // 16 bit y
  static const int Y_OFFSET = 5;
  // locals
  static const int RETURN_ADDRESS = 4;
  // 16 bit sum
  static const int SUM_OFFSET = 3;
  // 16 bit shiftedx
  static const int SHIFTEDX_OFFSET = 2;
  // 16 bit j
  static const int J_OFFSET = 1;
  
  emit_ln("(mult16)");
  // Init shiftedx to be x
  emit_move_stack_value(X_OFFSET, SHIFTEDX_OFFSET);
  emit_ln("(mult16.loop)");
  // Get the Jth bit of Y into D
  emit_peek_stack_to_d(Y_OFFSET);
  emit_push_d_to_stack();
  // Don't forget...pushing onto current stack...must account for new values for current offsets
  emit_peek_stack_to_d(J_OFFSET+1);
  emit_push_d_to_stack();
  emit_call_bit16();
  emit_pop_stack_to_d();
  // Test if the bit is 1
  tab_emit_ln("@mult16.j.is.zero");
  tab_emit_ln("D;JEQ");
  // Bit is 1, so...
  // Get shiftedx into D
  emit_peek_stack_to_d(SHIFTEDX_OFFSET);
  // Position to sum
  emit_address_at_stack_offset(SUM_OFFSET);
  // Add shiftedx into sum
  tab_emit_ln("M=D+M");
  emit_ln("(mult16.j.is.zero)");
  // shiftedx = shiftedx << 1
  emit_peek_stack_to_d(SHIFTEDX_OFFSET);
  emit_push_d_to_stack();
  emit_call_lshift16();
  emit_pop_stack_to_d();
  emit_poke_d_to_stack(SHIFTEDX_OFFSET);
  // increment J
  emit_address_at_stack_offset(J_OFFSET);
  tab_emit_ln("M=M+1");
  // Done?
  emit_constant_to_d(15);
  emit_address_at_stack_offset(J_OFFSET);
  tab_emit_ln("D=D-M");
  tab_emit_ln("@mult16.loop");
  tab_emit_ln("D;JNE");
  // Done...put sum into x
  emit_move_stack_value(SUM_OFFSET, X_OFFSET);
  // Fix up stack for return
  // Pop J
  emit_pop_stack();
  // Pop shiftedx
  emit_pop_stack();
  // Pop sum
  emit_pop_stack();
  // Get the return address into D
  emit_pop_stack_to_d();
  // Pop Y
  emit_pop_stack();
  // Return
  tab_emit_ln("A=D");
  tab_emit_ln("0;JMP");
}

void emit_call_div16() {
  emit_call("div16", 2);
}

/*
int div(int x, int y) {
  int remainder = x;
  int quotient = 0;
  while (remainder > 0) {
    remainder = remainder - y;
    if (remainder >= 0)
      quotient++;
  }
  return quotient;
}
*/
void emit_div16_function() {
  // stack
  // args
  // 16 bit x
  static const int X_OFFSET = 5;
  // 16 bit y
  static const int Y_OFFSET = 4;
  // locals
  static const int RETURN_ADDRESS = 3;
  // 16 bit remainder
  static const int REMAINDER_OFFSET = 2;
  // 16 bit quotient
  static const int QUOTIENT_OFFSET = 1;
  
  emit_ln("(div16)");
  // int remainder = x;
  emit_move_stack_value(X_OFFSET, REMAINDER_OFFSET);
  // while (remainder > 0) {
  emit_label("div16.loop.begin");
  emit_peek_stack_to_d(REMAINDER_OFFSET);
  tab_emit_ln("@div16.loop.end");
  tab_emit_ln("D;JLE");
  // remainder = remainder - y;
  emit_peek_stack_to_d(Y_OFFSET);
  emit_address_at_stack_offset(REMAINDER_OFFSET);
  tab_emit_ln("MD=M-D");
  // if (remainder >= 0)
  tab_emit_ln("@div16.loop.begin");
  tab_emit_ln("D;JLT");
  // quotient++;
  emit_address_at_stack_offset(QUOTIENT_OFFSET);
  tab_emit_ln("M=M+1");
  tab_emit_ln("@div16.loop.begin");
  tab_emit_ln("0;JMP");
  // }
  emit_label("div16.loop.end");
  // return quotient;
  emit_move_stack_value(QUOTIENT_OFFSET, X_OFFSET);
  // Fix up stack for return
  // Pop quotient
  emit_pop_stack();
  // Pop remainder
  emit_pop_stack();
  // Get the return address into D
  emit_pop_stack_to_d();
  // Pop Y
  emit_pop_stack();
  // Return
  tab_emit_ln("A=D");
  tab_emit_ln("0;JMP");
}