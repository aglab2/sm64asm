.orga 0x120FB00
	.dw 0x00040000
	.dd 	0x0C0000008040F680
	.dw 0x08000000
	.dd 	0x0C0000008040FC00
	.dw 0x09000000

.orga 0x120FC00
.area 0x100
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LW V1, 0x80361160
	
; 10s delay
	LW T0, 0x154(V1)
	SLTI AT, T0, 10
	BNEZ AT, end
	NOP
	
; load bowser object to calc distance for death anim
	LW A0, 0x100(V1)
	JAL 0x8029E2F8
	ADDU A1, R0, V1
	
	LW A0, 0x100(V1)
	
	LI T0, 780.0
	MTC1 T0, F2
	c.lt.s F0, F2
	NOP
	bc1t killbowser
	NOP
	
; normal work with bowser
; init cs
	LW T0, 0x14C(A0)
	; kill bowser should not be interrupted
	LI T1, 0x4
	BEQ T0, T1, killbowser
	NOP
	LI T1, 0x6
	BEQ T0, T1, end
	NOP
	LI T1, 0x5
	BEQ T0, T1, end
	NOP
	
; always run
	LI T0, 0x7
	SW T0, 0x14C(A0)
	LI T1, 0xC237BD80
	SW T1, 0x54(A0)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

killbowser:
	LI T0, 0x4
	SW T0, 0x14C(A0)
	LW T1, 0xA0(V1)
	SW T1, 0xA0(A0)
	LW T1, 0xA8(V1)
	SW T1, 0xA8(A0)
	LW T0, 0x150(A0)
	LI T1, 2
	BNE T0, T1, end
	NOP
	B end
	SW R0, 0x074(V1)
	
.endarea

; bowser always runs :3
.orga 0x70F38
	B 0x70F50

.orga 0x70D7C
	B 0x70D94

.orga 0x70D34
	B 0x70D4C
