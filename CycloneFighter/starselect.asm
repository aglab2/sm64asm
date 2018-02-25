.orga 0x226FEC
.area 0x1C, 0x00
	;set max star to 3
	LUI A0, 0x801C
	ADDIU A1, R0, 0x03
	SB A1, 0x9AA1(A0)

	;load "file" with 4 stars
	ADDIU V0, R0, 0x0F
.endarea

.orga 0x2271E4
	ADDIU A2, R0, 0x7A

.orga 0x2272CC
	;load "file" with 4 stars
	ADDIU V0, R0, 0x0F