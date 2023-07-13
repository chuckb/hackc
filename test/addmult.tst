load addmult.asm,
output-file addmult.out,
compare-to addmult.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

repeat 5000 {
  ticktock;
}
output;