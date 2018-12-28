; 802DB9EC -- draws the course text
; 802DBA0C -- draws the course number

; Fix 6 -> 7 symbols
.orga 0x9677C
	LW AT, 0x4(T7)
	SW AT, 0x4(T6)

.orga 0x1202B00
	.db 0x00 ;0
	.db 0x00 ;1
	.db 0x01 ;2
	.db 0x01 ;3
	.db 0x02 ;4
	.db 0x02 ;5
	.db 0x03 ;6
	.db 0x04 ;7
	.db 0x04 ;8
	.db 0x05 ;9
	.db 0x05 ;10

; Shift for Chapter text
.orga 0x969E4
	ADDIU A0, R0, 0x38

; Fix for chapter X text
.orga 0x969FC
	JAL 0x80402C00

.orga 0x1202C00
	LUI T0, 0x8040
	ADDU T0, T0, A0
	J 0x802D8B34
	LB A0, 0x2B00(T0)

; 80176FC4
; Set text in file select
.orga 0x227594
	JAL 0x80402D00
.orga 0x227580
	NOP
	
.orga 0x1202D00
	LB T2, 0x1(A3)
	BEQ T2, R0, digit2_2
	NOP

	LB T1, 0x0(A3)
	LUI T0, 0x8040
	ADDU T0, T0, T1
	LB T1, 0x2B00(T0)
	J 0x802D7B84
	SB T1, 0x0(A3)
digit2_2:
	LI T0, 5
	SB T0, 0x0(A3)
	LI T0, 0xFF
	J 0x802D7B84
	SB T0, 0x1(A3)


; Fix for chapter X text v2
.orga 0x983CC
	JAL 0x80402E00
.orga 0x9842C
	JAL 0x802D77DC

.orga 0x1202E00
	LB T2, 0x1(A2)
	BEQ T2, R0, digit2
	NOP

	LB T1, 0x0(A2)
	LUI T0, 0x8040
	ADDU T0, T0, T1
	LB T1, 0x2B00(T0)
	J 0x802D77DC
	SB T1, 0x0(A2)

digit2:
	LI T0, 5
	SB T0, 0x0(A2)
	LI T0, 0xFF
	J 0x802D77DC
	SB T0, 0x1(A2)