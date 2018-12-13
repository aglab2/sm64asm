.orga 0x76988
	LUI T1, 0x8033
	LB T1, 0xDDF9(T1)

; --- repeat me to add new clause
	LI T2, 0x1E
	BEQ T1, T2, warpout
	NOP
; --- repeat me to add new clause
	LI T2, 0x21
	BEQ T1, T2, warpout
	NOP
	
	B end
	ADDIU T0, R0, 1
warpout:
	ADDIU T0, R0, 0
end:
	J 0x24DC54
	NOP