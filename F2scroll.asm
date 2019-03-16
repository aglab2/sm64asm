; behav
.orga 0x120F000
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040F080
.dw 0x09000000

; +1 0x46010000=8256
; +2 0x46020000=8320
; +3 0x46030000=8384
; +4 0x46040000=8448

; -1 0x46FF0000=32640
; -2 0x46FE0000=32512
; -3 0x46FD0000=32384
; -4 0x46FC0000=32256

.orga 0x120F080
.area 0x80, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	LB A1, 0xA1(V1)
	LB A2, 0xA5(V1)
	
	JAL 0x8040F100
	LW A0, 0x188(V1)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

; A0 = cmdF2 seg address
; A1 = spd x
; A2 = spd y
.orga 0x120F100
.area 0x100, 0x00
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	SW A1, 0x18(SP)
	SW A2, 0x1C(SP)
	
	JAL 0x80277F50
	NOP
	
	LW A1, 0x18(SP)
	LW A2, 0x1C(SP)

; T1, T2, T3 = read bytes needed to be altered
	LBU T1, 0x1(V0)
	LBU T2, 0x2(V0)
	LBU T3, 0x3(V0)
	
; T7 = X coordinate
	SLL  T4, T1, 4
	ANDI T5, T2, 0xF0
	SRL  T5, T5, 4
	ADDU T7, T4, T5
	
; T8 = Y coordinate
	ANDI T4, T2, 0x0F
	SLL  T4, T4, 8
	ADDU T8, T4, T3

; DO MANIPS ON T7, T8 here
	ADDU T7, T7, A1
	ADDU T8, T8, A2

; Convert coordinates back
; T1 = T7 (SSs)
	ANDI T1, T7, 0xFF0
	SRL  T1, T1, 4
; T2 = T7 | T8 (ssS Ttt)
	ANDI T2, T7, 0x00F
	SLL  T2, T2, 4
	ANDI T0, T8, 0xF00
	SRL  T0, T0, 8
	ADDU T2, T2, T0
; T3 = T8 (tTT)
	ANDI T3, T8, 0x0FF
	
	
; write back data
	SB T1, 0x1(V0)
	SB T2, 0x2(V0)
	SB T3, 0x3(V0)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea