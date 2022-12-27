.orga 0x5BD4
	JAL 0x80404800
	NOP
.orga 0x5B48
	JAL 0x80404800
	NOP

; hook is set into param preparation for 'play_transition' call
.orga 0x1204800
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SW A0, 0x18(SP)
	SW A1, 0x1C(SP)

	LUI A0, 0x8034
	JAL 0x8024a584 ; music_changed_through_warp
	LH A0, 0xB256(A0)
	SLTIU S0, V0, 1
	SW S0, 0x2C+0x28(SP)

	LW A0, 0x18(SP)
	LW A1, 0x1C(SP)	
	LI A2, 0
	LI A3, 0

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP