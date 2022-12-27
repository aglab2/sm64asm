.orga 0x366c
	JAL 0x405000

.orga 0xe9ae80
	; movie start - corresponds to the m64 0x400 offset
	.dw 0x01100000
	.dw 0x01010101
	.dw 0x01010101
	.dw 0x01010101
	
.orga 0x1205000 ; 0x405000 = 0x1205000
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	LUI A1, 0x8040
	LW A1, 0x4ff0(A1)
	ADDIU A2, A1, 4
	LUI AT, 0x8040
	SW A2, 0x4ff0(AT)
	JAL 0x278504
	NOP
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	NOP
	NOP
	NOP
	NOP
	NOP
	