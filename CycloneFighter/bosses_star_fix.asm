.org 0x8C4C
	J 0x2B25AC
	NOP
;ANDI T9, T8, 0x0400
;SLTU T0, R0, T9 -- old
;ADDIU T0, R0, 1 -- new

.orga 0x6D5AC
.area 0x70
;T1, T2 can be used

	LUI V1, 0x8033
	LB T1, 0xDDF9(V1)
	
;check if level is BC1, C10, BC2, BB3 
	LI T2, 0x11
	BEQ T1, T2, yeswarp
	LI T2, 0x0A
	BEQ T1, T2, yeswarp
	LI T2, 0x13
	BEQ T1, T2, yeswarp
	LI T2, 0x22
	BEQ T1, T2, yeswarp
	NOP
	
nowarp:
	B endwarp
	ADDIU T0, R0, 1 ;set T0 to 1 -> no warp out
	
yeswarp:
	;warp only on star 4 and 5
	LW T1, 0x30(SP)
	LB T1, 0x188(T1)
	LI T0, 5
	BEQ T1, T0, yeswarp_s45
	LI T0, 4
	BEQ T1, T0, yeswarp_s45
	NOP
	B endwarp
	ADDIU T0, R0, 1 ;set T0 to 1 -> no warp out
	
yeswarp_s45:
	ADDIU T0, R0, 0 ;set T0 to 0 -> warp out

endwarp:
	J 0x24DC54
	NOP
.endarea