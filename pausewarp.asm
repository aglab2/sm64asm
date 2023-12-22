; HOLD B TO WARP
.orga 0x1205200
	.db 0x11, 0x18, 0x15, 0x0D, 0x9E, 0x0B, 0x9E, 0x0A, 0x17, 0x0D, 0x9E, 0x1E, 0x17, 0x19, 0x0A, 0x1E, 0x1C, 0x0E, 0x9E, 0x1D, 0x18, 0x9E, 0x20, 0x0A, 0x1B, 0x19, 0xFF

; gUseWarp
.orga 0x1205300
	.db 15
	
	.db 0x9, 0x18, 0xc, 0x5, 0x4, 0x7, 0x16, 0x8, 0x17, 0xa, 0xb, 0x24, 0xd, 0xe, 0xf

; hook to print B to warp
.orga 0x97994
	JAL 0x80405400

.orga 0x1205400
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	SUBIU T0, A0, 74
	ADDIU T1, A1, 125
	
	SW T0, 0x18(SP)
	JAL 0x2D77DC ; print_generic_string(x + 54, y - 5, strVal)
	SW T1, 0x1C(SP)	
	
	LW A0, 0x18(SP)
	LI A2, 0x80405200
	JAL 0x2D77DC ; print_generic_string(x - 20, y + 120, holdBToWarp)
	LW A1, 0x1C(SP)
	
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

.orga 0x97BFC
	LI T9, 15
	; gUseWarp = 15
	SB T9, 0x80405300
	B 0x97C18
	SH T8, 0x26(SP)

; hook for exit course
.orga 0x97ca0
	JAL 0x80405500
	LUI AT, 0x8033
	B 0x97CF0
	NOP

.orga 0x1205500
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LI V0, 1 ; MENU_OPT_DEFAULT
	SB R0, 0x1470(AT)
	
	LB T0, 0x1490(AT) ; gDialogLineNum
	SLTIU T1, T0, 15
	BEQ T1, R0, @@nowarp
	
	; gPlayer3Controller->buttonDown & B_BUTTON
	LW T3, 0x8032d5ec
	LH T2, 0x10(T3)
	ANDI T2, T2, 0x4000
	BEQ T2, R0, @@nowarp
	
@@yeswarp:
	; gUseWarp = gDialogLineNum
	SB T0, 0x80405300
	LI V0, 2 ; MENU_OPT_EXIT_COURSE
	
@@nowarp:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

; play_mode_paused hook
.orga 0x6668
	LB A0, 0x80405300
	JAL 0x80405600
	NOP
	NOP
	
.orga 0x1205600
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	; check if course was selected
	LI T0, 15
	BGE A0, T0, @@death_warp

@@pause_warp:
	; warpTbl[gUseWarp]
	LUI T1, 0x8040
	ADD T1, T1, A0
	LB A0, 0x5301(T1)

	LI A1, 1 ; area 1
	B @@ehd
	LI A2, 0xa ; warp idx 0xA

@@death_warp:
	JAL 0x8027a9c8
	LI A0, 0xa ; <-- warp index used for the 'exit course'
	
	LB A0, 0x1(V0)
	LB A1, 0x2(V0)
	LB A2, 0x3(V0)
	
@@ehd:
	; trigger the warp using A0-A2 (initiate_warp)
	JAL 0x8024a700
	LI A3, 0

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
