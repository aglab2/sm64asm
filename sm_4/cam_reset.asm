.orga 0x4e60
	JAL 0x80404000

.orga 0x1204000
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	JAL 0x80286F68
	SW T0, 0x18(SP)
	
	LW T0, 0x18(SP)
	LW A0, 0x24(T0)
	LB A1, 0x1(A0)
	JAL 0x80286188
	LI A2, 1

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP