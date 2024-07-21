.orga 0x97b50
	lw at, 0x8040A110
	jalr at
	nop

.orga 0x97c30
.area 0x1C, 0x00
	lw at, 0x8040A110
	jalr at
	nop
	nop
.endarea

.orga 0x120ca00
	LUI AT, 0x0800
	AND T2, T1, AT
	BEQ T2, R0, fin
	NOP
	lw t0, 0x8040A114
	bne t0, r0, blck
	nop
	LUI T0, 0x8034
	LB T0, 0xB249 (T0)
	ORI T1, R0, 0x000F
	BNE T0, T1, fin
	NOP
	LUI T0, 0x8034
	LB T0, 0xB24A (T0)
	ORI T1, R0, 0x0006
	BNE T0, T1, fin
	NOP

blck:
	ORI T2, R0, 0x0000

fin:
	JR RA
	NOP
