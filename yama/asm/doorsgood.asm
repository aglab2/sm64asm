.orga 0xF12F8
.area 256, 0x16
.endarea

; Alter these values to setup textbox for star count
.orga 0xF12F7 + 3
.db 25

.orga 0xF12F7 + 8
.db 26

.orga 0xF12F7 + 30
.db 27

.orga 0xF12F7 + 50
.db 28

.orga 0xF12F7 + 121
.db 29

.orga 0xF12F7 + 127
.db 24

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