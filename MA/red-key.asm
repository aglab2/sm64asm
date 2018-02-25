; [ARMIPS 0.9+] Make reds in bowser set key flag, warp hole hook for boxes

;============Hook bowser reds==============
;add music for red coins grabberino
.orga 0xAE31C
.area 0x28
LUI A0, 0x2436
ADDI A0, A0, 1
JAL 0x8031EB00
NOP
j 0x2B3600
NOP
.endarea
;=========================End Hooks===========================



.orga 0x6E600
.area 0x1B4
redgethook:
	;====================Red hook code=====================
	ADDI T9, T9, 0x1
	LUI T7, 0x8034
	SB T9, 0xB4A6 (T7) ;should save!
	
	LUI T7, 0x8034
	LB T7, 0xB249(T7) ;current level
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI AT, 0x8020
	ADDI AT, AT, 0x7700 ;current eep base
	
red_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, red_fileselectend
	NOP
	ADDI AT, AT, 0x70
	B red_fileselectloop
	NOP
red_fileselectend:

	ADDIU T8, R0, 0x11
	BNE T7, T8, red_nob1
	NOP
	LB T6, 0x0B(AT)
	ORI T6, T6, 0x10
	SB T6, 0x0B(AT)
	b red_fini
	NOP
red_nob1:

	ADDIU T8, R0, 0x1C
	BNE T7, T8, red_nomc
	NOP
	LB T6, 0x0B(AT)
	ORI T6, T6, 0x20
	SB T6, 0x0B(AT)
	LB T6, 0x07(AT)
	ORI T6, T6, 0x02
	SB T6, 0x07(AT)
	b red_fini
	NOP
red_nomc:

	ADDIU T8, R0, 0x1D
	BNE T7, T8, red_nowc
	NOP
	LB T6, 0x0B(AT)
	ORI T6, T6, 0x20
	SB T6, 0x0B(AT)
	LB T6, 0x07(AT)
	ORI T6, T6, 0x04
	SB T6, 0x07(AT)
	b red_fini
	NOP
red_nowc:

	ADDIU T8, R0, 0x12
	BNE T7, T8, red_novc
	NOP
	LB T6, 0x0B(AT)
	ORI T6, T6, 0x20
	SB T6, 0x0B(AT)
	LB T6, 0x07(AT)
	ORI T6, T6, 0x01
	SB T6, 0x07(AT)
	b red_fini
	NOP
red_novc:
	;just spawn reds then, rip :]
	;first part
	LUI T5, 0x8036
	LW T5, 0x1160(T5)
	LWC1 F12, 0xA0(T5)
	LWC1 F14, 0xA4(T5)
	JAL 0x2F2C24
	LW A2, 0xA8(T5)
	;jump to 2nd part
	j 0x2F3334
	NOP
	
red_fini:
	j 0x2F3350 ;longjump cause scrub
	NOP
	;====================Red hooks end======================
.endarea







.orga 0xB6C4C
.area 0x10C
	;=================Custom behav start====================
;warp 0
;addr 0x2FBC4C
	LUI T8, 0x8036
	LW T8, 0x1160(T8)
	LUI T9, 0x00E0
	SW T9, 0x0188(T8)
	j 0x2AAA60
	NOP
;warp 1
;addr 0x2FBC64
	LUI T8, 0x8036
	LW T8, 0x1160(T8)
	LUI T9, 0x00E1
	SW T9, 0x0188(T8)
	j 0x2AAA60
	NOP
;warp 2
;addr 0x2FBC7C
	LUI T8, 0x8036
	LW T8, 0x1160(T8)
	LUI T9, 0x00E2
	SW T9, 0x0188(T8)
	j 0x2AAA60
	NOP
;AB challenge
;addr 0x2FBC94
	addiu sp, sp, -0x18
	sw ra, 0x14 (sp)
 
	LUI T8, 0x8034
	LB T8, 0xAFA2(T8)
	BEQ T8, R0, ded_end
	NOP
 
	LUI T8, 0x8034
	LB T9, 0xB21E(T8)
	SUBI T9, T9, 0x1
	SB T9, 0xB21E(T8)
 
	ded_end:
	lw ra, 0x14 (sp)
	jr ra
	addiu sp, sp, 0x18
	;==================Custom behav end=====================
.endarea









.orga 0xB87F8
.area 0x154
	;=================Custom behav start====================
;addr 0x2FD7F8
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI AT, 0x8020
	ADDI AT, AT, 0x7700 ;current eep base
	
w1_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, w1_fileselectend
	NOP
	ADDI AT, AT, 0x70
	B w1_fileselectloop
	NOP
w1_fileselectend:
	LB T6, 0x07(AT)
	ANDI T6, T6, 0x01
	BEQ T6, R0, w1_fini
	NOP
	j 0x2FBC4C
	NOP
w1_fini:
	jr RA
	NOP

;addr 0x2FD840
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI AT, 0x8020
	ADDI AT, AT, 0x7700 ;current eep base
	
w2_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, w2_fileselectend
	NOP
	ADDI AT, AT, 0x70
	B w2_fileselectloop
	NOP
w2_fileselectend:
	LB T6, 0x07(AT)
	ANDI T6, T6, 0x02
	BEQ T6, R0, w2_fini
	NOP
	j 0x2FBC64
	NOP
w2_fini:
	jr RA
	NOP
;addr 0x2FD888
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI AT, 0x8020
	ADDI AT, AT, 0x7700 ;current eep base
	
w3_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, w3_fileselectend
	NOP
	ADDI AT, AT, 0x70
	B w3_fileselectloop
	NOP
w3_fileselectend:
	LB T6, 0x07(AT)
	ANDI T6, T6, 0x03
	BEQ T6, R0, w3_fini
	NOP
	j 0x2FBC7C
	NOP
w3_fini:
	jr RA
	NOP
;addr 0x2FD8D0
;FLY when lower then 0x4648AA4F
	LUI T0, 0x464D
	ADDIU T0, T0, 0xA0EF
	MTC1 T0, F4
	LUI T1, 0x8034
	LW T0, 0xB1B0(T1)
	MTC1 T0, F6
	
	c.lt.s F4, F6
	BC1T fly_no
	NOP
	
	LW T2, 0xB17C(T1)
	LUI T0, 0x0300
	ADDIU T0, T0, 0x0880
	BEQ T0, T2, fly_setzspeed
	NOP
	ADDIU T0,T0, 0x1
	BEQ T0, T2, fly_setzspeed
	NOP
	ADDIU T0,T0, 0x1
	BEQ T0, T2, fly_setzspeed
	NOP
	
	B fly_no
	NOP

fly_setzspeed:
	LUI T0, 0x0
	ADDIU T0, T0, 0x4220
	SH T0, 0xB1BC(T1)
	;LUI T0, 0x0300
	;ADDIU T0, T0, 0x0880
	;SW T0, 0xB17C(T1)
	
fly_no:
	JR RA
	NOP
	;==================Custom behav end=====================
.endarea