load vars.asm,
output-file vars.out,
compare-to vars.cmp,
output-list RAM[0]%D1.6.1 RAM[35]%D1.6.1;

// Addrs: X=35, B=32, A=33, C=34
set RAM[32] 5,
set RAM[33] 3,
set RAM[34] 6;

repeat 30000 {
  ticktock;
}
output;