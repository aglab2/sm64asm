.orga 0x966F8
	LI T0, 8

.orga 0x96700
	SB T0, 0x1F(SP)

.orga 0x96730
	SUBIU T1, T0, 1

.orga 0x9673C
	SLT AT, T4, T3