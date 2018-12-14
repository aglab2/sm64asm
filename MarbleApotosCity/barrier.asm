;klepto pt2 behav 5324
.orga 0x21F124
.word 0x00090000
.word 0x2A000000
.word 0x07003DC0 ;fill me
.word 0x0E437FFF
.word 0x08000000
	.word 0x0C000000
	.word 0x80310898
.word 0x09000000

.orga 0xCB898
.area 0x100
	ADDIU SP, SP, 0x18
	SW RA, 0x04(SP)
	
	LUI T7, 0x8034
	LB T7, 0xB249(T7) ;current level
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI V1, 0x8020
	ADDI V1, V1, 0x7700 ;current eep base

barrier_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, barrier_fileselectend
	NOP
	ADDI V1, V1, 0x70
	B barrier_fileselectloop
	NOP
barrier_fileselectend:

	ADDIU V1, V1, 0x21
	LB T0, 0x0(V1)
	BEQ T0, R0, barrier_set
	NOP
	
	JAL 0x802E6AF8
	NOP
	
barrier_set:
	JAL 0x803839CC
	NOP
	
	LW RA, 0x04(SP)
	JR RA
	ADDIU SP, SP, -0x18
.endarea