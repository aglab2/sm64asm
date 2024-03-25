.orga 0x13198
	LUI V1, 0x8040
	LHU T7, 0x18(A0)

.orga 0x131a4
	LB V1, 0x51d2(V1)
	BEQ V1, R0, @@nopatch
	LI A1, 0x7a
	LI A1, 0xe2
@@nopatch:
	LI AT, 1
	LHU T9, 0x1A(A0)
	ADDIU S0, T9, 1
	SH S0, 0x1A(A0)
	
.orga 0x131f8
	NOP
.orga 0xa80c0
	NOP
