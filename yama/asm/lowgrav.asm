;119AC - tj 4.0
;1171C - lj 2.0

.orga 0x1199C
	JAL 0x80402d00
	NOP

.orga 0x1202d00
.area 0x80
	LUI AT, 0x8034
	LB AT, 0xB249(AT)
	
	LI V1, 0x1f
	BNE AT, V1, tj_normal_value
	NOP
	
	LUI AT, 0x8034
	LB AT, 0xB24A(AT)
	
	LI V1, 0x2
	BNE AT, V1, tj_normal_value
	
	; z coordinate
	LUI AT, 0x8034
	LWC1 F6, 0xB1B0(AT)
	neg.s F6, F6
	
	LI AT, 2166.0
	MTC1 AT, F4
	div.s F6, F6, F4
	
	LI AT, 3.46
	MTC1 AT, F4
	add.s F6, F6, F4
	
	B tj_end
	
tj_normal_value:
	LI AT, 4.0
	MTC1 AT, F6

tj_end:
	JR RA
	NOP
.endarea






.orga 0x1170C
	JAL 0x80402d80
	NOP

.orga 0x1202d80
.area 0x80
	LUI AT, 0x8034
	LB AT, 0xB249(AT)
	
	LI V1, 0x1f
	BNE AT, V1, lj_normal_value
	NOP
	
	LUI AT, 0x8034
	LB AT, 0xB24A(AT)
	
	LI V1, 0x2
	BNE AT, V1, lj_normal_value
	
	; z coordinate
	LUI AT, 0x8034
	LWC1 F10, 0xB1B0(AT)
	neg.s F10, F10
	
	LI AT, 2166.0 * 2.0
	MTC1 AT, F4
	div.s F10, F10, F4
	
	LI AT, 3.46 / 2.0
	MTC1 AT, F4
	add.s F10, F10, F4
	
	B lj_end
	
lj_normal_value:
	LI AT, 2.0
	MTC1 AT, F10

lj_end:
	JR RA
	NOP
.endarea