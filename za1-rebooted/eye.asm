; don't drop homing
;.orga 0x61BD8
;	NOP
.orga 0x61870
	B 0x61888

; inf timer
;.orga 0x61560
;	ADDIU T2, R0, 0x7FFF
.orga 0x616DC
	ADDIU T7, R0, 0x7FFF