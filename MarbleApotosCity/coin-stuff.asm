;replace "belongs to little cage probably", behav 0F2C
.orga 0x21AD2C
.dw 0x000B0000
.dw 0x11010041
.dd 0x0C000000802AE908
.dd 0x04000000130008FC

.orga 0x69908
.area 0x20
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	ADDIU T0, R0, 0x04
	SW T0, 0x144(V1)
	JR RA
	SW T0, 0x0F4(V1)
.endarea