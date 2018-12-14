;Set lives to 69, no HUD

.orga 0x9E758
	J 0x802AE928
	NOP

.orga 0x9E76C
	NOP		

.orga 0x9E788
	;Store lives in T0, either 0 or 69
	SB T0, 0xB21D(V1)

.orga 0x69928
.area 0x40
	LUI V1, 0x8034
	LH T1, 0xB218(V1)
	SLTI T0, T1, 5
	BNE T0, R0, coinlives_0lives
	XORI T0, T0, 1
	
	ADDIU T0, R0, 0x45
	LB T2, 0xB21D(V1)
;Lives are not lost
	BEQ T2, T0, coinlives_0lives
	NOP
;Was <5 coins -> lives=0
	BEQ T2, R0, coinlives_0lives
	NOP
;Remove coins for lost life
	SUBI T1, T1, 5
	SH T1, 0xB218(V1)
	SH T1, 0xB262(V1)

coinlives_0lives:
	J 0x802E3760
	NOP
.endarea