.orga 0x3bd8
	JAL 0x802CB1D8

.orga 0xe29ac
	JAL 0x802CB1C0

.orga 0x21cce0
	.dw 0x80404600


.orga 0x861c0
; Frame 0x802CB1C0
	LUI T0, 0x8040
	LW T1, 0x4780(T0)
	ADDIU T1, T1, 1
	SW T1, 0x4780(T0)
	
	J 0x80327b98
	NOP

; VisualFrame 0x802CB1D8
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	JAL 0x80248090
	NOP

	LUI T0, 0x8040
	LW T1, 0x4780(T0)
	SUBIU T1, T1, 2
	SW T1, 0x4780(T0)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18


.orga 0x66F54
	JAL 0x80403d00
	LWC1 F4, 0x015C (T7)
	NOP
	
.orga 0x66fe4
	JAL 0x80403d00
	LWC1 F8, 0x15C(T0)
	NOP
	c.lt.s F6, F8
	
.orga 0x1203d00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LUI T0, 0x8040
	LW T1, 0x4788(T0)
	
	LI T2, 100
	BGE T2, T1, noclamp
	NOP
	
	LI T1, 100
noclamp:

	MTC1 T1, F10
	cvt.s.w F10, F10
	
	LI T2, 40.0
	MTC1 T2, F6
	mul.s F10, F10, F6

	LI AT, 5000.0
	MTC1 AT, F6
	
	sub.s F6, F6, F10
		
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

.orga 0x59d38
	JAL 0x80403e00
	LW A0, 0x2c(SP)
	BEQL V1, R0, 0x59dbc
	LI V0, 0

.orga 0x1203e00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	JAL 0x277F50
	NOP
	
	LW T0, 0x0(V0)
	LI T1, 0x000C0000
	
	BNE T0, T1, nodespawn
	LI V1, 1
	
	LW T2, 0x80404788
	LI T3, 30
	BGE T3, T2, nodespawn
	NOP
	
	B despawn_end
	LI V1, 0
	
nodespawn:
	SW V0, 0x30(SP)
	JAL 0x2C9F04
	LW A0, 0x30(SP)

despawn_end:
	LW RA, 0x14(SP)
	ADDIU SP, SP, 0x18
	JR RA
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	
.orga 0x59dfc
	JAL 0x80403e80
.orga 0x57a38
	JAL 0x80403e80
	
.orga 0x1203e80
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	BEQ A0, R0, nodoingthing
	NOP
	
	JAL 0x8029f0e0
	NOP

nodoingthing:
	LW RA, 0x14(SP)
	ADDIU SP, SP, 0x18
	JR RA
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP