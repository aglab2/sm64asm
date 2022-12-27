.orga 0x120FB00
	.dw 0x00040000
	.dd 	0x0C0000008040F680
	.dw 0x08000000
	.dd 	0x0C0000008040FC00
	.dw 0x09000000




.orga 0x120F680
.area 0x80
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; search bowser
	LI A0, 0x13001850
	JAL 0x8029F95C
	NOP
	
	LW V1, 0x80361160
	SW V0, 0x100(V1)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea



.orga 0x120FC00
.area 0x100
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LW V1, 0x80361160
	LW A0, 0x100(V1)
	
; 10s delay
	LW T0, 0x154(V1)
	SLTI AT, T0, 10
	BNEZ AT, end
	NOP

; normal work with bowser
; init cs
	LW T0, 0x14C(A0)
	; kill bowser should not be interrupted
	LI T1, 0x4
	BEQ T0, T1, end
	NOP
	LI T1, 0x6
	BEQ T0, T1, end
	NOP
	LI T1, 0x5
	BEQ T0, T1, end
	NOP
	LI T1, 0xc
	BEQ T0, T1, end
	NOP

; always run
	LI T0, 0x7
	SW T0, 0x14C(A0)
	; LI T1, 0xc17ef600
	; SW T1, 0x54(A0)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
.endarea





; make running speed a bit more reasonable
.orga 0x70D00
	JAL 0x8040F900
	
.orga 0x70ce8
; speed delim, currently 15.f
; every attack speed will raise
	LUI AT, 0x4170

.orga 0x120f900
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	; T3=bowser
	; multiply delim by bowser health
	LWC1 F10, 0x184(T3)
	NOP
	cvt.s.w F8, F10 
	NOP
	mul.s F6, F6, F8
	NOP

	; F8 distance to mario
	LWC1 F8, 0x15C(T3)
	NOP
	; F6 is loaded from AT above
	c.lt.s F8, F6
	NOP
	bc1f nofixup
	NOP
	MOV.s F8, F6
	NOP

nofixup:
	DIV.s F8, F8, F6
	NOP
	SWC1 F8, 0xB8(T3)
	NOP
	
	; let's do the check for the bowser hitting bomb here
	JAL 0x802b5f6c ; bowser_check_hit_mine
	NOP
	BEQ V0, R0, nobombhit
	
	LW V1, 0x80361160
	LW T0, 0x184(V1)
	SUBIU T0, T0, 1
	SW T0, 0x184(V1)
	BLE T0, R0, ded
	LI T1, 4 ; DEAD
	LI T1, 12 ; HIT_MINE
ded:
	SW T1, 0x14c(V1)
nobombhit:

	; original tail call
	JAL 0x802a5288 ; cur_obj_init_animation_and_check_if_near_end
	LI A0, 19 ; BOWSER_ANIM_RUN
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP




; turn a bit quicker
.orga 0x70d9c
	ADDIU A1, R0, 0x500

; bowser always runs :3
.orga 0x70D7C
	B 0x70D94

.orga 0x70D34
	B 0x70D4C

; hitting edge quickturns bowser
; T8=gCurrentObject
.orga 0x70F38
	BEQ T0, R0, 0x70f50
	LW T2, 0x0C8(T8)
	ADDIU T2, T2, 0x8000
	SW T2, 0x0C8(T8)
	NOP
	NOP



; tighten bomb radius a bit
.orga 0x70f94
	LUI AT, 0x4396
	
	
	
	
	
; disable bowser tail tangibility
.orga 0x6ec2c
	LW V1, 0x80361160
	LW V1, 0x68(V1)
	
	LI T0, -1
	SW T0, 0x9C(V1)
	
	JR RA
	NOP




; hook into audio codes to pull tatums
;.orga 0xd8c20
;	JAL 0x8040fd00
;	NOP
;
;.orga 0x120fd00
;	LUI V0, 0x8041
;	LW T3, 0xfcf0(V0)
;	ADDIU T3, T3, 1
;	SW T3, 0xfcf0(V0)
;
;	ADDU T3, T5, T7
;	SH T3, 0xC(S1)
;
;	JR RA
;	NOP

; bowser init/loop hooks
.orga 0x21B6B8
	.dw 0x8040f880

.orga 0x21B6C4
	.dw 0x8040f300

; init
.orga 0x120f880
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	SW R0, 0x8040fcf0
	SW R0, 0x8040fcf4
	SW R0, 0x8040fcf8

	JAL 0x802B7878
	NOP

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

; loop
.orga 0x120f300
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	; debugging for the effects
	;LW A3, 0x802229ec
	;LI A0, 20
	;LI A2, 0x80283890
	;JAL 0x802d62d8
	;LI A1, 20

	; music effects engine
	; wait a bit before going ham
	LW V1, 0x80361160
	LW T0, 0x8040fcf8
	ADDIU T0, T0, 1
	SW T0, 0x8040fcf8
	BLE T0, 30, call_bowser_loop
	NOP

	LW T0, 0x802229ec	
	LW V1, 0x8040fcf4
	BGE T0, 1760, play0
	NOP
	BGE T0, 1550, play1
	NOP
	BGE T0, 1415, play2
	NOP
	BGE T0, 1203, play3
	NOP
	BGE T0, 1134, play_reset
	NOP
	BGE T0, 500, play0
	NOP
	B play_reset
	NOP

play0:
	ANDI AT, V1, 1
	BNE AT, R0, call_bowser_loop
	NOP
	LI A0, 0x2428FF81
	LI A1, 0x803331f0
	JAL 0x8031eb00
	NOP
	ORI V1, 1
	B call_bowser_loop

play1:
	ANDI AT, V1, 2
	BNE AT, R0, call_bowser_loop
	NOP
	LI A0, 0x243AFF81
	LI A1, 0x803331f0
	JAL 0x8031eb00
	NOP
	ORI V1, 2
	B call_bowser_loop

play2:
	ANDI AT, V1, 4
	BNE AT, R0, call_bowser_loop
	NOP
	LI A0, 0x243BFF81
	LI A1, 0x803331f0
	JAL 0x8031eb00
	NOP
	ORI V1, 4
	B call_bowser_loop

play3:
	ANDI AT, V1, 8
	BNE AT, R0, call_bowser_loop
	NOP
	LI A0, 0x243CFF81
	LI A1, 0x803331f0
	JAL 0x8031eb00
	NOP
	ORI V1, 8
	B call_bowser_loop

	NOP
play_reset:
	LI V1, 0

call_bowser_loop:
	SW V1, 0x8040fcf4
	JAL 0x802B75A4
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18