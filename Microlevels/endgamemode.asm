;rip 2/3 parts of mole
.orga 0x21E81C ;behav 0x4A1C
.dw  0x00040000
.dd  0x0C000000803044C0 ;nullifier from progressor.asm
.dw  0x08000000
.dd  0x0C000000803045C0 ;set hard mode stuff
.dw  0x09000000

;End game mode set!
.orga 0xBF5C0
.area 0x40

;Set lives to 1
	LUI T3, 0x8034
	ADDIU T0, R0, 1
	SB T0, 0xB21D (T3)
;Set hp to 8
	ADDIU T0, T0, 0x0880
	SH T0, 0xB21E (T3)

;Set speedrun mode stuff
	LUI T3, 0x8041
	ADDIU T0, R0, 1
	SB T0, 0x0E (T3) ;set whatever not 0
	
	JR RA
	NOP
.endarea