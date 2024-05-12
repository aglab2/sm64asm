; lakitu
.orga 0x3b27c
	LW V1, 0x801ce0c8
	JALR V1
	ADDIU A0, SP, 0x48

; mario
.orga 0x3fa58
	LW V1, 0x801ce0d0
.orga 0x3fa78
	JALR V1
