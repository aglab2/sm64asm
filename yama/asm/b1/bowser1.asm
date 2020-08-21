.orga 0x21D9B4 ;3BB4
.dw 0x00090000
.dw 0x08000000
.dd 0x0C000000802F0168
.dw 0x09000000

.orga 0xAB168 ;802F0168
.area 0x200
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)

;2d stuff
	LUI T0, 0x8034
	
	LWC1 F0, 0xB1B4(T0)
	LI T8, -3700.0
	MTC1 T8, F2
	
	;if phase 2 already
	LW T1, 0x0A0 (V1)
	BEQ T1, R0, nophase2
	NOP
	
	c.lt.s F0, F2
	NOP
	BC1F nophase2
	NOP

	SW R0, 0x0A0 (V1)
	LI T1, 0xC000
	SH T1, 0x188 (V1)
	
	LI T1, -1000.0
	SW T1, 0xB1B4 (T0)
	
nophase2:
	;set mario position, lakitu cam angle
	LW T1, 0x0A0 (V1)
	SW T1, 0xB1AC(T0)
	LH T1, 0x188 (V1)
	SH T1, 0xC778(T0)

	;fix lakitu cam state
	LUI T1, 0x0
	ADDIU T1, T1, 0x4
	SB T1, 0xC685(T0)

	;set lakitu cam angle
	LUI T1, 0x0
	ADDIU T1, T1, 10
	SB T1, 0xC849(T0)
	
;set bowser position to 0 on X
	LI.u A0, 0x13001850
	JAL 0x8029F95C
	LI.l A0, 0x13001850
	
	BEQ V0, R0, bowser_end
	NOP
	
	SW R0, 0x0A0(V0)
bowser_end:

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
.endarea