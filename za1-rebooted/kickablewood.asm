.orga 0x21A498
	.dd 0x0C0000008040E900

.orga 0x120E900
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	
	LW T0, 0x14C(V1)
	SLTI AT, T0, 3
	BNEZ AT, orig
	NOP

	LWC1 F0, 0x188(V1)
	LWC1 F2, 0x0A4(V1)
	
	; check for fallen to proper point
	c.lt.s F0, F2
	nop
	bc1t nosetfini
	nop
	
	B orig
	SWC1 F0, 0x0A4(V1)
nosetfini:

	; fall down with acceleration
	LW T2, 0x154(V1)
	MTC1 T2, F0
	cvt.s.w F0, F0
	LI T3, 5.0
	MTC1 T3, F4
	add.s F0, F0, F4
	sub.s F2, F2, F0
	SWC1 F2, 0x0A4(V1)
	
orig:
	JAL 0x802AA3F4
	NOP

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18