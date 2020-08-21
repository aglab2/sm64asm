;setup behaviour script
.org 0x21F1DC ;53DC
.word 0x00090000
.word 0x08000000
	.word 0x0C000000
	.word 0x80312168
.word 0x09000000

;setup 2d behaviour shit
.org 0xCD168
.area 0x100
ADDIU SP, SP, -0x18
SW RA, 0x14(SP)

	LUI T9, 0x8041
	LUI T8, 0x8034

	LB T1, 0x0000(T9)
.f_testInput BUTTON_L, BUTTON_PRESSED, func_changecambit
	XORI T1, T1, 0x1
	SB T1, 0x0000(T9)
	ADDIU T2, R0, 0x4000
	SH T2, 0xC778(T8)
	
	ADDIU T3, R0, 0x0800
	SH T3, 0xB21E(T8)
	
	ADDIU A1, R0, 0x2A
	ADDU A1, A1, T1
	JAL 0x80320544
	ADDU A0, R0, R0
	
	LUI T9, 0x8041
	LB T1, 0x0000(T9)
	LUI T8, 0x8034
func_changecambit:



	BNE T1, R0, func_no2dcam
	NOP
	
;set mario position, lakitu cam angle
	SW R0, 0xB1B4(T8)
	SH R0, 0xC778(T8)

;set lakitu cam Z angle
	LUI T1, 0x0
	ADDIU T1, T1, 10
	SB T1, 0xC849(T8)

;fix lakitu cam state
	LUI T1, 0x0
	ADDIU T1, T1, 0x4
	B func_end
	SB T1, 0xC685(T8)
	
func_no2dcam:
	LH T3, 0xB21E(T8)
	ADDIU T4, R0, 0x0004
	SUB T3, T3, T4
	SH T3, 0xB21E(T8)
	
func_end:
LW RA, 0x14(SP)
JR RA
ADDIU SP, SP, 0x18
.endarea