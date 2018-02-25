;overwrite klepto behav with gp bonk
;use behav 5310, model 0 in tt64

.orga 0x21F110;behav 0x13005310
.word 0x00040000
.word 0x08000000
.word 0x0C000000
	.word 0x80310498
.word 0x09000000

.orga 0xCB498
.area 0xB0
	LUI T1, 0x8034
	LW T2, 0xB17C(T1)
	
	;check for jumps
	LUI T0, 0x0300
	ADDIU T0, T0, 0x0880
	BEQ T0, T2, nogp_bonk
	NOP
	ADDIU T0, T0, 0x1
	BEQ T0, T2, nogp_bonk
	NOP
	ADDIU T0, T0, 0x1
	BEQ T0, T2, nogp_bonk
	NOP
	ADDIU T0, T0, 0x6
	BEQ T0, T2, nogp_bonk
	NOP
	
	;check for gp
	LUI T0, 0x0080
	ADDIU T0, T0, 0x08A9
	BEQ T0, T2, nogp_bonk
	NOP
	
	;check for sf
	LUI T0, 0x0100
	ADDIU T0, T0, 0x0883
	BEQ T0, T2, nogp_bonk
	NOP

	ADDIU T0, T0, 0x4
	BEQ T0, T2, nogp_bonk
	NOP

	
	B nogp_nobonk
	NOP

nogp_bonk:
	LUI T0, 0x0102
	ADDIU T0, T0, 0x08B0
	SW T0, 0xB17C(T1)
	
nogp_nobonk:
	JR RA
	NOP
.endarea