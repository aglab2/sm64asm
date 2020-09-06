
; both mio0 and regular load are served by the same function
.orga 0x108694
	.dw 0x80402000
	.dw 0x80402000

.orga 0x1202000
.area 0x100, 0x01
	ADDIU SP, SP, -0x20
	SW RA, 0x14(SP)
	
	LUI T0, 0x8039
	LW T0, 0xBE28(T0)
	
; load data from commands
; A0 is either bank/ram address
	LBU V0, 0x0(T0)
	LBU A0, 0x3(T0)
	LW  A1, 0x4(T0)
	LW  A2, 0x8(T0)

; detect if static or dynamic
; 2nd byte tells
; if dynamic, we have done everything already
	LBU T1, 0x2(T0)
	
	ADDIU T0, R0, 1
	BNE T1, T0, dynamic
	NOP
	
; static
;bug check
; could be removed if wanted
static:
SLTIU AT, A0, 0x14
BEQ AT, R0, bugon
NOP

; prepare ptr in segment list
	LUI T0, 0x8034
	SLL T1, A0, 2
	ADDU T9, T0, T1
	SW T9, 0x18(SP)

; prepare ptr in static ram
	SLL T1, A0, 2
	LUI T0, 0x8040
	ADDU T0, T0, T1
	LW A0, 0x2220(T0)
	SW A0, 0x1C(SP)
BEQ A0, R0, bugon
NOP


; do it -- select either 17 or 18 loader
	LI T0, 0x18
	BEQ T0, V0, mio0
	NOP	
	JAL 0x80278504
	NOP
	B enddyn
	NOP
mio0:
	JAL 0x80402100
	NOP

enddyn:
; set the new segment ptr
	LW T9, 0x18(SP)
	LW A0, 0x1C(SP)
	LI T0, 0x00FFFFFF
	AND A0, A0, T0
	B end
	SW A0, 0xB400(T9)

; these NOPs manipulate Wii rng, don't question them
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
dynamic:
	JAL 0x8027868C
	ADDIU A3, R0, 0

end:
	LUI T0, 0x8039
	LW T1, 0xBE28(T0)
	LB T2, 0x1(T1)
	ADDU T1, T1, T2
	SW T1, 0xBE28(T0)

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x20
	
bugon:
	J 0
	NOP
.endarea

; mio0 static loader, matched interface of cmd17 static loader
; A0 = ram address
; A1 = rom start
; A2 = rom end
.orga 0x1202100
.area 0x130, 0x01
	ADDIU SP, SP, -0x30
	SW RA, 0x14 (SP)
	SW A0, 0x0024 (SP) ; 0x28 - bank // static ram = 0x24
	SW A1, 0x002C (SP) ; 0x2C - rom start
	SW A2, 0x0020 (SP) ; 0x30 - rom end

	LI A0, 0x80670000 ; collision data, have like 0xB0000 space
	SW A0, 0x001C (SP) ; 0x1C - alloced temp mio0

	LW A1, 0x002C (SP)
	JAL 0x80278504 ; dmacopy(ram mio0, rom start, rom end)
	LW A2, 0x0020 (SP)

	LW A0, 0x001C (SP)
	JAL 0x8027F4E0 ; unpack(mio0 packed, mio0 unpacked)
	LW A1, 0x0024 (SP)

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x30
.endarea

.if readu32(outputname(), 0x1202000) == 0xD0FFBD27
; ptr load table
; this should be filled in from the target rom
.orga 0x1202220
	.dw 0x00000000 ;0
	.dw 0x00000000 ;1
	.dw 0x00000000 ;2
	.dw 0x00000000 ;3
	.dw 0x00000000 ;4
	.dw 0x80720000 ;5
	.dw 0x80570000 ;6
	.dw 0x80620000 ;7
	.dw 0x00000000 ;80 40 22 00 ;8
	.dw 0x00000000 ;80 40 22 00 ;9
	.dw 0x00000000 ;80 40 22 00 ;A
	.dw 0x00000000 ;80 40 22 00 ;B
	.dw 0x00000000 ;80 40 22 00 ;C
	.dw 0x00000000 ;80 40 22 00 ;D
	.dw 0x80420000 ;80 40 20 B0 ;E
	.dw 0x00000000 ;80 40 22 00 ;F
	.dw 0x00000000 ;80 40 22 00 ;10
	.dw 0x00000000 ;80 40 22 00 ;11
	.dw 0x00000000 ;80 40 22 00 ;12
	.dw 0x807B0000 ;80 40 21 90 ;13
.endif