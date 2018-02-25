; rip ukiki, behav 0x1CB0
.org 0x21BAB0
.dw 0x00040000
.dw 0x08000000
.dd 0x0C000000802B261C
.dw 0x09000000

.orga 0x6D61C
.area 0x70, 0x00
;play sfx
	ADDIU SP, SP, -0x18
	SW RA, 0x08(SP)
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	LUI V0, 0x8034
	
;load object height
	LW T0, 0xA4(V1)
	MTC1 T0, F4

;load maro height
	LW T1, 0xB1B0(V0)
	MTC1 T1, F6
	
;if height is lower than objects place, ignore
	c.lt.s F6, F4
	BC1T speedrun_no
	NOP
	
	LUI T0, 0x0102
	ADDIU T0, T0, 0x08B0
	SW T0, 0xB17C(V0)
	
;SPEEDRUNNERS HATE HIM
	LUI A0, 0x243D
	JAL 0x802CA190
	ORI A0, A0, 1

speedrun_no:
	LW RA, 0x08(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea