;0E003000
;07000000=AED714
; texture needed 07003010=AF0724
;dl starts at 0700DB70=AFB284
; FB cmd address 0700F150=AFC864

; 0007E200 = 14000000
; 0007E4D0 = 140002D0

; 21F4C0 = 8016F000
; 21FD70 = 8016F8B0 <- should hook
; 21FE44 = 8016F984 <- can write here
.orga 0x21FD70
	JAL 0x8016F984

.orga 0x21FE44
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SW A0, 0x18(SP)
	SW A1, 0x1C(SP)
	SW A2, 0x20(SP)
	SW A3, 0x24(SP)
	
; should be fully shown
	LI T0, 0x3F800000
	BNE T0, A1, end
	NOP
	
	LI A0, 0x0700F150
	JAL 0x80277F50
	NOP
	
	LBU T0, 0x4(V0)
	LI T1, 250
	BEQ T0, T1, end
	NOP
	
	ADDIU T0, T0, 10
	SB T0, 0x4(V0)
	SB T0, 0x5(V0)
	SB T0, 0x6(V0)

end:
	LW A0, 0x18(SP)
	LW A1, 0x1C(SP)
	LW A2, 0x20(SP)
	JAL 0x80325924
	LW A3, 0x24(SP)

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28