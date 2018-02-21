.org 0x108A18
.ls_callFunc 0x00, 0x8024B940

//************** DmaCopy function **************//
.orga 0x6940 ; Overwrite the unused function 0x8024B940
.area 0x64 ; Set data import limit to 0x64 bytes
addiu sp, sp, 0xFFE8
sw ra, 0x14 (sp)
sw a0, 0x10 (sp) ; lvl cmd 0x11 safeguard

// These two are nessecary because of what we overwrote at 0x108A18.
.f_osViBlack FALSE ; Set screen blackout to false
sw r0, 0x8038BE24 ; Set level accumulator to 0

// Copies 0x100 bytes from ROM addr 0x7F0000 to RAM addr 0x80370000
.f_DmaCopy 0x80370000, 0x03000000, 0x03000200

lw v0, 0x10 (sp) ; lvl cmd 0x11 safeguard
lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea

//************** Mario loop function **************//
.orga 0x861C0 ; Set ROM address
.area 0x90 ; Set data import limit to 0x90 bytes
addiu sp, sp, 0xFFE8
sw ra, 0x14 (sp)

jal 0x80370000 ; Call our custom timer function
nop

lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea

.orga 0x03000000
.area 0x200
	ADDIU SP, SP, -0x18
	SW RA, 0x10(SP)

	LUI T0, 0x8034
	LUI V1, 0x8037

;check sliding
	LW T9, 0xB17C(T0)
	LUI T8, 0x0088
	ADDIU T8, T8, 0x0456
	BNE T9, T8, anti_end
	NOP

;check if stuck
	LW T2, 0xB1AC(T0)
	LW T3, 0xB1B0(T0)
	LW T4, 0xB1B4(T0)

	LW T5, 0x020C(V1)
	LW T6, 0x0210(V1)
	LW T7, 0x0214(V1)

	move A0, T2
	move A1, T5
	JAL 0x803700F4 ;func_compare
	NOP
	BNE V0, R0, anti_nostuck
	NOP
	move A0, T3
	move A1, T6
	JAL 0x803700F4 ;func_compare
	NOP
	BNE V0, R0, anti_nostuck
	NOP
	move A0, T4
	move A1, T7
	JAL 0x803700F4 ;func_compare
	NOP
	BNE V0, R0, anti_nostuck
	NOP
	
	LB V0, 0x0200(V1)
	ADDI V0, V0, 0x1
	SB V0, 0x0200(V1)
	LUI T0, 0x0000
	ADDI T0, T0, 30; 1 second
	BGE T0, V0, anti_nofixyet
	NOP

anti_fixstuck:	
	LUI T1, 0x8034
	LUI T0, 0x0102
	ADDIU T0, T0, 0x08B0
	SW T0, 0xB17C(T1)
	SW T0, 0x0200(V1)
	MTC1 T3, F0
	LI T0, 300.0
	MTC1 T0, F2
	ADD.S F0, F0, F2
	MFC1 T3, F0
	LUI T0, 0x8034
	SW T3, 0xB1B0(T0)
	
anti_nostuck: ;save prev coord, nullify cnt
	SB R0, 0x0200(V1)
anti_nofixyet:
	SW T2, 0x020C(V1)
	SW T3, 0x0210(V1)
	SW T4, 0x0214(V1)

anti_end:
	LW RA, 0x10(SP)
	JR RA
	ADDIU sp, sp, 0x18
	NOP

	
	
	
;nostuck will give 0
func_compare:
	ADDIU SP, SP, -0x18
	SWC1 F0, 0x10 (SP)
	SWC1 F2, 0x14 (SP)
	
	MTC1 A0, F0
	MTC1 A1, F2
	SUB.S F0, F2, F0
	
	;get absolute value
	MTC1 R0, F2
	C.LT.S F2, F0
	BC1T compare_noreverse
	NOP
	SUB.S F0, F2, F0
compare_noreverse:
	
	LI A0, 1.0
	MTC1 A0, F2
	
	LUI V0, 0x0000
	C.LT.S F0, F2
	BC1T compare_end
	NOP
	
	ADDIU V0, V0, 0x1
	
compare_end:
	LWC1 F0, 0x10 (SP)
	LWC1 F2, 0x14 (SP)
	JR RA
	ADDIU sp, sp, 0x18 
.endarea