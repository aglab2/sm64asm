; behav
.orga 0x120D000
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040D1000
.dw 0x09000000g

; layer 1 and layer 4 will work
.orga 0x120D080
	.dd 0xFC127E24FFFFF3F9
	.dd 0xFC70FEE1FFFFF3F9

.orga 0x120D100
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; V0 = combiner cmd
	LW V1, 0x80361160
	LW A0, 0x188(V1)
	JAL 0x80277F50
	NOP
	
	; T8 = target FC cmd address
	LI T8, 0x8040D080

	LW V0, 0x8033B1D8
	BEQ V0, R0, end	
	
	LH T9, 0x0(V0)
	LI T0, 0x7B
	
	BNE T0, T9, setfc
	NOP
	
	ADDIU T8, T8, 8
	
setfc:
	LW T0, 0x0(T8)
	SW T0, 0x0(V0)
	LW T1, 0x4(T8)
	SW T1, 0x4(V0)
	
end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

.endarea