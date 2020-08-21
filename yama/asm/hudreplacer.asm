.orga 0x21AD2C ;13000F2C
.dw 0x00080000
.dd 0x0C000000802AE908
.dw 0x1D000000
;bparam1 -- addr to hud

.orga 0x69908
.area 0x58
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	.f_SegmentedToVirtual 0x02000000
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	ADDU A0, R0, V0
	LW A1, 0x188(V1)
	JAL 0x80278504 ;dmacopy to 02
	ADDIU A2, A1, 0x4400
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea