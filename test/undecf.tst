load undecf.asm,
output-file undecf.out,
compare-to undecf.cmp,
output-list RAM[0]%D1.6.1 RAM[34]%D1.6.1;

// Addrs: B=32, A=33
set RAM[32] 5,
set RAM[33] 3,

repeat 30000 {
  ticktock;
}
output;