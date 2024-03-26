.orga 0xDB3BC
	NOP
	JAL 0x80405900
	NOP

.orga 0x1205900
	LI AT, 7
	BNE AT, S4, @@nopatch
	NOP
	
	LI AT, 0xE
	BEQ AT, S5, @@patch
	NOP
	LI AT, 0xF
	BEQ AT, S5, @@patch
	NOP
	LI AT, 0x6
	BEQ AT, S5, @@patch
	NOP
	LI AT, 0x7
	BEQ AT, S5, @@patch
	NOP
	
	B @@nopatch

@@patch:
	LUI AT, 0x3e99
	B @@end
	SW AT, 0x20(A1)
	
@@nopatch:
	SWC1 F22, 0x20(A1)

@@end:
	LUI AT, 0x3f00
	JR RA
	MTC1 AT, F10

	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

.orga 0xdb0b4
	JAL 0x80405980
	NOP
	NOP

.orga 0x1205980
	LI AT, 7
	BNE AT, S4, @@nopatch
	NOP
	
	LI AT, 0xE
	BEQ AT, S5, @@patch
	NOP
	LI AT, 0xF
	BEQ AT, S5, @@patch
	NOP
	LI AT, 0x6
	BEQ AT, S5, @@patch
	NOP
	LI AT, 0x7
	BEQ AT, S5, @@patch
	NOP
	
	B @@nopatch

@@patch:
	LUI AT, 0x3e99
	B @@end
	SW AT, 0x20(T8)
	
@@nopatch:
	SWC1 F22, 0x20(T8)

@@end:
	LUI AT, 0x3f00
	JR RA
	MTC1 AT, F16

	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
