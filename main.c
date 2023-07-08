#include "cradle.h"
#include <stdio.h>

// Can we echo to stdout a file sent via stdin?
// Yes, silly, but those are the main bits in cradle.c.
// make and then ./hackc < test.txt
int main (void) {
  init();
  while (look.i != EOF) {
    printf("%c", look.c);
    get_char();
  }
}