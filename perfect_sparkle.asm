; spawn_sparkles
.orga 0x1204700
.area 0x80
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW A0, 0x80361158
	LI A2, 0x130009e0
	JAL 0x8029edcc
	LI A1, 0x95
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

; act_dive_slide
.orga 0x1204780
.area 0x80
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SW A0, 0x18(SP)
	SW A1, 0x1C(SP)
	SW A2, 0x20(SP)
	
	; check for m->flags & MARIO_ACTION_SOUND_PLAYED
	LW T0, 0x4(A0)
	LI T2, 0x10000
	AND T1, T0, T2
	BNE T1, R0, @@no_sparkles
	NOP

	JAL 0x80404700
	NOP

@@no_sparkles:
	LW A0, 0x18(SP)
	LW A1, 0x1C(SP)
	JAL 0x80252cf4
	LW A2, 0x20(SP)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea

.orga 0x236EC
	JAL 0x80404780

; act_air_hit_wall
.orga 0x1204800
.area 0x80
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SW A0, 0x18(SP)
	SW A1, 0x1C(SP)
	SW A2, 0x20(SP)
	
	; check for m->actionTimer == 1
	LHU T0, 0x1A(A0)
	LI T1, 1
	BNE T0, T1, @@no_sparkles
	NOP

	JAL 0x80404700
	NOP

@@no_sparkles:
	LW A0, 0x18(SP)
	LW A1, 0x1C(SP)
	JAL 0x80252cf4
	LW A2, 0x20(SP)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea

.orga 0x28A14
	JAL 0x80404800
	
; act_move_punching
.orga 0x1204880
.area 0x80
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SW A0, 0x18(SP)
	SW A1, 0x1C(SP)
	SW A2, 0x20(SP)
	
	; check for m->forwardVel >= 20.f
	LWC1 F0, 0x54(A0)
	LUI T1, 0x41a0 ; 20.f
	MTC1 T1, F2
	NOP
	c.le.s F0, F2
	NOP
	bc1t @@no_sparkles
	NOP

	JAL 0x80404700
	NOP

@@no_sparkles:
	LW A0, 0x18(SP)
	LW A1, 0x1C(SP)
	JAL 0x80252cf4
	LW A2, 0x20(SP)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea

.orga 0x21618
	JAL 0x80404880