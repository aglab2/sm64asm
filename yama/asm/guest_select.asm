.orga 0x2275b0
	jal 0x80404a00
	
.orga 0x1204a00
	SUBIU SP, SP, 0x18
	SW RA, 0x14(SP)
	
	LH T3, 0x8033bac6
	SLTI AT, T3, 16
	BEQZ AT, sidecourse

	LI T0, 0x10
	B fini
	SB T0, 0x0(A3)

sidecourse:
	LI T0, 0x11
	SB T0, 0x0(A3)
	LI T0, 0x0f
	SB T0, 0x1(A3)

fini:
	JAL 0x2d7b84
	NOP
	
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

; level name 
; T3 = course name
.orga 0x227658
	jal 0x80404a80
	
.orga 0x1204a80
	SUBIU SP, SP, 0x18
	SW RA, 0x14(SP)
	
	SLTI AT, T3, 16
	BNEZ AT, @@nochange
	NOP
	
	LUI V0, 0x8040
	SUBIU T0, T3, 0x10
	SLL T0, T0, 2
	ADDU V0, V0, T0
	LB T1, 0x8033B24A
	ADDU V0, V0, T1
	LB T2, 0x4c00(V0)
	SLL T2, T2, 5
	LI A0, 0x404e00 - 3
	ADDU A0, A0, T2
	
@@nochange:
	JAL 0x277f50
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

; act name tbl
.orga 0x227668
	jal 0x80404b00

.orga 0x1204b00
	SUBIU SP, SP, 0x18
	SW RA, 0x14(SP)
	
	LH T3, 0x8033bac6
	SLTI AT, T3, 16
	BNEZ AT, @@nochange
	NOP
	
	LUI V0, 0x8040
	SUBIU T0, T3, 0x10
	SLL T0, T0, 2
	ADDU V1, V0, T0
	LB T1, 0x8033B24A
	ADDU V1, V1, T1
	LB T2, 0x4c00(V1)
	SLL T2, T2, 5
	LI T4, 0x404d00
	ADDU T4, T4, T2
	SW T4, 0x4AF4(V0)
	ADDIU T4, T4, 0x10
	SW T4, 0x4AF8(V0)
	LI T5, 0x404df0
	SW T5, 0x4AFC(V0)
	
	LI A0, 0x404b00 - 0xc + 0x6 * 4
	LI T5, 24
	MULT T5, T3
	MFLO T6
	SUBU A0, A0, T6
	
@@nochange:
	JAL 0x277f50
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
.orga 0x227000
	JAL 0x80405000
.orga 0x2272cc
	JAL 0x80405000
	
; save_file_get_star_flags in bhv_act_selector_init
.orga 0x1205000
	SUBIU SP, SP, 0x18
	SW RA, 0x14(SP)
	
	JAL 0x27a1c8
	NOP
	
	LH T3, 0x8033bac6
	SLTI AT, T3, 16
	BNEZ AT, @@nochange
	NOP
	
	LB T1, 0x8033B24A
	SUBIU T1, T1, 1
	SLL T1, T1, 1
	SRLV V0, V0, T1
	ANDI V0, V0, 3
	
@@nochange:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
; save_file_get_star_flags in lvl_init_act_selector_values_and_stars
.orga 0x227a44
	JAL 0x80405080
	
.orga 0x1205080
	SUBIU SP, SP, 0x18
	SW RA, 0x14(SP)
	
	JAL 0x27a1c8
	NOP
	
	LH T3, 0x8033bac6
	SLTI AT, T3, 16
	BNEZ AT, @@nochange
	NOP
	
	LI V0, 0
	
@@nochange:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
; save_file_get_course_star_count in lvl_init_act_selector_values_and_stars
.orga 0x227a84
	JAL 0x80405100
	
.orga 0x1205100
	SUBIU SP, SP, 0x18
	SW RA, 0x14(SP)
	
	JAL 0x279f80
	NOP
	
	LH T3, 0x8033bac6
	SLTI AT, T3, 16
	BNEZ AT, @@nochange
	NOP
	
	LH A0, 0x8032ddf4
	LH A1, 0x8033bac6
	
	SUBIU A0, A0, 1
	JAL 0x80405000
	SUBIU A1, A1, 1
	ANDI T0, V0, 0x1
	ANDI T1, V0, 0x2
	
	LI V0, 0

	BEQ T0, R0, @@not1
	NOP
	ADDIU V0, V0, 1
@@not1:
	
	BEQ T1, R0, @@not2
	NOP
	ADDIU V0, V0, 1
@@not2:
	
@@nochange:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

.orga 0x2277b8
	JAL 0x80405900

; hints managing
.orga 0x1205900
	SUBIU SP, SP, 0x28
	SW RA, 0x14(SP)
	
	LH T3, 0x8033bac6
	
	SLTI AT, T3, 11
	BNEZ AT, @@nochange
	NOP
	
	SLTI AT, T3, 16
	BNEZ AT, @@nomicro
	NOP
	
	LUI V0, 0x8040
	SUBIU T0, T3, 0x10
	SLL T0, T0, 2
	ADDU V0, V0, T0
	LB T1, 0x8033B24A
	ADDU V0, V0, T1
	LB T2, 0x4c00(V0)
	SLL T2, T2, 4
	LI A1, 0x80404c80
	B @@printguest
	ADDU A1, A1, T2

@@nomicro:
	SLL T2, T3, 5
	LI A1, 0x80405840 - 0x20 * 11
	B @@printguest
	ADDU A1, A1, T2

@@printguest:
	SW A1, 0x18(SP)
	LI A2, 10.0
	JAL 0x802d8844
	LI A0, 160
	
	ADD A0, V0, R0

	LW A2, 0x18(SP)
	JAL 0x802d77dc
	LI A1, 118
	
@@nochange:
	LI V0, 0
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28