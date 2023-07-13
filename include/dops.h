#ifndef __DOPS_H__
#define __DOPS_H__

void emit_push_d_to_stack();
void emit_pop_stack_to_d();
void emit_dereference_to_d();
void emit_set_value_from_d();
void emit_peek_stack_to_d(int offset);
void emit_poke_d_to_stack(int offset);
void emit_negate_d();
void emit_constant_to_d(int c);

#endif