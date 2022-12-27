.orga 0x6674
	JAL 0x80405800

.orga 0x1205700 + 29
.db 11
.orga 0x1205700 + 9
.db 12
.orga 0x1205700 + 24
.db 13
.orga 0x1205700 + 12
.db 14
.orga 0x1205700 + 5
.db 15
.orga 0x1205700 + 21
.db 16

.orga 0x1205800
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LI A0, 26 ; courtyard
	LI A1, 1
	LHU T0, 0x8032ddf8
	LUI T1, 0x8040
	ADD T1, T1, T0
	LB A2, 0x5700(T1)
	
	JAL 0x8024a700
	LI A3, 0

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