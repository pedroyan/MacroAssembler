;Código fonte do módulo B:
MOD_B:  BEGIN
VAL:    EXTERN
L1:     EXTERN
		PUBLIC  Y
		PUBLIC  MOD_B
		OUTPUT  Y
		OUTPUT  VAL
		OUTPUT  Y + 2
		JMP     L1
Y:      SPACE   3
		END