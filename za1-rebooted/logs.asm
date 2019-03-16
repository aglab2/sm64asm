.orga 0x21E658
	.dw 0x8040E600

; no angle reset
.orga 0xBC080
	NOP

; no gp
.orga 0xBBF68
	NOP
.orga 0xBBEEC
	ADD V0, R0, R0

; 3 turns in 200000

.orga 0x120E600
.area 0x200, 0x00
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	
; V0 = normals address
; 0E02DFF0 - pound 1 color
	LI T5, 0x0E02DFF0
	LB T4, 0x188(V1)
	SLL T1, T4, 8
	JAL 0x80277F50
	ADD A0, T5, T1
	
	LW T9, 0xF4(V1)
; take absolute value
; T9 = og value
; T8 = sign
; T7 = abs
; T6 = color max
; T5 = address of color thing
; T4 = bparam 1
	
	SRA T8, T9, 31
	XOR T7, T8, T9
	SUB T7, T7, T8

; detect if thing is not blue enough
; T3 = stuff with bit to set/delete
; T2 = old data
	LI T3, 1
	SLLV T3, T3, T4
	LUI T1, 0x8040
	LB T2, 0x4(T1)
	LI T0, 50000
	
	BGE T7, T0, win
	OR T2, T2, T3
	ADDIU T0, R0, 0xFFFF
	XOR T3, T3, T0
	AND T2, T2, T3
win:
	SB T2, 0x4(T1)

; angle clamp
	LI T0, 100000
	BGE T0, T7, noclamp
	NOP

	BEQZ T8, posclamp
	NOP
	SUB T9, R0, T0
posclamp:

noclamp:
	
; color clamp
	LI T0, 90000
	BGE T0, T7, nocclamp
	NOP
	
	B set
	LI T6, 0xFF
nocclamp:
	
; calculate color value
; 80000 = 0
; 0      approx FF
; divisor is 640
	LI T0, 360
	DIV T7, T0
	MFLO T6
	
; make it restore back its state slowly
set:
	LI T0, 160 ; decay speed
	LB T1, 0x189(V1)
	MULT T0, T1
	MFLO T0
	BEQZ T8, posdecay
	NOP
	SUB T0, R0, T0
posdecay:
	SUB T9, T9, T0	

	SB T6, 0x0(V0)
	SB T6, 0x1(V0)
	SB T6, 0x4(V0)
	SB T6, 0x5(V0)
	SRL T6, T6, 1
	SB T6, 0x8(V0)
	SB T6, 0x9(V0)
	SB T6, 0xC(V0)
	B end
	SB T6, 0xD(V0)

end:
	SW T9, 0xF4(V1)

	JAL 0x80300ECC
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea

.orga 0x120EE00
	.dw 0x00040000
	.dw 0x08000000
	.dd 	0x0C0000008040EF00
	.dw 0x09000000
	
.orga 0x120EF00
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LUI T0, 0x8040
	LB T9, 0x4(T0)
	
	LI T0, 0xF
	BNE T0, T9, nostar
	NOP
	
	LW V1, 0x80361160
	SW R0, 0x74(V1)
	
	LWC1 F12, 0xA0(V1)
	LWC1 F14, 0xA4(V1)
	LW A2, 0xA8(V1)
	
	JAL 0x802F2B88
	NOP
	
	LI T0, 5
	SB T0, 0x188(V0)
	
nostar:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea