.orga 0x38914
	JAL 0x8040F100

.orga 0x120F100
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; dont do magic during timestop, it does verk
	LW V1, 0x8033d480
	BNE V1, R0, nooverride

	; only draw object with animations
	LW V0, 0x44(SP)
	BEQ V0, R0, ehd
	NOP
	
nooverride:
	JAL 0x27d518
	NOP

ehd:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

.orga 0x57b70
	NOP
	NOP
	JAL 0x8040F200
	NOP

.orga 0x587a0
	JAL 0x8040F2e4
	NOP