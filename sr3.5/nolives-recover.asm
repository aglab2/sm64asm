;Set lives to 69, no HUD

.orga 0x9E758
.area 0x4
LUI T0, 0x8034
.endarea

.orga 0x9E76C
.area 0x4
ADDIU T1, R0, 0x45
.endarea

.orga 0x9E788
.area 0x4
JAL 0x80404500
;SB T1, 0xB21D(T0)
.endarea

.orga 0x1204500
	LB T2, 0xB21D(T0)
	SB T1, 0xB21D(T0)
	BGE T1, T2, norestorehp
	ADDIU T3, R0, 0x0880
	SH T3, 0xB21E(T0)
	
norestorehp:
	JR RA
	NOP