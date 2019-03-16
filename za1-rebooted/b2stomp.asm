; set audip
.orga 0x3887C
.area 0x5C, 0x00
	LH T0, 0x8032DDF8
	LI T1, 0x21
	
	BEQ T0, T1, abnormal
	NOP
	
	LUI AT, 0x8034
	SLL T6, S0, 6
	ADDU AT, AT, T6
	LW T7, 0xBB18(AT)
	LW T8, 0xBB1C(AT)
	B end
	LW T9, 0xBB20(AT)
	
abnormal:
	LI T7, 0xC2136900
	LI T8, 0x44EDE9B7
	LI T9, 0xC609B632
end:

	SW T7, 0x54(T4)
	SW T8, 0x58(T4)
	SW T9, 0x5C(T4)
.endarea