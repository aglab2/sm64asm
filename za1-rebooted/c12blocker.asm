.orga 0x120B400
	.dw 0x00090000
	.dd 0x2A0000000E0D2AF0
	.dw 0x0E437FFF
	.dw 0x11010001
	.dw 0x08000000
	.dd 0x0C0000008040B480
	.dd 0x0C000000803839CC
	.dw 0x09000000

.orga 0x120B480
.area 0x80, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LI A0, 0x0E0D2A30
	LI A1, 2
	JAL 0x8040F100
	LI A2, 1
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea