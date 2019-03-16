.orga 0x120D200
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040DE00
.dw 0x09000000

.orga 0x120DE00
.area 0x100, 0x00
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	
	LB T0, 0x80400040
	BEQ T0, R0, kys
	NOP
	
; desat
; A0 = segptr
; A1 = size
	LW A0, 0x188(V1)
	LB A1, 0xA9(V1)
	LBU T0, 0xA5(V1)
	SLL T0, T0, 8
	OR A1, A1, T0
	LBU T0, 0xA1(V1)
	SLL T0, T0, 16
	OR A1, A1, T0
	LI A2, 0x8040D300
	JAL 0x8040D400
	NOP
	
; despawn
	JAL 0x8040D500
	NOP
	
	LW T0, 0x154(V1)
	BNE T0, R0, nomusic
	NOP

; play music
	LI A0, 0
	LI A1, 2
	JAL 0x80320544
	LI A2, 0
	NOP
	
nomusic:
	SLTI AT, T0, 20
	BNE AT, R0, bend
	NOP
	
kys:
	SW R0, 0x74(V1)
	
bend:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea

; pixel desaturate
.orga 0x120D300
.area 0x100, 0x00
; T0 is min
; T1 is max
	ADD T0, A0, R0
	ADD T1, A0, R0
	
	BGE A1, T0, l1
	NOP
	ADD T0, A1, R0
l1:
	BGE A2, T0, l2
	NOP
	ADD T0, A2, R0
l2:

	BGE T1, A1, l3
	NOP
	ADD T1, A1, R0
l3:
	BGE T1, A2, l4
	NOP
	ADD T1, A2, R0
l4:

	BEQ T0, T1, fini
	NOP

	BNE T1, A0, Rdec
	NOP
	SUBI A0, A0, 1
Rdec:
	BNE T1, A1, Gdec
	NOP
	SUBI A1, A1, 1
Gdec:
	BNE T1, A2, Bdec
	NOP
	SUBI A2, A2, 1
Bdec:
	BNE A0, T0, Rinc
	NOP
	ADDI A0, A0, 1
Rinc:
	BNE A1, T0, Ginc
	NOP
	ADDI A1, A1, 1
Ginc:
	BNE A2, T0, Binc
	NOP
	ADDI A2, A2, 1
Binc:
	
fini:
	JR RA
	NOP
.endarea

; A0 segmented ptr start
; A1 data count
; A2 function ptr(R, G, B, A), returns in the same registers
.orga 0x120D400
.area 0x100, 0x00
	ADDIU SP, SP, -0x38
	SW RA, 0x14(SP)
	SW A2, 0x20(SP)
	SW A1, 0x24(SP)
	
	LW V1, 0x80361160
; V0 = ptr to data
	JAL 0x80277F50
	NOP
	
; T9 = ptr to func to call
; T4 = left to process
	LW T9, 0x20(SP)
	LW T4, 0x24(SP)
	
; Data Cycle Start
loop:
	BEQ T4, R0, end
	NOP
	
; T8 = RGBA 5+5+5+1
	LH T8, 0x0(V0)

; Convert
; RRRRRGGG GGBBBBBA
; A0 = R; A1 = G; A2 = B
	SRL A0, T8, 11
	ANDI A0, A0, 0x001F
	SRL A1, T8, 6
	ANDI A1, A1, 0x001F
	SRL A2, T8, 1
	ANDI A2, A2, 0x001F
	ANDI A3, T8, 0x01

; Do transforms....
	SW V0, 0x18(SP)
	SW T4, 0x1C(SP)
	JALR T9
	NOP
	LW V0, 0x18(SP)
	LW T4, 0x1C(SP)
	LW T9, 0x20(SP)

; Convert back
	SLL T8, A2, 1
	SLL T0, A1, 6
	OR T8, T8, T0
	SLL T0, A0, 11
	OR T8, T8, T0
	OR T8, A3
	
endloop:
	SH T8, 0x0(V0)
	SUBI T4, T4, 2
	ADDI V0, V0, 2
	B loop
	NOP

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x38
.endarea

; Despawn world
.orga 0x120D500
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LI A0, 0x13000000
	JAL 0x80277F50
	NOP
	
	LW V1, 0x80361160
	LI T9, 0x8033D488
	LI T8, 240
dwloop:
	BEQ T8, R0, dwend
	NOP

; don't kys
	BEQ T9, V1, dwloopend
	NOP
; objects behaviour whitelist
	LW T0, 0x20C(T9)
	ADDIU T1, V0, 0x2EC0
	BEQ T1, T0, dwloopend
	NOP
	LI T1, 0x8040D200
	BEQ T1, T0, dwloopend
	NOP
	LI T1, 0x8040C480
	BEQ T1, T0, dwloopend
	NOP
	
	SW R0, 0x74(T9)
	
dwloopend:
	ADDIU T9, T9, 0x260
	SUBIU T8, T8, 1
	B dwloop
	NOP

dwend:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea