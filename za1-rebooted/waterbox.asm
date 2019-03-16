; Prepare waterbox address
.orga 0x7D930
.area 0x3C, 0x00
	LW V0, 0x80361160
	LW V1, 0x80361184
	LB T0, 0x188(V0)
	LI T1, 0xC
	MULT T0, T1
	MFLO T3
	ADD V1, V1, T3
.endarea

; Load from prepared address
.orga 0x7D998
	LH T5, 0xC(V1)
.orga 0x7D9FC
	SH T4, 0xC(V1)