;802d739c - 9239C
;802d7060
;802d7470 - 92470
;	802ddcbc - 98CBC
;802ac854 - 67854
;8026adcc - 25DCC
;8026d42c - 2842C
;8024c1c8 - 71C8

; fading warps :)
.orga 0x98CBC
	JAL 0x80403700
.orga 0x1203734
	JR RA

.orga 0xB594
	JAL 0x80402300
.orga 0x1202314
	JR RA

; wind cheat :)
.orga 0x2640C
	JAL 0x80402550
.orga 0x1202584
	JR RA
	
; lava cheat :)
.orga 0xF204
	ADDIU T9, T5, 0xFFC0
	SH T9, 0xAE(T6)

; koopa cheat
;.orga 0x2d5d4
;	ADDIU T6, T5, 1

;.orga 0x31998
;	SLTI T2, T1, 0xC
	
;.orga 0x31a00
;	SLTI T2, T1, 0x23