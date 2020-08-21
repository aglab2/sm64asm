.orga 0x11780
	JAL 0x80403F00
	NOP
	
.orga 0x1203F00
	LI T3, 3.2 ; gravity
	
	LUI AT, 0x8034

	LB T1, 0xB249(AT)
	LI T2, 0xE	
	BNE T1, T2, reg
	NOP
	
	; Level Check
	LB T1, 0xB24A(AT)
	LI T2, 3
	BNE T1, T2, reg
	NOP
	
	; Area Check
	LWC1 F0, 0xB1B0(AT)
	LI T1, 1000.0
	MTC1 T1, F2
	NOP
	c.lt.s F0, F2
	NOP
	bc1f reg
	NOP
	
	; Collision Tri check
	lwc1 f10, 0xB1B0(AT)
	mfc1 t1, f10
	slti t2, t1, 1000
	beqz t2, reg
	NOP

	LI T3, 0.7
	
reg:
	MTC1 T3, F10
	
	JR RA
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