.orga 0x120D600
.dw 0x00040000
	.dd 	0x0C0000008040F680
.dw 0x08000000
	.dd 	0x0C0000008040D700
.dw 0x09000000

.orga 0x120D680
.dw 1229.0, -1744.0
.dw -1231.0,-1748.0
.dw -2046.0, 670.0
.dw 0.0, 2124.0
.dw 1974.0, 640.0

.orga 0x120D6C0
.asciiz "%d"
.orga 0x120D6D0
.db 0x28, 0x15, 0x29, 0x37, 0x7B

.orga 0x120D700
.area 0x200, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	
; 10f delay
	LW T0, 0x154(V1)
	SLTI AT, T0, 10
	BNEZ AT, prepare
	NOP
	
; init cutscenes
	LW A0, 0x100(V1)
	
	LW T0, 0x14C(A0)
	LI T1, 0x4
	BEQ T0, T1, end
	NOP
	LI T1, 0x6
	BEQ T0, T1, end
	NOP
	LI T1, 0x5
	BEQ T0, T1, end
	NOP

; do bowser things here
	LW T0, 0x104(V1)
	BNE T0, R0, dofight
	NOP
	
; bowser defeated POGGERS
	LI T0, 4
	SW T0, 0x14C(A0)
	SW R0, 0x74(V1)
; global var to affect death warp
	LUI T1, 0x8040
	SW T0, 0x30(T1)
	B center
	NOP
	
dofight:
	LW T0, 0x14C(A0)
	BNE T0, R0, checkforhit
	NOP

changebowserposition:
; pull bowser action here
	JAL 0x8040D900
	NOP
	SW V0, 0x14C(A0)
	LI T0, 8
	BEQ T0, V0, center
	NOP

reroll:
	JAL 0x80383BB0
	NOP

; get new position	
	LUI T9, 0x8041
	LI T0, 5
	DIV V0, T0
	MFHI T1
; should be different place
	LB T2, 0x108(V1)
	BEQ T2, T1, reroll
	NOP
; should not be where mario is standing
	LW T3, 0x8033B1D8
	LH T3, 0x0(T3)
	LUI T4, 0x8041
	ADD T4, T4, T1
	LB T5, 0xD6D0(T4)
	BEQ T5, T3, reroll
	NOP

; it is all good, set stuff up
	SB T1, 0x108(V1)
	SLL T2, T1, 3
	ADD T9, T9, T2
	
	LW A0, 0x100(V1)

; set new position
	LW T0, 0xD680(T9)
	SW T0, 0xA0(A0)
	LW T0, 0xD684(T9)
	SW T0, 0xA8(A0)
	
	B endlookatmario
	NOP

center:
	SW R0, 0xA0(A0)
	SW R0, 0xA8(A0)
	LI T1, 0x7
	SB T1, 0x108(V1)
	B endlookatmario
	NOP

checkforhit:
; load data for collision and check for hit
	LW T0, 0x8033B1D8
	LH T0, 0x0(T0)
	LB T1, 0x108(V1)
	LUI T2, 0x8041
	ADD T2, T2, T1
	LB T3, 0xD6D0(T2)
	BNE T0, T3, endlookatmario
	NOP
	
; register hit for mario and move away bowser
	LW T0, 0x104(V1)
	SUBI T0, T0, 1
	B changebowserposition
	SW T0, 0x104(V1)

endlookatmario:
	LW A1, 0x80361158
	JAL 0x8029E694
	NOP

	LW A0, 0x100(V1)
	SH V0, 0xCA(A0)
	
printscore:
	LI A0, 10
	LI A1, 210
	LI A2, 0x8040D6C0
	JAL 0x802d62d8
	LW A3, 0x104(V1)
	
	B end
	NOP

prepare:
	LI T0, 15
	SW T0, 0x104(V1)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

.orga 0x120D900
.area 0x100, 0x00
	LW T0, 0x104(V1)
	;finale
	LW T1, 0x10C(V1)
	LI T2, 5
	BGE T1, T2, outrage
	NOP
	
	ADDI T1, T1, 1
	SW T1, 0x10C(V1)
	ANDI AT, T0, 1
	BNE AT, R0, fireflames
	LI V0, 0xF
fireflames:
	LI V0, 0xD
	B nooutrage
	NOP
	
outrage:
	SW R0, 0x10C(V1)
	LI V0, 0x8
nooutrage:
	SLTI AT, T0, 4
	BNE AT, R0, fini
	NOP
	LI T1, 20
	SB T1, 0x10C(V1)
	; flames 4-8
	SLTI AT, T0, 8
	BNE AT, R0, fini
	LI V0, 0xF
	
	; jumps 8-12
	SLTI AT, T0, 12
	BNE AT, R0, fini
	LI V0, 0xD ;jumps
	
	; dance 12-14
	SLTI AT, T0, 15
	BNE AT, R0, fini
	LI V0, 0x3
	
	LI V0, 0xE

fini:
	JR RA
	NOP
.endarea