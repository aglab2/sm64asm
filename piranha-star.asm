.orga 0xC8018
	ADDIU V1, R0, 4 ; star number
	LUI AT, 0x8034
	LWC1 F12, 0x8C54(AT)
	LUI A2, 0xC5C4  ; coordinates will be fucked up!
	ORI A2, A2, 0xE000
	JAL 0x802F2B88
	LWC1 F14, 0x8C58 (AT)
	SB V1, 0x188(V0)