.org 0x82444; 0x2C7454
	J 0x80310898

.orga 0xCB898
.area 0x80
	JAL 0x2A3754
	NOP
;in V0=1 if hit actually occured
	BEQ V0, R0, whomp_nohit
	NOP
;perform on hit check
;mario's height >800
	LUI T0, 0x8034
	LWC1 F0, 0xB1B0(T0)
	LI T1, -800.0
	MTC1 T1, F2
	
	c.lt.s F0, F2
	BC1T whomp_nohit
	XOR V0, V0, V0

;actually hit, put V0 where it was
	ADDIU V0, R0, 1
;also make boss harder :3
	;0x184
	;LUI V1, 0x8036
	;LW V1, 0x1160(V1)
	;LW T0, 0x184(V1)
	;SLL T0, T0, 5
	;ADDIU T0, T0, 0x40
	
	;LUI T1, 0x802C
	;SH T0, 0x7766(T1)
	
whomp_nohit:
	J 0x802C744C
	NOP
.endarea
