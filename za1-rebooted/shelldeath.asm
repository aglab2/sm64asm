.orga 0x21BD5C
	.dd 0x0C0000008040B700

.orga 0x120B700
.area 0x100, 0x00
	ADDIU SP, SP, -0x20
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	LB T0, 0x14F(V1)
	BNE T0, R0, normal
	NOP
	
	LW T1, 0x154(V1)
	SLTI AT, T1, 350
	BNE AT, R0, normal
	NOP
	
	B end
	SW R0, 0x74(V1)

normal:
	JAL 0x802BD680
	NOP

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x20
.endarea