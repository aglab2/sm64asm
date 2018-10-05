;savestate: memcpy A2->A0 to A1=A0
;save:
;	A0 = 80400000
;	A1 = 80426B28
;	A2 = 8033B170

;copy to 80780000

; 1) check if saved at least once

.orga 0x21ED40 ;4F40
	.dw 0x00040000
	.dd 0x0C0000008030A93C
	.dw 0x08000000
	.dd 0x0C0000008030A1C0
	.dw 0x09000000

.orga 0xC593C
	LUI T0, 0x8040
	SW R0, 0x18(T0)

	JR RA
	NOP
	

.orga 0xC51C0
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LUI T0, 0x8040
	LW T0, 0x18(T0)
	.f_PrintReg 15, 15, 0x80283890, T0
	
	LUI V0, 0x8034
	LUI V1, 0x8040
	
	;quicksand should trigger unconditional savestate load
	LW T0, 0xB17C (V0)
	LI T1, 0xFFFFF000
	AND T0, T0, T1
	LI T1, 0x00021000
	BEQ T1, T0, loadstate
	NOP
	
	;count all the states and drop if too many
	; TODO
	
	LH T0, 0xAFA0 (V0)
	LH T2, 0xAFA2 (V0)
	
	
	ANDI T1, T2, 0x20
	BEQ T1, R0, noload
	NOP

loadstate:
	LW T0, 0x18(V1)
	BEQ T0, R0, finish
	NOP
	
	LI A0, 0x8033B170
	LI A1, 0x80361C98
	LI A2, 0x80780000
	
	B memcpy
	NOP	
noload:


	ANDI T1, T0, 0x1000
	BEQ T1, R0, nosave
	NOP
	
	LI A0, 0x80780000
	LI A1, 0x807A6B28
	LI A2, 0x8033B170
	B memcpy
	NOP
nosave:


finish:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

memcpy:
	LW T9, 0x0(A2)
	SW T9, 0x0(A0)
	ADDIU A0, A0, 4
	BNE A1, A0, memcpy
	ADDIU A2, A2, 4
	
	B finish
	NOP


; update score
.orga 0x98CBC
	J 0x80403700
	NOP
	
.orga 0x1203700
	LUI T6, 0x8033
	LH T6, 0x14F8(T6)
	
	LUI V1, 0x8040
	LB A0, 0x1C(V1)
	SB T6, 0x1C(V1)
	
	BEQ A0, T6, noact
	NOP
	ADDI A1, R0, -1
	BEQ A0, A1, noact
	NOP
	
	LW A0, 0x18(V1)
	ADDIU A0, A0, 1
	SW A0, 0x18(V1)
	
noact:
	J 0x802DDCC4
	NOP