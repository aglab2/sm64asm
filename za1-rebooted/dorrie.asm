; unlock dorrie
.orga 0xC6418
	B 0xC6488

.orga 0xC5F80
	ADDIU T2, R0, 0x15

.orga 0xC6000
	ADDIU T8, R0, 0x0

; no gp :[
.orga 0xC6488
	ADD V0, R0, R0