.orga 0x2640C
	J 0x80402550	; MUL.S F8, F18, F16
	NOP				; SWC1 F8, 0x50(T2)
	
.orga 0x1202550
	LUI V1, 0x8034
	LW A0, 0xB1D8(V1)
	LH A0, 0x0(A0)
	LI A1, 0x2C
	BNE A0, A1, nowind
	NOP
	
	LWC1 F8, 0xB1B0(V1)
	LI A0, 20.0
	MTC1 A0, F10
	sub.s F8, F8, F10
	SWC1 F8, 0xB1B0(V1)
	
nowind:
	MUL.S F8, F18, F16
	SWC1 F8, 0x0050 (T2)

	J 0x8026B414
	NOP