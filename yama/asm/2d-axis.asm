;setup behaviour script
.org 0x21F1DC
.word 0x00090000
.word 0x08000000
	.dd 0x0C00000080312168
.word 0x09000000

; good angles for lakitu cam
;0900 / 441B0000
;1E00 / 44600000
;+0xB/+0x22

;setup 2d behaviour shit
.org 0xCD168
.area 0x200
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	LUI T0, 0x8034
	LUI T8, 0x8040
	
	LW T7, 0x154(V1)
	BNE T7, R0, notinit
	NOP
	
	LI T7, 0x0900
	SH T7, 0x3670(T8)
	LUI T7, 0x441B
	SW T7, 0x3674(T8)
notinit:
	
;set mario position
	LW A1, 0XB1D8 (T0)
	LI A3, 0X00880898 ; cannon
	LW A2, 0XB17C (T0)
	BEQ A3, A2, nolock
	NOP
	LH A2, 0X0 (A1)
	LI V0, 0XD
	BEQ V0, A2, nolock
	NOP
	LW T1, 0x36D0(T8)
	SW T1, 0xB1B4(T0)  ;LW T1, 0x0A8 (V1)

nolock:
;lakitu cam angle
	LH T1, 0xAFA2(T0)
	LH T3, 0xAFA0(T0)
	
;set far lakitu cam angle
	ANDI T9, T1, 0x04
	BEQ T9, R0, nocup
	NOP
	
	LH T7, 0x3670(T8)
	LI T6, 0x2200
	ADDIU T7, T7, 0x0680 ; this is angle
	BGE T7, T6, nocup
	NOP
	
	SH T7, 0x3670(T8)
	LH T7, 0x3674(T8)
	ADDIU T7, T7, 0x0015 ; this is zooming
	SH T7, 0x3674(T8)

nocup:
	ANDI T9, T1, 0x08
	BEQ T9, R0, nocdown
	NOP
	
	LH T7, 0x3670(T8)
	SUBIU T7, T7, 0x0680 ; this is angle
	BGE R0, T7, nocdown
	NOP

	SH T7, 0x3670(T8)
	LH T7, 0x3674(T8)
	SUBIU T7, T7, 0x0015 ; this is zooming
	SH T7, 0x3674(T8)
	
nocdown:
	ANDI T1, T1, 0xFFF3
	;ANDI T3, T3, 0xFFF3
	
; handle dup properly
	ANDI AT, T3, 0x0800
	BEQZ AT, nofilter
	NOP

; check if normal dup will work fine
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
	
; also ignore small angles to avoid weird stuttering
	abs T6, T5
	LI T7, 0x1010
	BGE T7, T6, nofilter

; emulate dup myself by setting best angle + filtering cstick and dpad
	LI T9, 0x2000
	BGE R0, T5, setangle
	ADDIU T2, R0, 0xF6FE
	LI T9, -0x2000
	B setangle
	ADDIU T2, R0, 0xF5FD

nofilter:
; allow for some angles in between with filtering for c-stick
	LH T8, 0xC778(T0)
	LI T9, 0x2000
	BGE T8, T9, setangle
	ADDIU T2, R0, 0xFEFE
	LI T9, -0x2000
	BGE T9, T8, setangle
	ADDIU T2, R0, 0xFDFD
	
	B nosetangle
	NOP

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
.endarea