#ifndef __CRADLE_H__
#define __CRADLE_H__

typedef union {
    int i;
    char c;
} look_t;

extern look_t look;

void get_char();
void error(char* message);
void bail(char* message);
void expected(char* message);
void match(char c);
char get_name();
char get_num();
int is_add_op(char c);
void emit(char* s);
void emit_ln(char* s);
void tab_emit(char* s);
void tab_emit_ln(char* s);
void tab_emit_constant(int c);
void init();

#endif