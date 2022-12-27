.orga 0x1202140
	JAL 0x80402800

.orga 0x120214C
	NOP ; do not set V0, I will do it from the hook

.orga 0x1202800
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; A0 = 0x80570000
	; A1 = from
	; A2 = to
	LI T1, 0x0097F0C4
	BNE T1, A1, regular
	LI T2, 0x009E1FD4
	BNE T2, A2, regular
	NOP

patchd:
	; load content to 0x80440000 instead, there is enough space
	JAL 0x80278504
	LUI A0, 0x8044
	B ehd
	LUI V0, 0x44

regular:
	JAL 0x80278504
	NOP
	LUI V0, 0x57

ehd:
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
