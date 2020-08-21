.org 0x105F4
	J 0x802F336C
	LW A0, 0x18(SP)

;pitoune replace
.orga 0xAE36C
.area 0x100, 0x00
;quicksand cap
	LB T0, 0x07(A0)
	ANDI T0, T0, 0x02
	BEQ T0, R0, quicksand_yes
	NOP
;Jump to regular ground (sandy actually)
	J 0x802554B0 ;104B0
	NOP

quicksand_yes:
;patch quicksand from downwarps
	;ymax of triangle
	LUI T9, 0x8034
	LW T0, 0xB1D8 (T9)
	LH T0, 0x08 (T0)
	SLL T0, T0, 2
	ADDI T0, T0, 10

	;get maros Y
	LW T1, 0xB1B0(T9)
	MTC1 T1, F10
	cvt.w.s F12, F10
	MFC1 T1, F12
	
	SLTU AT, T0, T1
	BEQZ AT, quicksand_fini
	NOP
	J 0x802554B0 ;104B0
	NOP

quicksand_fini:
	JAL 0x2521A0
	NOP
	J 0x802555FC
	NOP
.endarea