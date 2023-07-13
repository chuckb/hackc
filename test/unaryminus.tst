load unaryminus.asm,
output-file unaryminus.out,
compare-to unaryminus.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

repeat 5000 {
  ticktock;
}
output;