; protect: 7B, 2C, 2D, 2E, 2F, 27
; og - 8037F164 8037F214
; delta = 283280

; filter
.orga 0x1202600
	LUI V1, 0x8039
	LW V1, 0xBE28(V1)

	LBU T0, 0x3(V1)
	
	ADD V0, R0, R0
	
	LI T1, 0x7B
	BEQ T1, T0, end
	ADDIU V0, V0, 1
	
	LI T1, 0x2C
	BEQ T1, T0, end
	ADDIU V0, V0, 1
	
	LI T1, 0x2D
	BEQ T1, T0, end
	ADDIU V0, V0, 1
	
	LI T1, 0x2E
	BEQ T1, T0, end
	ADDIU V0, V0, 1
	
	LI T1, 0x2F
	BEQ T1, T0, end
	ADDIU V0, V0, 1
	
	LI T1, 0x27
	BEQ T1, T0, end
	ADDIU V0, V0, 1

	ADD V0, R0, R0
	
end:
	JR RA
	NOP

;cmd 21
.orga 0x1202800
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	JAL 0x80402600
	NOP
	
	BEQ V0, R0, @@call_og
	NOP
	
	LUI  V1, 0x8040
	ADDU V1, V1, V0

	LB T0, 0x10(V1)
	BEQ T0, R0, @@call_og
	SB K1, 0x10(V1)
	
;ignore mode -- move to next cmd
	LUI V1, 0x8039
	LW T0, 0xBE28(V1)
	ADDIU T0, T0, 8
	SW T0, 0xBE28(V1)
	
	B @@ignore
	NOP

@@call_og:
	JAL 0x8037F164
	NOP
@@ignore:

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18


;cmd 22
.orga 0x1202900
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	JAL 0x80402600
	NOP
	
	BEQ V0, R0, @@call_og
	NOP
	
	LUI  V1, 0x8040
	ADDU V1, V1, V0

	LB T0, 0x10(V1)
	BEQ T0, R0, @@call_og
	SB K1, 0x10(V1)
	
;ignore mode -- move to next cmd
	LUI V1, 0x8039
	LW T0, 0xBE28(V1)
	ADDIU T0, T0, 8
	SW T0, 0xBE28(V1)

	B @@ignore
	NOP

@@call_og:
	JAL 0x8037F214
	NOP
@@ignore:

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18