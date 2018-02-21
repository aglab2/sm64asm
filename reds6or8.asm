.orga 0xADDE4
.area 0x08
	B 0xCB498
	NOP
.endarea

.orga 0xCB498
.area 0xB0
	ADDIU R1, R0, 6
	BEQ R8, R1, 0xADDEC
	NOP
	ADDIU R1, R0, 8
	BEQ R8, R1, 0xADDEC
	NOP
	B 0xADDFC
.endarea