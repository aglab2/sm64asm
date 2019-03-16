.orga 0x120FD00
	.dw 0x00090000
	.dd 0x2a0000000E0F2030
	.dw 0x0E437FFF
	.dw 0x11010001
	.dw 0x08000000
	.dd 0x0C0000008040FD80
	.dd 0x0C000000803839CC
	.dw 0x09000000

.orga 0x120FD80
.area 0x80, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LI A0, 22.0
	LI A1, 10.0
	LI A2, -23.0
	JAL 0x8040FE00
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

; sin wave function
; A0 half amplitude
; A1 speed, higher slower
; A2 offset
.orga 0x120FE00
.area 0x100, 0x00
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SW A0, 0x18(SP)
	SW A1, 0x1C(SP)
	SW A2, 0x20(SP)
	
	LW V1, 0x80361160
	
	LW T0, 0x154(V1)
	
	MTC1 T0, F12
	cvt.s.w F12, F12

	MTC1 A1, F2 ; speed
	div.s F12, F12, F2
	
	JAL 0x80325480
	NOP
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	LWC1 F2, 0x18(SP) ; middle height
	mul.s F0, F2, F0
	LWC1 F2, 0x20(SP) ; offset
	add.s F0, F2, F0
	
	SWC1 F0, 0xA4(V1)

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea