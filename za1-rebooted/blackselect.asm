;black=80214C70
;white=80214D78

;8033B06C -> current f3d command

; func 802D77DC

; 801772C4 sets envcolor for most letters
; 801773DC sets envcolor for other most letters 
; 80247570 - last DL command

; color 2A654A
.orga 0x2A654A
	.dh 0b0001000010000101

.orga 0x227798
	LI T5, 0xFFFFFFFF
	SW T5, 0x4(T4)

.orga 0x227898
	LI T2, 0xFFFFFFFF
	SW T2, 0x4(T3)
	
;bank 2 @ 80064F80
;803156 = 02000000
;81A616 = 020174C0 = 8007C440 -> that's what I need?

; 01020040 002206C8
; 01030040 002206C8
; 01010040 00220708

; 06000000 02017350=81A4A6

; 213620?

; 802CBB2C/802D22B0 - target?
; 802CB9A0

; all anims are black
.orga 0x868B8
	SB R0, 0x3B(SP)
.orga 0x868C4
	SB R0, 0x3A(SP)
.orga 0x868D0
	SB R0, 0x39(SP)
	
.orga 0x35840
	ANDI A0, A0, 0x0
	ANDI A1, A1, 0x0
	ANDI A2, A2, 0x0