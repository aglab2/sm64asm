.orga 0x120B200
	.dw 0x00090000
	.dd 0x2A0000000E0F1EB0
	.dw 0x0E437FFF
	.dw 0x11010001
	.dd 0x0C0000008040B280
	.dw 0x08000000
	.dd 0x0C0000008040B300
	.dd 0x0C000000803839CC
	.dw 0x09000000

.orga 0x120B280
.area 0x80, 0x00
	LH T9, 0x8032DDF4 ;current file
	LI T1, 0x70
	MULT T9, T1
	MFLO T1
	LI AT, 0x80207690 ;current eep base
	ADD AT, AT, T1
	
	LB T0, 0xB(AT)
	ANDI T1, T0, 0xA0
	BEQ T1, R0, end
	NOP
	
	LW V1, 0x80361160
	SW R0, 0x74(V1)

end:
	JR RA
	NOP
.endarea

.orga 0x120B300
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LI A0, 0x0E0F1E78
	LI A1, 2
	JAL 0x8040F100
	LI A2, 1
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea