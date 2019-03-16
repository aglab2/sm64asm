; A0, A1 - coordinates
; A2 - what to print
.orga 0x120DF00
.area 0xF0, 0x00
	ADDIU SP, SP, -0x38
	SW RA, 0x14(SP)
	
	SW A0, 0x20(SP)
	SW A1, 0x24(SP)
	
	LI T0, 30
	DIV A2, T0
	
	MFLO T0
	SW T0, 0x18(SP)
	MFHI T1
	SW T1, 0x1C(SP)
	
	LI A2, 0x8040DFF0
	JAL 0x802D62D8
	LW A3, 0x18(SP)
	
	LW A0, 0x20(SP)
	ADDIU A0, A0, 30
	LW A1, 0x24(SP)
	LI A2, 0x8040DFF0
	JAL 0x802D62D8
	LW A3, 0x1C(SP)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x38
.endarea

.orga 0x120DFF0
.asciiz "%02d"