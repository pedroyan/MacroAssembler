MOD_A: BEGIN
	MOD_B: EXTERN
	L2: EQU 0
	PUBLIC FAT
	PUBLIC N
	INPUT N
	LOAD N
	FAT: SUB ONE
	JMPZ FIM
	JMP MOD_B
	FIM: OUTPUT N
	STOP
	N: SPACE
	ONE: CONST 1
END