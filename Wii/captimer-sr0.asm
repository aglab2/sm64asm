.orga 0xf484
	JAL 0x80406880
	NOP
	BNEZ T9, 0xf4d0
	NOP
	
.orga 0x1206880
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	SW T9, 0x10(SP)
	LI A0, 0x1d
	LI A1, 0x10
	LI A2, 0x80338388
	JAL 0x802d62d8
	ADDIU A3, T6, 0
	
	LW T9, 0x10(SP)
	BEQZ T9, nofixup
	NOP
	JAL 0x80249448
	NOP
	
nofixup:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP