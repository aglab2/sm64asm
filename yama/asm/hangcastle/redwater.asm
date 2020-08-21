.orga 0xF1A8
	JAL 0x80405a00

.orga 0x1205a00
.area 0x80
	LUI T1, 0x8034
	LB T1, 0xB249(T1)
	ADDIU S0, R0, 0x17
	BEQ S0, T1, geeroid_water
	NOP
	
	B end
	ADDIU S0, R0, 1

geeroid_water:
	ADDIU S0, R0, 0x7

end:
	JR RA
	NOP
.endarea