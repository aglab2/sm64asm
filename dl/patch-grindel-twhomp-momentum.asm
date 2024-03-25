; act 0 rewrite to update oVelY together with oPosY
.orga 0x682d0
	LW V1, 0x80361160
	LW T8, 0x144 (V1)
	LW T7, 0x154 (V1)
	ADDIU T9, T8, 0x0028
	SLT AT, T9, T7
	BEQ AT, R0, @@br
	NOP
	ADDIU T0, R0, 0x0001
	SW T0, 0x014C (V1)
	LUI AT, 0x40A0
	MTC1 AT, F6
	SW AT, 0xB0(V1)
	LWC1 F4, 0x00A4 (V1)
	ADD.S F8, F4, F6
	BEQ R0, R0, @@end
	SWC1 F8, 0x00A4 (V1)

@@br:
	LUI AT, 0x4120
	MTC1 AT, F16
	SW AT, 0xB0(V1)
	LWC1 F10, 0x00A4 (V1)
	ADD.S F18, F10, F16
	SWC1 F18, 0x00A4 (V1)
	
@@end:
	JR RA
	NOP

; act 1 patch to remove oVelY
.orga 0x68250
	SW R0, 0xB0(T6)

; act 1 patch to remove oVelY
.orga 0x681BC
	SW R0, 0xB0(T6)
