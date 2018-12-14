.orga 0x8593C
	J 0x80310998

.orga 0xCB998
.area 0x100
	LUI T0, 0x8033
	LB T0, 0x31AC(T0)
	
	ADDIU T1, R0, 0x16
	BEQ T1, T0, fix_noset
	NOP
	
	JAL 0x80320544
	NOP
	
fix_noset:
	J 0x802CA944
	NOP
.endarea