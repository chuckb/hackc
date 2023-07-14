load paren.asm,
output-file paren.out,
compare-to paren.cmp,
output-list RAM[0]%D1.6.1 RAM[32]%D1.6.1;

repeat 5000 {
  ticktock;
}
output;