.orga 0x120BB00
	.dw 0x00040000
	.dw 0x08000000
	.dd 0x0C0000008040BB70
	.dd 0x0C0000008040BC00
	.dw 0x09000000

.orga 0x120BB20
	.asciiz "START TO SET STATE"
.orga 0x120BB40
	.asciiz "L TO LOAD STATE"
.orga 0x120BB50
	.asciiz "CAN LEDGEGRAB SLIDE SIDES"

.orga 0x120BB70
.area 0x90, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW A1, 0x80361158
	LW A0, 0x80361160
	JAL 0x8029E2F8
	NOP
	
	LI T0, 300.0
	MTC1 T0, F2
	LI A0, 160
	c.lt.s F0, F2
	LI A1, 180
	bc1f endpri
	NOP
	
	LI A2, 0x8040BB20
	jal 0x802D66C0
	NOP
	
	LI A0, 160
	LI A1, 160
	LI A2, 0x8040BB40
	jal 0x802D66C0
	NOP
	
	LI A0, 160
	LI A1, 40
	LI A2, 0x8040BB50
	jal 0x802D66C0
	NOP

endpri:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

.orga 0x120BC00
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	JAL 0x8040BF00
	NOP
	
	LI T0, 1
	SB T0, 0x80400040
	
	LUI V0, 0x8034
	LUI V1, 0x8040
	
	;quicksand should trigger not allowing to load
	LW T0, 0xB17C (V0)
	LI T1, 0xFFFFF000
	AND T0, T0, T1
	LI T1, 0x00021000
	BEQ T1, T0, finish
	NOP
	
	LB T0, 0xB21E (V0)
	BEQ T0, R0, finish
	NOP

	LH T0, 0xAFA2 (V0)
	
	ANDI T1, T0, 0x20
	LI T4, 0x20
	BNE T1, T4, noload
	NOP

loadstate:
	LW T0, 0x100(V1)
	BEQ T0, R0, finish
	NOP
	
	LUI T1, 0x8033
	LW T1, 0xDDCC(T1)
	LW T1, 0x24(T1)
	SB R0, 0x30(T1)
	
	LI A0, 0x8033B170
	LI A1, 0x80361C98
	LI A2, 0x80780000
	
	B memcpy
	NOP

noload:

	ANDI T1, T0, 0x1000
	LI T4, 0x1000
	BNE T1, T4, nosave
	NOP
	
	SW K0, 0x100(V1)
	LI A0, 0x80780000
	LI A1, 0x807A6B28
	LI A2, 0x8033B170
	B memcpy
	NOP
nosave:


finish:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

memcpy:
	LW T9, 0x0(A2)
	SW T9, 0x0(A0)
	ADDIU A0, A0, 4
	BNE A1, A0, memcpy
	ADDIU A2, A2, 4
	
	B finish
	NOP
.endarea

; save game
.orga 0x120BF00
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW T0, 0x8033B17C
	LI T1, 0x00001904
	BNE T0, T1, nosav
	NOP
	
	; must save
	LI T1, 1
	SB T1, 0x8033B4A6

	; current file
	LH A0, 0x8032DDF4
	SUBI A0, A0, 1
	JAL 0x80279840
	NOP

nosav:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea