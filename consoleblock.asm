.orga 0x0021B338
	.dw 0x80402600

.orga 0x1202600
	LW T0, 0xA4100018
	BEQ T0, R0, not_console
	NOP
	
	LW V1, 0x80361160
	SW R0, 0x74(V1)

not_console:
	JR RA
	NOP

	NOP
	NOP
	NOP
	NOP
