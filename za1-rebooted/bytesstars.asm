; bparam1 = offset in eep
; bparam2 = mask to check
; bparam3 = star count to set
.orga 0x120B900
.dw 0x00090000
.dd 0x0C0000008040BA00
.dd 0x0400000013000B10

.orga 0x120BA00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LW V1, 0x80361160
	
; eepbase
	LH T9, 0x8032DDF4 ;current file
	LI T1, 0x70
	MULT T9, T1
	MFLO T1
	LI AT, 0x80207690 ;current eep base
	ADD AT, AT, T1
	
	LB T0, 0x188(V1)
	ADD AT, AT, T0
	LB T9, 0x0(AT)
	
	LB T1, 0x189(V1)
	AND T2, T9, T1
	BNE T2, R0, nolockdoor
	NOP
	
	LB T3, 0x18A(V1)
	SB T3, 0x188(V1)
	B end
	SB T3, 0x189(V1)
	
nolockdoor:
	SB R0, 0x188(V1)
	SB R0, 0x189(V1)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18