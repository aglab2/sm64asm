.orga 0x3516c
	LI V1, 0x1ff0fffe
	LUI T8, 0x8033
	LH T8, 0xDDF4 (T8)
	LUI V0, 0x8020
	SLL T9, T8, 0x3
	SUBU T9, T9, T8
	SLL T9, T9, 0x4
	ADDU V0, V0, T9
	LW V0, 0x7698 (V0)
	JR RA
	OR V0, V0, V1
