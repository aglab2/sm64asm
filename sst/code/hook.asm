.orga 0x21CCE0
	.dw 0x80408000

; Timer
.orga 0x57E9C
	NOP
.orga 0x57EC0
	NOP
	
.orga 0x4688
	SB K1, 0xB25E(AT)
.orga 0x4694
	NOP

.orga 0x6194
	ORI T2, T1, 0x40

.orga 0x8C7C
	SB R0, 0xEE(T5)
	
.orga 0x5024
	B 0x503C
	
; HUD
.orga 0x9EDB0
	NOP
.orga 0x9EDC8
	NOP
.orga 0x9EDE0
	NOP
.orga 0x9EA24
	NOP
	
; No Music
.orga 0xD83F4
	LI A1, 0
	
; Stars always yellow
.orga 0xAD548
	B 0xAD56C
.orga 0x65FC4
	B 0x65Fd4
	
; No Pause Menu in OW
.orga 0x97C30
	NOP
.orga 0x97C3C
	NOP
.orga 0x97C48
	NOP
	
; No Pasue Menu in Stage
.orga 0x97B50
	NOP
.orga 0x97B58
	NOP