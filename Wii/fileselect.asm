.if readu32(outputname(), 0x6F50) == 0xC00B100C || readu32(outputname(), 0x6F50) == 0xC00B1008
.orga 0x6F34
	JAL 0x80402F00
	NOP

.orga 0x6F50
	B 0x6F90
	OR V0, R0, R0
	
.orga 0x1202F00
	LUI AT, 0x8033
	LH AT, 0xDDF8(AT)
	LUI T0, 0x8040
	ADDU T0, T0, AT
	JR RA
	LBU AT, 0x2EC0(T0)
.endif