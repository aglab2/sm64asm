; 2DB9DC decided whether hint should be shown

; always show hints, skip COURSE thing
.orga 0x969DC
	BEQ AT, R0, 0x96A14
	ADD S1, R0, AT
	; BEQZ	AT, 0x96AC0 ;BEQ AT, R0, 0x96A14

; more drawing stuff of COURSE
.orga 0x96AA8
.area 0x30, 0x00
	LW A2, 0x48(SP)
	BEQ S1, R0, xd
	LI A0, 0x5E
	LI A0, 0x75
xd:

	LI A1, 0x9D
	JAL 0x802D77DC
	ADDIU A2, A2, 3
.endarea

.orga 0x96A40
	JAL 0x8040CF00
	
.orga 0x120CF00
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	; T3 has level
	LI T0, 15
	BGE T0, T3, nochange
	NOP
	
; A0 = Get textbox address
	LI A0, 0x0403AA48
	SUBI T0, T3, 16
	SLL T1, T0, 8
	ADD A0, A0, T1
	
	; Find out which stars were collected
; eepbase
	LH T9, 0x8032DDF4 ;current file
	LI T1, 0x70
	MULT T9, T1
	MFLO T1
	LI AT, 0x80207690
	ADD AT, AT, T1
	ADD AT, AT, T3
	
	LB T4, 0xB(AT)
	ANDI T4, T4, 0x7F ; trim cannon

; find first not collected star and fix act on A0
repet:
	ANDI T5, T4, 1
	SRL T4, T4, 1
	BEQZ T5, foundact
	NOP
	B repet
	ADDI A0, A0, 0x20
foundact:
	
	JAL 0x80277F50
	NOP
	B end
	NOP
	
nochange:
	JAL 0x80277F50
	NOP

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea