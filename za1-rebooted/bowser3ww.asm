.orga 0x5B50
	JAL 0x8027B1A0
	
.orga 0x5B34
	JAL 0x8040DB00 ;LI T3, 0xF1
	;LUI AT, 0x8034

.orga 0x120DB00
.area 0x100, 0x00
	ADDIU SP, SP, -0x20
	SW RA, 0x14(SP)
	
; b3 special caser
	LUI T0, 0x8034
	LB T0, 0xB249(T0)
	
	LI T1, 0x22
	BNE T0, T1, normal
	NOP
	
; flag should be set
	LUI T1, 0x8040
	LW T0, 0x30(T1)
	
	BEQ T0, R0, normal
	NOP
	
; abnormal warp
	LI T3, 0xE1
	B end
	SW R0, 0x30(T1)
	
normal:
	LI T3, 0xF1
	
end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x20
.endarea