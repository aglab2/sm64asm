.orga 0x8593C
	JAL 0x80402A00

.orga 0x1202A00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LUI T0, 0x8036
	LB T1, 0x4B89(T0)
	BEQ T1, R0, setmusic
	NOP
	
	B ehd
	SB A1, 0x4B8A(T0)

setmusic:
	JAL 0x80320544
	SB A1, 0x4B88(T0)
	
ehd:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
;rng manip
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP