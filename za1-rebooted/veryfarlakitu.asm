.orga 0x3C61C
	JAL 0x8040DA00
	
.orga 0x120DA00
.area 0x100, 0x00
	ADDIU SP, SP, -0x20
	SW RA, 0x14(SP)
	
	LUI T8, 0x8034
	LB T0, 0xB249(T8)
	LB T3, 0xB24A(T8)
	
	LI T1, 0x22
	BNE T0, T1, notveryfar
	NOP
	
	LI T2, 2600.0
	MTC1 T2, F12
	NOP
	B doit
	NOP

notveryfar:

	LI T1, 0x17
	BNE T0, T1, notfar
	NOP
	
	LI T1, 2
	BNE T3, T1, notfar
	NOP
	
	LI T2, 600.0
	MTC1 T2, F12
	NOP

notfar:

doit:
	JAL 0x80281188
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x20
.endarea