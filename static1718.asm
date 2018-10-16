; FBA24 -- cmd 17; calling func 0x27868C ->? 278504
; FBA78 -- cmd 18; calling func 0x2787D8

;8033B400 + bank * 4 -- another jump table?
; if (bank - 5) < 15 // bank < 0x14

;1202000-1202044 - asm header - picks if static alloc
;1202044-1202088 - asm static alloc preparation?
;1202090-12020A8 - asm selector for alloc func

;1202200-1202230 - asm data for bank > 0x14, common finisher
;12021C8-1202234 - asm - does static alloc
;1202234-1202270 - data jump table? (bank - 5) * 4

;804020B0 - bank E alloc func, allocs to 8042
;804020E8 - bank 7 alloc func, allocs to 8062
;80402120 - bank 6 alloc func, allocs to 8057
;80402158 - bank 5 alloc func, allocs to 8072
;80402190 - bank 13 alloc func, allocs to 807B

; 0x18 - 8038BE28
; 0x14 - 8038BE28

; 8D3C4020
; 80660000 - 

; crash at 8037F058

.orga 0x108694
	.dw 0x80401500
	.dw 0x80402040

;proper static 17
.orga 0x1202000
	ADDIU SP, SP, -0x18
	SW RA, 0x14 (SP)
	
	LI A0, 0x8027868C
	LI A1, 0x80278504
	JAL 0x80402100
	NOP
	
	LW RA, 0x14 (SP)
	JR RA
	ADDIU SP, SP, 0x18

.orga 0x1202040
	ADDIU SP, SP, -0x18
	SW RA, 0x14 (SP)
	
	LI A0, 0x802787D8
	LI A1, 0x80402080
	JAL 0x80402100
	NOP
	
	LW RA, 0x14 (SP)
	JR RA
	ADDIU SP, SP, 0x18

.orga 0x1202080
.area 0x80
	ADDIU SP, SP, -0x28
	SW RA, 0x14 (SP)
	SW A0, 0x0024 (SP) ; 0x28 - bank // static ram = 0x24
	SW A1, 0x002C (SP) ; 0x2C - rom start
	SW A2, 0x0020 (SP) ; 0x30 - rom end

	;ADDIU AT, R0, 0xFFF0
	;SUBU T8, A2, A1
	;ADDIU T9, T8, 0x000F
	;AND A0, T9, AT ; 0x20 - rounded rom length
	;JAL 0x80278120 ;malloc(rounded rom length, 1)
	;ADDIU A1, R0, 0x0001
	LI A0, 0x80750000 ; hacked collision, could be used as storage?
	SW A0, 0x001C (SP) ; 0x1C - alloced temp mio0

	LW A1, 0x002C (SP)
	JAL 0x80278504 ; dmacopy(ram mio0, rom start, rom end)
	LW A2, 0x0020 (SP)

	LW A0, 0x001C (SP)
	JAL 0x8027F4E0 ; unpack(mio0 packed, mio0 unpacked)
	LW A1, 0x0024 (SP)

	;JAL 0x80278238 ; free(mio0)
	;LW A0, 0x001C (SP)

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28
.endarea
	

; generic static allocator
; A0 = original dynamic func
;	A0 = bank Id
;	A1 = rom start
;	A2 = rom end
; A1 = static memory copy func
;	A0 = ptr to mem
;	A1 = rom start
;	A2 = rom end
.orga 0x1202100
.area 0x120, 0x00
	ADDIU SP, SP, -0x30
	SW RA, 0x2C (SP)
	
	; T4 & T5 store func ptrs
	ADDU T4, R0, A0
	ADDU T5, R0, A1

	LUI T0, 0x8039
	LW T0, 0xBE28(T0)
	SW T0, 0x14(SP)
	
	LB T0, 0x2(T0)
	LI T1, 1
	BNE T0, T1, dynamic_alloc
	NOP

static_alloc_checkprep:
	LW V1, 0x0014 (SP)
	LB T9, 0x0003 (V1)

	; let's try not to crash the game lmfao
	SLTI AT, T9, 0x13
	BEQZ AT, dynamic_alloc
	NOP
	
	; T0=bank*4
	SLL T0, T9, 2
	
	; A0 = get static ram ptr
	LUI A0, 0x8040
	ADDU A0, A0, T0
	LW A0, 0x2220(A0)
	
	; same as previous, ptr=0, unknown static alloc
	BEQ A0, R0, dynamic_alloc
	NOP

static_alloc:
	; Set ptr in segment table offset
	; Remove leading 0x80
	LI T8, 0x00FFFFFF
	AND T8, A0, T8
	
	LUI T7, 0x8034
	ADDU T7, T7, T0
	SW T8, 0xB400 (T7)

	; Now copy data in the static place
	LW A1, 0x0004 (V1)
	JALR T5
	LW A2, 0x0008 (V1)
	
	B end
	NOP

dynamic_alloc:
	; pass arguments to orig func
	LW V1, 0x0014 (SP)
	LBU A0, 0x0003 (V1)
	LW  A1, 0x0004 (V1)
	JALR T4
	LW  A2, 0x0008 (V1)

end:
	; fix ptrs to next cmd
	LW V1, 0x0014 (SP)
	LUI V0, 0x8039
	LBU T0, 0x0001 (V1)
	ADDU T0, V1, T0
	SW T0, 0xBE28(V0)

	LW RA, 0x2C (SP)
	JR RA
	ADDIU SP, SP, 0x30

.endarea

; 0 at 2220
.orga 0x1202220
	.dw 0x00000000 ;0
	.dw 0x00000000 ;1
	.dw 0x00000000 ;2
	.dw 0x00000000 ;3
	.dw 0x00000000 ;4
	.dw 0x80720000 ;80 40 21 58 ;5
	.dw 0x80570000 ;80 40 21 20 ;6
	.dw 0x80620000 ;80 40 20 E8 ;7
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x80420000 ;80 40 20 B0 ;E
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x00000000 ;80 40 22 00
	.dw 0x807B0000 ;80 40 21 90 ;13 -- this is interesting????