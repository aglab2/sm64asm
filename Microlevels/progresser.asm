;monty mole is ded!

;nullifier + warp checker
.orga 0x21E800 ;behav 0x4A00
.dw  0x00040000
.dd  0x0C000000803044C0
.dw  0x08000000
.dd  0x0C00000080304540
.dw  0x09000000

.orga 0xBF4C0
.area 0x80
	ADD T0, R0, R0

nullifier_loop:
	LUI T8, 0x8041
	ADD T8, T8, T0
	SW R0, 0x0(T8)

	ADDIU T0, T0, 4
	SLTI AT, T0, 0x40
	BNE AT, R0, nullifier_loop
	
	;account for Z button
	LUI T8, 0x8041
	ADDIU T0, T0, 0x20
	
	JR RA
	SB T0, 0x0C(T8)
.endarea


;konami code interpreter (lol)
.orga 0xBF540
.area 0x80
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LUI T8, 0x8041

	LUI AT, 0x8034
	LB T1, 0xAFA0(AT)
	
	LB T0, 0x0C(T8)
	OR T0, T0, T1
	SB T0, 0x0C(T8)
	
	;check for 0xFF... so adding 1 should make it 0
	ADDIU T0, T0, 1
	BNE T0, R0, konami_nowarp
	NOP
	
	ADDIU A1, R0, 0x0013
	LUI A0, 0x8033
	JAL 0x8024A9CC
	ORI A0, A0, 0xB170
	addiu t1, r0, 0x13
	sh t1, 0xb252 (AT)
	addiu a0, r0, 0xF
	sh a0, 0xB256 (at)
	
konami_nowarp:
	LW RA, 0x14 (SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea