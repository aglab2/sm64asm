.orga 0x4205c
.area 0xA8, 0x0
	SH R0, 0xc686(at)
	SH R0, 0xC84A (AT)
	SH R0, 0xC68A (AT)
	SH R0, 0xC68C (AT)
	SH R0, 0xC770 (AT)
	SH R0, 0xC772 (AT)
	SH R0, 0xC774 (AT)
	SH R0, 0xC75E (AT)
	SH R0, 0xC760 (AT)
	SH R0, 0xC75A (AT)
	SH R0, 0xC75C (AT)
	SW R0, 0xC77C (AT)
	SW R0, 0xC780 (AT)
	SW R0, 0xC764 (AT)
	SW R0, 0xC76C (AT)
	SH R0, 0xC76A (AT)
	SH R0, 0xC768 (AT)
	SH R0, 0xC776 (AT)
	;SH R0, 0xC778 (AT)
	
	LHU T0, 0x8033B19E
	ADDI T0, T0, 0x9000
	ANDI T0, T0, 0xe000
	SH T0, 0xC778 (AT)
.endarea