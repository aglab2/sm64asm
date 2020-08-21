.orga 0x96AA0
	JAL 0x80404900

.orga 0x1204900
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LHU T0, 0x8033bac6
	LBU T1, 0x80331620
	LI T2, 7
	BNE T2, T1, not7
	NOP
	
	LI A2, 0x80404700 - 0x20
	SLL T4, T0, 5
	B end
	ADD A2, A2, T4
not7:

	LI T2, 8
	BNE T2, T1, not8
	NOP
	
	LI T3, 15
	BEQ T3, T0, notc15
	NOP
	
	LI A2, 0x804048f0
	B end
	NOP
notc15:
	LI A2, 0x804048e0

not8:
end:

	JAL 0x802d77dc
	nop
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop