;overwrite klepto behav with c1 switcheroni

.orga 0x21F110;behav 0x13005310
.word 0x00040000
.word 0x08000000
.word 0x0C000000
	.word 0x80310498
.word 0x09000000

.orga 0xCB498
.area 0xB0
;Beat Start
	LUI V0, 0x8040
	LW T0, 0x0004(V0)
	ADDIU T1, R0, 60
	
	BEQ T0, T1, c1_beatswitch
	NOP
	
	ADDIU T0, T0, 0x1
	SW T0, 0x0004(V0)
	B c1_beatend
	NOP
	
c1_beatswitch:
	SW R0, 0x0004(V0)
	LB T2, 0x0000(V0)
	ADDIU T3, R0, 0x0002
	SUB T2, T3, T2
	SB T2, 0x0000(V0)
c1_beatend:

;Light bobomb start
	LUI V0, 0x8034
	LW T0, 0xB17C(V0)
	
	LUI T1, 0x0000
	ADDIU T1, 0x0447
	
	BNE T0, T1, c1_bobombend
	NOP
	
	LUI T1, 0x0000
	ADDIU T1, 0x0385
	SW T1, 0xB17C(V0)
c1_bobombend:

	JR RA
	NOP
.endarea