L1:	EQU 1
L2: EQU 1
LOAD N
SECTION TEXT ;comentarios
IF L1
LOAD N ;faz esta operação se L1 for verdadeiro
IF L2
INPUT N ;faz esta operação se L2 for verdadeiro
INPUT X+L2

SECTION DATA
N: SPACE
x: SPACE 3
LOAD N