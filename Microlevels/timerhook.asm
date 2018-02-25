;Hook for timer code to stop when it should stop

.orga 0xA99F4
.area 0x08
J 0x803046E0
NOP
.endarea

.orga 0xBF6E0
.area 0x100
	LUI T7, 0x8034
	LW T8, 0xB17C(T7)

	ADDIU T9, R0, 0x1302
	
	BEQ T8, T9, timerhook_noinc
	ADDIU T9, R0, 0x1303

	BEQ T8, T9, timerhook_noinc
	ADDIU T9, R0, 0x1307
	
	BEQ T8, T9, timerhook_noinc
	ADDIU T9, R0, 0x1904

	BEQ T8, T9, timerhook_noinc
	NOP
	
;regular behaviour
	BNEZ T3, timerhook_noded
	LUI T5, 0x8033

	LH T6, 0xDDF8(T5)
	ADDIU T5, R0, 0x08
	BEQ T5, T6, timerhook_win
	NOP
	
timerhook_actuallyded:
	J 0x802EE9FC ;0xA99FC -- ded
	NOP
	
timerhook_win:
	;add residue to timer
	LUI T5, 0x8041
	LHU T6, 0x04(T5)
	ADDIU T6, T6, 300
	SH T6, 0x04(T5)

	;stop survival
	LUI T7, 0x8041
	LB T6, 0xD(T7)
	BNE T6, R0, timerhook_actuallyded
	NOP
	ADDIU T6, R0, 1
	SB T6, 0xD(T7)

	;fix timer, let's give him a chance to win
	LUI T7, 0x8037
	ADDIU T5, R0, 300
	SH T5, 0x6E(T7)

	ADDIU A1, R0, 122
	LUI A2, 0x1300
	ADDIU A2, A2, 0x07F8
	JAL 0x8029EDCC
	ADD A0, R0, V1
	
	J 0x802EEA2C ;0xA9A18 -- no ded
	NOP

timerhook_noinc: ;this means we need to store a new time to global timer
	;fix timer back
	ADDIU T3, T3, 1
	SH T3, 0x006E(AT)

	;0x184 -- check if timer was fixed
	LB T8, 0x184(V1)
	BNE T8, R0, timerhook_noded
	
	LUI T5, 0x8041
	LHU T6, 0x04(T5)
	
;get starting timer
	LB T7, 0x188(V1)
	ADDIU T8, R0, 30
	MULT T8, T7
	MFLO T7
	
	SB T8, 0x184(V1)

;add to global timer local max and sub leftovers
	ADD T6, T6, T7
	SUB T6, T6, T3
	
	SH T6, 0x04(T5)
	
timerhook_noded:
	J 0x802EEA18 ;0xA9A18 -- no ded
	NOP
.endarea