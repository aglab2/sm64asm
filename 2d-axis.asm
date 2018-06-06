;setup behaviour script
.org 0x21F1DC
.word 0x00090000
.word 0x08000000
	.word 0x0C000000
	.word 0x80312168
.word 0x09000000

;setup 2d behaviour shit
.org 0xCD168
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	LUI T0, 0x8034
	
	LW T1, 0x0A8 (V1)
;set mario position, lakitu cam angle
	SW T1, 0xB1B4(T0)
	SH R0, 0xC778(T0)

;fix lakitu cam state
	LUI T1, 0x0
	ADDIU T1, T1, 0x4
	SB T1, 0xC685(T0)

;set lakitu cam angle
	LUI T1, 0x0
	ADDIU T1, T1, 10
	SB T1, 0xC849(T0) 

	JR RA
	NOP