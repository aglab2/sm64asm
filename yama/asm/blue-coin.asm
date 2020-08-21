; set oHomeY and oPosY
.orga 0x7d4cc
	LW T0, 0x0a4(T2)
	SW T0, 0x168(T2)
.orga 0x7d4dc
	SWC1 F4, 0xb0(T2)

.orga 0x7D590
	B 0x7d628
.orga 0x7d508
	B 0x7d628

.orga 0x7d5e8
	ADDIU A0, A0, 0x2588
	LW A0, 0x80361160

	; any blues are spawned
	BEQ V0, R0, dtor
	NOP
	
	LW T7, 0x154(A0)
	SLTI AT, T7, 0xec
	BNEZ AT, 0x7d628
	NOP
	
	; reset
	JAL 0x80404800
	NOP
	
	B 0x7d628
	NOP
dtor:
	; spawn a star and destory
	JAL 0x80404880
	NOP
	NOP
	
	LW RA, 0x1c(SP)

; restart
.orga 0x1204800
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; unhide
	JAL 0x8029f694
	NOP
	
	LW T0, 0x168(A0)
	SW T0, 0x0A4(A0)

	; reset to act 0
	SW R0, 0x14c(A0)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	nop
	nop
	nop
	nop
	nop
	nop

; spawn a star and die
.orga 0x1204880
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	sw s0, 0x18(SP)

	; invalid action means do nothing
	LI T9, 100
	SW T9, 0x14c(A0)

	LWC1 F12, 0x0A0(A0)
	LWC1 F14, 0x0A4(A0)
	LI T0, 400.0
	MTC1 T0, F0
	add.s F14, F14, F0
	JAL 0x802f2c24
	LW A2, 0x0A8(A0)
	
	LI T0, 6
	SB T0, 0x188(V0)
	
	; JAL 0x802ab558
	; LI A0, 6
	
	lw s0, 0x18(SP)
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
	
; blue coin behav
.orga 0x7d308
	LUI A0, 0x1300
	JAL 0x29F95C
	ADDIU A0, A0, 0x2568
	LW A0, 0x80361160
	
	; despawn if blue switch is missing
	BNE V0, R0, nonull
	NOP
	SW R0, 0x074(A0)
	
nonull:
	; hide the object for search fn
	LW T0, 0x20C(A0)
	SUBIU T0, T0, 4
	SW T0, 0x20C(A0)
	
	; prepare
	SW V0, 0xF8(A0)
	LW T1, 0x14C(A0)
	ADDIU T1, T1, 1
	BEQ R0, R0, 0x7d404
	SW T1, 0x14C(A0)
	
.orga 0x7d364
	ADDIU AT, R0, 1
	
.orga 0x7d374
	LW A0, 0x80361160
	JAL 0x80404980
	NOP
	NOP

; interacted with player
.orga 0x7d3d4
	JAL 0x80404900
; timer expired
.orga 0x7d3f4
	JAL 0x80404900

; interacted with player or timer expired
.orga 0x1204900
	SW R0, 0x14c(A0)
	SW R0, 0x134(A0)
	JR RA
	NOP

	nop
	nop
	nop
	nop
	nop
	nop

; prepare for the switch
.orga 0x1204980
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	; unhide object
	LW T0, 0x20C(A0)
	ADDIU T0, T0, 4
	SW T0, 0x20C(A0)
	LW T0, 0x14c(A0)
	ADDIU T0, T0, 1
	SW T0, 0x14c(A0)
	
	; unhide
	JAL 0x8029f694
	NOP

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

	nop
	nop
	nop
	nop
	nop
	nop
