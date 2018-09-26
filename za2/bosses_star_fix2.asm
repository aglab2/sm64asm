.org 0x8C4C
	J 0x2BB988
	NOP
;ANDI T9, T8, 0x0400
;SLTU T0, R0, T9 -- old
;ADDIU T0, R0, 1 -- new

.orga 0x76988
.area 0x100
;T1, T2 can be used

	LUI V1, 0x8033
	LB T1, 0xDDF9(V1)
	
;check if level is BB1, BB2, VC, WC, MC, SA
	LI T2, 0x1E
	BEQ T1, T2, yeswarp
	LI T2, 0x21
	BEQ T1, T2, yeswarp
	LI T2, 0x23
	BEQ T1, T2, yeswarp
	LI T2, 0x1C
	BEQ T1, T2, yeswarp
	LI T2, 0x1D
	BEQ T1, T2, yeswarp
	LI T2, 0x12
	BEQ T1, T2, yeswarp
	LI T2, 0x14
	BEQ T1, T2, yeswarp
	NOP
	
nowarp:
	B endwarp
	ADDIU T0, R0, 1 ;set T0 to 1 -> no warp out
	
yeswarp:
	ADDIU T0, R0, 0 ;set T0 to 0 -> warp out

endwarp:
	J 0x24DC54
	NOP
.endarea