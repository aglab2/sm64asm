.orga 0x7c3b8
	JAL 0x80403b00
	NOP

.orga 0x1203b00
	LB T3, 0x18B(T4)
	BNE T3, R0, ehd
	NOP

	LI T3, 4

ehd:
	SUBI T3, T3, 1
	JR RA
	SW T3, 0xF0(T4)
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	
	

.orga 0x7c8f8
	JAL 0x802AAE8C
.orga 0x7c918
	JAL 0x80403b80

.orga 0x1203b80
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	SLTI AT, A3, 3
	BNE AT, R0, noclamp
	NOP
	LI A3, 3
	
noclamp:
	JAL 0x802AE0CC
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
.orga 0x7c334
	JAL 0x80403c00
	LW T9, 0x144(T8)

.orga 0x1203c00
	BNE T9, 3, ehd1
	NOP
	
	LI T6, 15
	LH T7, 0x8033bac6
	BNE T7, T6, c15
	LI T9, 4
	LI T9, 12
c15:

ehd1:
	JR RA
	SW T9, 0xF0(T8)
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP