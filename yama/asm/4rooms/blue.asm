.orga 0x21A078 ;13000278
.dw 0x00090000
.dw 0x08000000
.dd 0x0C000000802A816C
.dw 0x09000000

.orga 0x6316C ;2A816C
.area 0x200
	LUI T9, 0x8034
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	;debug
	LW T3, 0xB1D8 (T9)
	LH T7, 0x06 (T3)
	LH T8, 0x08 (T3)
	SW T8, 0x180(V1) ;debug ymax in Damage
	SW T7, 0x19C(V1) ;debug ymin in Gravity
	
	;(4846, -532) - (1245, 2819)
	LW T2, 0xB1B0(T9)
	LW T0, 0xB1B4(T9)
	LW T1, 0xB1AC(T9)
	
	MTC1 T0, F0
	;---X---
	LI T3, 2819.0
	MTC1 T3, F2
	c.lt.s F2, F0
	NOP
	BC1T fly_no
	
	LI T3, -532.0
	MTC1 T3, F2
	c.lt.s F0, F2
	NOP
	BC1T fly_no
	
	MTC1 T1, F0
	;---Y---
	LI T3, 4846.0
	MTC1 T3, F2
	c.lt.s F2, F0
	NOP
	BC1T fly_no
	
	LI T3, 1245.0
	MTC1 T3, F2
	c.lt.s F0, F2
	NOP
	BC1T fly_no
	
	
	MTC1 T2, F0
	;---Z---
	LI T3, 7065.0
	MTC1 T3, F2
	c.lt.s F2, F0
	NOP
	BC1T fly_no
	
	LI T3, 4947.0
	MTC1 T3, F2
	c.lt.s F0, F2
	NOP
	BC1T fly_no
	
	;Getting collision triangle ymin
	LW T3, 0xB1D8 (T9)
	LH T7, 0x06 (T3)
	LI T4, 1000 ;totally random but should work
	BGE T7, T4, fly_no
	
	NOP

fly_setzspeed:
	LW T4, 0x14C(V1)
	BNE T4, R0, fly_nosaveZ
	NOP
	
	B fly_goflynocheck
	SW T2, 0x14C(V1)

fly_nosaveZ:
	;last check for Z coordinate gliding
	LW T3, 0x14C(V1)
	MTC1 T3, F2
	c.lt.s F2, F0
	NOP
	BC1T fly_fini
	NOP

fly_goflynocheck:
	;fix shitty camera
	ADDIU T5, R0, 1
	SB T5, 0xC6D4(T9)

	;fly
	ADDIU T5, R0, 0x4220
	SH T5, 0xB1BC(T9)
	LI T5, 0x03000880
	B fly_fini
	SW T5, 0xB17C(T9)
	
fly_no:
	SW R0, 0x14C(V1)

fly_fini:
	JR RA
	NOP
.endarea