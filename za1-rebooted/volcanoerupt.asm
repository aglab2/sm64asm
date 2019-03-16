.orga 0x120C200
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040C300
.dw 0x09000000


.orga 0x120C300
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	
	LI T0, 0x00001904
	LW T1, 0x8033B17C
	BEQ T0, T1, kys
	NOP
	
	LW T0, 0x154(V1)
	LI T1, 1350
	
	BGE T0, T1, kill
	LI A2, 0
	SUB A2, T1, T0
	B print
	NOP

kill:
	SH R0, 0x8033B21E
	B print
	NOP
	
kys:
	SW R0, 0x74(V1)
	B end

print:
	; print time
	LI A0, 10
	JAL 0x8040DF00
	LI A1, 210

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea