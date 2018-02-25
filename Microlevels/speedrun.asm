;make this warp be linear from 0x10 to 0x23

;overwritten mole behaviour 3/3
.orga 0x21E838 ;behav 0x1304A38

.dw  0x00060000
.dw  0x11010009
.dw  0x102A2000
.dw  0x10050000
.dd  0x0C00000080304600
.dw  0x08000000
.dd  0x0C000000802AAA60
.dw  0x09000000

.orga 0xBF600
.area 0xE0
	ADDIU SP, SP, 0xFFE8
	SW RA, 0x14 (SP)
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)

	LUI T8, 0x8041
	LUI T9, 0x8034
	
	LB T0, 0xF(T8)
	BNE T0, R0, spdwarp_setwarp
	NOP
	
	LB T0, 0xB24B(T9)
	ADDIU T1, R0, 10
	BNE T0, T1, spdwarp_noset
	NOP
	
;Load current challenge - 1
spdwarp_setwarp:
	ADDIU T0, R0, 1
	SB T0, 0xF(T8)
	
	LW V0, 0x08(T8)
	ADDIU V0, V0, 0xF ;0x10 - 1

	SH V0, 0x188(V1)

spdwarp_noset:
;set lives to 0 and health to 8
	LUI T3, 0x8034
	SB R0, 0xB21D (T3)
	ADDIU T0, T0, 0x0880
	SH T0, 0xB21E (T3)

	LW RA, 0x14 (SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea