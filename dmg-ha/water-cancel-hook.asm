.orga 0x2f864
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	lw at, 0x8040A128
	jalr at
	nop
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

.orga 0x2AA18
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	lw at, 0x8040A12C
	jalr at
	nop
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
