.orga 0x12068b8
	JAL 0x406990
	LI T9, 30

.orga 0x1206990
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LHU A3, 0x8033b170+0xB6
	DIVU A3, T9
	JAL 0x2d62d8
	MFLO A3

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
