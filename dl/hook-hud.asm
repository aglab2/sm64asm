.orga 0x9eddc
	LW V1, 0x801ce01c
	JALR V1
	NOP
	LI T9, 0 ; dont render keys

; dont render coins and pass A0 param to render hook
.orga 0x9edbc
	andi a0, t4, 2
.orga 0x9edc8
	NOP