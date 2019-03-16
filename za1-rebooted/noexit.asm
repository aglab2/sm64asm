.orga 0x97B6C
	JAL 0x8040CA00 ;LUI AT, 0x0800
	NOP			   ;AND T2, T1, AT

.orga 0x120CA00
.area 0x100, 0x00
	LUI AT, 0x0800
	AND T2, T1, AT
	BEQ T2, R0, end
	NOP
	
	LB T0, 0x8033B249
	LI T1, 0xF
	BNE T0, T1, end
	NOP
	
	LB T0, 0x8033B24A
	LI T1, 6
	BNE T0, T1, end
	NOP
	
	LI T2, 0
	
end:
	JR RA
	NOP
.endarea