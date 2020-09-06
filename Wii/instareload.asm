;~8033CA64
; 802868F8 -- called for each frame

; 8033CBD0

.orga 0x21CCDC
	.dd 0x0C00000080403900

.orga 0x1203900
.area 0x200
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LUI V0, 0x8034
	LUI V1, 0x8040
	
	;quicksand should trigger unconditional savestate load
	LW T0, 0xB17C (V0)
	LI T1, 0xFFFFF000
	AND T0, T0, T1
	LI T1, 0x00021000
	BEQ T1, T0, loadstate
	NOP
	
	LB T0, 0xB21E (V0)
	BEQ T0, R0, loadstate
	NOP

	LH T0, 0xAFA0 (V0)
	LH T2, 0xAFA2 (V0)
	
	ANDI T1, T0, 0x400
	LI T4, 0x400
	BNE T1, T4, noload
	NOP

loadstate:
	;LW T0, 0x18(V1)
	;BEQ T0, R0, finish
	;NOP
	
	LUI T1, 0x8033
	LW T1, 0xDDCC(T1)
	LW T1, 0x24(T1)
	SB R0, 0x30(T1)
	
	LI A0, 0x8033B170
	LI A1, 0x80361C98
	LI A2, 0x80780000
	
	B memcpy
	NOP

noload:

	ANDI T1, T0, 0x3010
	LI T4, 0x3010
	BNE T1, T4, nosave
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
	
	; IF YOU REMOVE THESE NOPS WII WILL CRASH
	; FUCK THIS GOD DAMN CONSOLE JESUS CHRIST
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
	NOP
	NOP
	NOP
	NOP
	NOP
.endarea