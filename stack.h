#ifndef __STACK_H__
#define __STACK_H__

void emit_pop_stack();
void emit_push_stack();
void emit_address_at_stack_offset(int offset);
void emit_move_stack_value(int source_offset, int dest_offset);

#endif