.orga 0xF12F8
.area 256, 0x16
.endarea

; Alter these values to setup textbox for star count
.orga 0xF12F7 + 1
.db 0x18

.orga 0xF12F7 + 3
.db 0x19

.orga 0xF12F7 + 8
.db 0x1A

.orga 0xF12F7 + 30
.db 0x1B

.orga 0xF12F7 + 50
.db 0x1C

.orga 0xF12F7 + 70
.db 0x1D

; toad in water room
.orga 0xF12F7 + 180
.db 33

; door to bowser
.orga 0xF12F7 + 181
.db 45

; reds to inside in ow
.orga 0xF12F7 + 182
.db 54


.orga 0x9584
; T2 - star count + 1
; so it will load from 803362F8+starcount+1
	LUI AT, 0x8033
	ADDU AT, AT, T2
	LBU T2, 0x62F8(AT)
	SLL T2, 16
	SW T2, 0x24(SP)
	B 0x9604
	NOP