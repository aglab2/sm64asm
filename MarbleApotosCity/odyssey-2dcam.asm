;klepto overwrite 5310
.orga 0x21F110
.word 0x00090000
.word 0x08000000
	.word 0x0C000000
	.word 0x80310498
.word 0x09000000

;rect coordinates
;(4542, -10527) - (1078, -7089)

.orga 0xCB498
.area 0x120
	LUI V0, 0x8034
	
	LWC1 F0, 0xB1B4(V0) ;Z
	LWC1 F2, 0xB1AC(V0) ;X
	
	;Check if inside area for X
	LI T0, 1078.0
	MTC1 T0, F4
	c.lt.s F4, F2
	BC1F odyssey2dcam_end
	
	LI T0, 4542.0
	MTC1 T0, F4
	c.lt.s F2, F4
	BC1F odyssey2dcam_end
	
	;Check if inside area for Z
	LI T0, -7089.0
	MTC1 T0, F4
	c.lt.s F0, F4
	BC1F odyssey2dcam_end
	
	LI T0, -10527.0
	MTC1 T0, F4
	c.lt.s F4, F0
	BC1F odyssey2dcam_end
	
	
	
	;Is in area 1: (>4000, <-7853)
	LI T0, 4000.0
	MTC1 T0, F4
	c.lt.s F4, F2
	BC1F odyssey2dcam_not1
		
	LI T0, -7853.0
	MTC1 T0, F4
	c.lt.s F0, F4
	BC1F odyssey2dcam_not1
	
	;Area 1 configs
	;set mario position + lakitu angle
	LI T7, 4178.0
	SW T7, 0xB1AC(V0)
	B odyssey2dcam_setstuff
	LUI T8, 0xC000
	
odyssey2dcam_not1:
	;Is in area 2: (>1892, >-7812)
	LI T0, 1892.0
	MTC1 T0, F4
	c.lt.s F4, F2
	BC1F odyssey2dcam_not2
		
	;LI T0, -7812.0
	;MTC1 T0, F4
	;c.lt.s F4, F0
	;BC1F odyssey2dcam_not2
	
	;Area 2 configs
	;set mario position + lakitu angle
	LI T7, -7476.0
	SW T7, 0xB1B4(V0)
	B odyssey2dcam_setstuff
	LUI T8, 0x8000
	
odyssey2dcam_not2:
	;Area 3 configs
	;set mario position + lakitu angle
	LI T7, 1467.0
	SW T7, 0xB1AC(V0)
	B odyssey2dcam_setstuff
	LUI T8, 0x4000

odyssey2dcam_setstuff:
	;set lakitu cam angle
	SW T8, 0xC778(V0)

	;fix lakitu cam state
	LUI T1, 0x0
	ADDIU T1, T1, 0x4
	SB T1, 0xC685(V0)

	;set lakitu cam angle
	LUI T1, 0x0
	ADDIU T1, T1, 10
	SB T1, 0xC849(V0) 

odyssey2dcam_end:
	JR RA
	NOP
.endarea