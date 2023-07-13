load singleint.asm,
output-file singleint.out,
compare-to singleint.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

repeat 5000 {
  ticktock;
}
output;