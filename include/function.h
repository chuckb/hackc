#ifndef __FUNCTION_H__
#define __FUNCTION_H__

void emit_label(char *);
void emit_goto(char *);
void emit_function(char *, int);
void emit_call(char *, int);
void emit_spin(char *);

#endif