.orga 0x120F800
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040F900
.dw 0x09000000

.orga 0x120F900
.area 0x100
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; get angle to center
	LW A1, 0x80361158
	LW A0, 0x80361160
	JAL 0x8029E694
	NOP
	
	LW V1, 0x80361160
	LUI T9, 0x8034
	
	; move cam a bit for offset part
LH T8, 0x100(V1)
	
	LH T0, 0xAFA0(T9)
	ANDI T1, T0, 0x01
	BEQ T1, R0, noright
	NOP
;left
	LI T2, 0x3000
	BEQ T8, T2, noright
	NOP
	ADDI T8, T8, 0x100
noright:

	ANDI T1, T0, 0x02
	BEQ T1, R0, noleft
	NOP
;right
	LI T2, -0x3000
	BEQ T8, T2, noleft
	NOP
	SUBI T8, T8, 0x100
noleft:
	
SH T8, 0x100(V1)
	
	; mask inputs
	LH T1, 0xAFA0(T9)
	ANDI T1, 0xF000
	SH T1, 0xAFA0(T9)
	LH T2, 0xAFA2(T9)
	ANDI T2, 0xF000
	SH T2, 0xAFA2(T9)
	
	; calculate angle as circular + offset
	ADD V0, T8, V0

	SH V0, 0xC778(T9)
	LI T1, 0xA
	SB T1, 0xC849(T9)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea