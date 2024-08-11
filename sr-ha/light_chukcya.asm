.orga 0x30530
	lw at, 0x8040A130
	jalr at
	LW A0, 0x18(SP)
	BEQ V0, R0, 0x30594
	NOP
	