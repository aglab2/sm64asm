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
;set mario position
	SW T1, 0xB1B4(T0)

;lakitu cam angle
	LH T1, 0xAFA2(T0)
	LH T3, 0xAFA0(T0)
	ANDI T1, T1, 0xFFF3
	ANDI T3, T3, 0xFFF3
	
	LUI T5, 0x8033
	LW T5, 0xDF60 (T5)
	LH T5, 0x0012 (T5)
	ADDI T6, R0, 0x6000
	BGE T5, T6, nofilter
	NOP
	ADDI T6, R0, -0x6000
	BGE T6, T5, nofilter
	NOP
	
	ANDI T1, T1, 0xF7FF
	ANDI T3, T3, 0xF7FF

nofilter:
	LH T8, 0xC778(T0)
	LI T9, 0x2000
	BGE T8, T9, setangle
	ADDIU T2, R0, 0xFEF2
	LI T9, -0x2000
	BGE T9, T8, setangle
	ADDIU T2, R0, 0xFDF1
	
	B nosetangle
	NOP
	
	;SH R0, 0xC778(T0)

setangle:
	SH T9, 0xC778(T0)
	AND T1, T1, T2
	AND T3, T3, T2

nosetangle:
	SH T1, 0xAFA2(T0)
	SH T3, 0xAFA0(T0)

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