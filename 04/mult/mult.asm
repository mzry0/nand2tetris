// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

	@R0
	D = M
	@i
	M = D	//store R0 in i
	@R1
	D = M
	@j
	M = D	//store R1 in j
	@R2
	M = 0
(START)
	@i
	D = M-1
	@END
	D;JLT
	@j
	D = M
	@R2
	M = M+D
	@i
	M = M-1
	@START
	0;JMP
(END)		//infinite loop
	@END
	0;JMP