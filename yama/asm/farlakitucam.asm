.orga 0x3C62C
	JAL 0x80405b00

.orga 0x1205b00
	ADDIU SP, SP, -0x20
	SW RA, 0x14(SP)

	LB T0, 0x8033B249
	LB T2, 0x8033B24A
	LI T1, 0xe
	BNE T0, T1, notveryfar
	NOP
	LI T3, 1
	BEQ T2, T3, notveryfar
	NOP
	LI T3, 3
	BEQ T2, T3, notveryfar
	NOP	

veryfar:
	LUI AT, 0x44a7
	mtc1 at, f12
	li a1, 0x0200
	B end
	nop

notveryfar:
	LI T1, 0xc
	BNE T0, T1, notveryclose
	NOP

veryclose:
	LUI AT, 0x4308
	mtc1 at, f12
	li a1, 0x0900
	B end
	nop

notveryclose:

end:
	JAL 0x80281188
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x20
	NOP
	NOP
	NOP
	NOP