; writes the star 802DBA90
; FA - hollow star
; FD - full star
; 9E - space

; act is at 80331620

; 802DBA40 - decides the textbox
.orga 0x96A1C
	JAL 0x80402600
	NOP

.orga 0x1202600
	LUI T9, 0x8033
	LBU T2, 0x1620(T9)
	
	LUI T8, 0x8034
	LH T8, 0xAFA2(T8)
	
	ANDI T7, T8, 0x0200
	BEQ T7, R0, noright
	NOP
	
	LI T6, 1
	BGE T6, T2, noright
	NOP
	
	B end
	SUBIU T2, T2, 1

noright:

	ANDI T7, T8, 0x0100
	BEQ T7, R0, noleft
	NOP
	
	LI T6, 8
	BGE T2, T6, noleft
	NOP
	
	B end
	ADDIU T2, T2, 1
noleft:
	
end:
	SB T2, 0x1620(T9)
	SB T2, 0x56(SP)
	SB T2, 0x5A(SP)
	JR RA
	NOP
	NOP
	NOP
	NOP
	NOP


; shift text a bit to fit in
.orga 0x96A70
	ADDIU A0, R0, 0x5B
.orga 0x96A88
	ADDIU A0, R0, 0x5B

; hook printing func
.orga 0x96A78
	JAL 0x80402900
.orga 0x96A90
	JAL 0x80402900

; text should be Star Space Act FF
.orga 0x1202900
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LI T0, 0x9E ; space
	SB T0, 0x1(A2)
	LI T0, 0xFF ; ending
	SB T0, 0x3(A2)
	
	; act and star is set already
	JAL 0x802D77DC
	NOP

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	NOP
	NOP
	NOP
	NOP