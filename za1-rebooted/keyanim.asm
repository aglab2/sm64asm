;80259904

;8032DD80 - stored id for eeprom
; should be any other secret stage?
.orga 0x34C94
	JAL 0x8040EA00
	NOP

.orga 0x120EA00
	LW T3, 0x30(SP)
	LUI AT, 0x8033
	LI T4, 0xF
	BEQ T3, T4, checklevel
	NOP
	LI T4, 0x10
	BEQ T3, T4, checklevel
	NOP
	B end
	NOP
	
checklevel:
	LH T5, 0xDDF8(AT)
	LI T4, 0x1E
	BEQ T4, T5, end
	NOp
	LI T4, 0x21
	BEQ T4, T5, end
	NOP
	
	LI T3, 0x11

end:
	JR RA
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP