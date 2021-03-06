.orga 0x21BE38 ;2038
	.dw 0x00090000
	.dd 0x0C000000802BEC34
	.dd 0x0400000000402d00

.orga 0x79C34
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	LB T0, 0x188(V1)
	JR RA
	SB T0, 0x18A(V1)
	
.orga 0x1202d00
	.dw 0x102A0004 
	.dw 0x110100C9 
	.dd 0x27260000030156C0
	.dw 0x28000000
	.dd 0x2A0000000301CE78 
	.dd 0x2300000000500064 
	.dw 0x10050000
	.dw 0x0E4303E8 
	.dw 0x2D000000 
	.dd 0x0C000000802ACC3C 
	.dw 0x08000000 
	.dd 0x0C00000080402d50
	.dd 0x0C000000802ACAC8
	.dw 0x09000000

	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LUI T0, 0x8033
	LH T0, 0xDDF4(T0)
	SUBI T0, T0, 1
	LI T1, 0x70
	MULT T0, T1
	MFLO T2
	
	LUI V0, 0x8020 ;0x7700
	ADDU V0, V0, T2
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	LB T3, 0x18A(V1)
	ADDU V0, V0, T3
	
	LB T4, 0x7700(V0)
	ANDI T4, T4, 0xFF
	BEQ T4, R0, closedoor
	ADDIU T5, R0, 210
	
opendoor:
	B setdoor
	ADDU T5, R0, R0

closedoor:

setdoor:
	SB T5, 0x188(V1)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP