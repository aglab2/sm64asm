.orga 0x38FF0
	JAL 0x80404b00

.orga 0x1204b00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; check that dls match
	LW T0, 0x14(A0)
	LI T1, 0x040679E0
	BEQ T1, T0, dopatch
	LI T2, 0x040691D0
	BEQ T2, T0, dopatch
	NOP
	
	B nopatch

dopatch:
	; V0 is global timer
	
	; store rotation
	LW V0, 0x8032d5d4
	SLL T3, V0, 7
	SH T3, 0x20(A0)
	
	; store sin of global timer to Y
	SLL T3, V0, 8
	ANDI T4, T3, 0xffff
	SRL T5, T4, 4
	SLL T5, T5, 2
	LUI T6, 0x8038
	ADD T7, T6, T5
	LWC1 F0, 0x6000(T7)
	LUI T8, 0x40a0 ; 5
	MTC1 T8, F2
	MUL.S F4, F0, F2
	cvt.w.s F4, F4
	MFC1 T9, F4
	SH T9, 0x1A(A0)

nopatch:
	JAL 0x8027C114
	NOP
	
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
	NOP