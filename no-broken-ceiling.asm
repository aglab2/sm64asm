.orga 0x112a0
	LW T0, 0x0050 (SP)
	MTC1 R0, F18
	LWC1 F16, 0x004C (T0)
	C.LE.S F18, F16
	NOP
	BC1F 0x00011308
	NOP
	MTC1 R0, F4
	LW T1, 0x0050 (SP)
	SWC1 F4, 0x004C (T1)

.orga 0x56f64
	ADDIU SP, SP, 0xFFB8
	SW RA, 0x0024 (SP)
	SW S0, 0x0020 (SP)
	JAL 0x00383CB4
	NOP
	SWC1 F0, 0x0038 (SP)
	JAL 0x00383CB4
	NOP
	LUI AT, 0x4120
	MTC1 AT, F4
	LUI AT, 0x41C8
	MTC1 AT, F8
	MUL.S F6, F0, F4
	LUI T6, 0x8036
	LW T6, 0x1160 (T6)
	ADD.S F10, F6, F8
	SWC1 F10, 0x00B8 (T6)
	LUI T7, 0x8036
	LW T7, 0x1160 (T7)
	LW S0, 0x014C (T7)
	BEQ S0, R0, 0x00056FD0
	NOP
	ADDIU AT, R0, 0x0001
	BEQ S0, AT, 0x00056FF8
	NOP
	BEQ R0, R0, 0x000570C0
	NOP
	LUI AT, 0x8033
	JAL 0x0029F430
	LWC1 F12, 0x777C (AT)
	LUI T8, 0x8036
	LW T8, 0x1160 (T8)
	LW T9, 0x014C (T8)
	ADDIU T0, T9, 0x0001
	SW T0, 0x014C (T8)
	BEQ R0, R0, 0x000570C0
	NOP
	LUI T1, 0x8034
	LW T1, 0xCBD0 (T1)
	ADDIU T2, SP, 0x0030
	SW T2, 0x0010 (SP)
	ADDIU A2, SP, 0x0034
	ADDIU A3, SP, 0x0032
	
.orga 0x10c44
	B 0x10d74
	LI V0, 2
	
.orga 0x57030
	LUI A0, 0x8034
	LW A0, 0xCBD0(A0)
	LH T6, 0x30(SP)