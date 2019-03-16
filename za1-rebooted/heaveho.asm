.orga 0x21B398
	.dd 0x0C0000008040B800

.orga 0x120B800
.area 0x100, 0x0
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	LB T0, 0x188(V1)
	BEQ T0, R0, end
	NOP
	
	LW T0, 0x154(V1)
	BNE T0, R0, setpos
	NOP
	
	LW T0, 0xA0(V1)
	SW T0, 0x100(V1)
	LW T0, 0xA4(V1)
	SW T0, 0x104(V1)
	LW T0, 0xA8(V1)
	SW T0, 0x108(V1)
	
setpos:
	LI T0, 3
	LW T1, 0x14C(V1)
	BEQ T0, T1, notflip
	NOP
	LI T0, 2
	SW T0, 0x14C(V1)
	SW R0, 0x154(V1)

notflip:
	LW T0, 0x100(V1)
	SW T0, 0xA0(V1)
	;LW T0, 0x104(V1)
	;SW T0, 0xA4(V1)
	LW T0, 0x108(V1)
	SW T0, 0xA8(V1)

end:
	JAL 0x802B2278
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea