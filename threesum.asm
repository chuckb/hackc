	@256
	D=A
	@SP
	M=D
	@2
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1
	@5
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1
	@R_0
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1
	@add16
	0;JMP
(R_0)
	@3
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1
	@SP
	M=M-1
	A=M
	D=M
	D=!D
	D=D+1
	@SP
	A=M
	M=D
	@SP
	M=M+1
	@R_1
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1
	@add16
	0;JMP
(R_1)
(end)
	@end
	0;JMP
(add16)
	@2
	D=A
	@SP
	A=M-D
	D=M
	A=A-1
	M=D+M
	@SP
	M=M-1
	A=M
	D=M
	@SP
	M=M-1
	A=D
	0;JMP