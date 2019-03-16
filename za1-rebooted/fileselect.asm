;801A81A0 - selected act
; set act to 6 by default
.orga 0x22700C
	JAL 0x8040EB00
	NOP

.orga 0x120EB00
	LUI T0, 0x801B
	LI T1, 5
	JR RA
	SB T1, 0x81A4(T0)
	NOP
	NOP	
	NOP
	NOP	
	NOP
	NOP	
	NOP
	NOP