.orga 0x105f4
.area 0x20, 0x0
	; m->flags & MARIO_VANISH_CAP
	LW T0, 0x18(SP)
	LW T1, 0x4(T0)
	ANDI T2, T1, 0x2
	BEQ T2, R0, 0x105c8
	NOP
.endarea

.orga 0x18718
.area 0x3c, 0x0
	; m->flags & MARIO_VANISH_CAP
	LW T1, 0x4(A0)
	ANDI T2, T1, 0x2
	BNE T2, R0, 0x18778 ; <- not qs

	LI T3, 0x23
	LW T7, 0x68(A0)
	LH T8, 0x0(T7)
	BNE T8, T3, 0x18778
	LW T9, 0xC(A0)
	ANDI T0, T9, 2
	BEQ T0, R0, 0x18778
	LI T4, 0x21312
	BEQ T9, T4, 0x18778
	NOP
.endarea