.orga 0x120F600
	.dw 0x00040000
	.dd 	0x0C0000008040F680
	.dw 0x08000000
	.dd 	0x0C0000008040F700
	.dw 0x09000000

.orga 0x120F680
.area 0x80
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; search bowser
	LI A0, 0x13001850
	JAL 0x8029F95C
	NOP
	
	LW V1, 0x80361160
	SW V0, 0x100(V1)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

.orga 0x120F700
.area 0x100
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LW V1, 0x80361160
	
	; let bowser start up
	LW T0, 0x154(V1)
	SLTI AT, T0, 10
	BNEZ AT, end
	NOP
	
	; load bowsey and his data
	LW A0, 0x100(V1)
	LW T0, 0x14C(A0)
	
	; init cs
	LI T1, 0x6
	BEQ T0, T1, end
	NOP
	LI T1, 0x5
	BEQ T0, T1, end
	NOP
	
	; reset timer on action end
	BNE T0, R0, noresetcycle
	NOP
	
	SW R0, 0x154(V1)
noresetcycle:

	LW T0, 0x154(A0)
	LI T1, 52 ; bowser drops on ground
	BNE T0, T1, noswitchblocks
	NOP
	
	;switch switchblocks
	LUI T0, 0x8040
	LB T1, 0x0(T0)
	LI T2, 2
	SUB T3, T2, T1
	SB T3, 0x0(T0)

noswitchblocks:
	; jump up straight
	LI T0, 0xD
	SW T0, 0x14C(A0)
	
	LW A1, 0x80361158
	; look at mario
	JAL 0x8029E694
	NOP

	LW A0, 0x100(V1)
	SH V0, 0xCA(A0)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea
	
	