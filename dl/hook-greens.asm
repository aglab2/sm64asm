; hook interaction to change action
.orga 0x8dec
	LUI V1, 0x801d
.orga 0x8e08
	LW V1, 0xe000(V1)
.orga 0x8e14
	SLL T4, T2, 1
.orga 0x8e1c
	JALR V1