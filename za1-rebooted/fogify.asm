.orga 0x120F200
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040F300
.dw 0x09000000

.orga 0x120F300
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	; V0 has addr to write fog stuff to
	JAL 0x80277F50
	LW A0, 0x188(V1)

	; do it every second
	LW T9, 0x154(V1)
	
	LI T0, 5
	DIV T9, T0
	
	MFHI T0
	BNE T0, R0, end
	NOP
	
	; T9 has amount of seconds
	MFLO T8
	
	; T6 will have A, T7 will have B
	; A=128000/(20+k)
	LI T0, 128000
	ADDI T1, T8, 20
	DIV T0, T1
	MFLO T6
	; B=(k-480)*256/(k+20)
	SUBI T0, T8, 480
	SLL  T0, T0, 8
	ADDI T1, T8, 20
	DIV T0, T1
	MFLO T7
	
	; store A and B
	SH T6, 0x4(V0)
	SH T7, 0x6(V0)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP