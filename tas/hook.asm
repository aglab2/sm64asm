.headersize 0x80245000

; notes about the spaces to put code in
; there is space in rom from 0x7cc6c0 to 0x800000
; there is space in ram from 0x80367500 to 0x80378700 (can fit in 17536 lines)

.definelabel code_rom, 0x7cc6c0; where your code goes in the rom
.definelabel code_ram, 0x80367500; where your code goes in the ram

.orga 0x396c; here it copies code into the ram at start up
li a0, code_ram
li a1, code_rom
li.u a2, code_end_copy
jal 0x80278504
li.l a2, code_end_copy
jal execonce
nop

.orga 0xfd354
jal execeveryframe
nop

; !!! TAS Input reader
.orga 0x366c
jal readinputs

; !!! Save is not loaded
.orga 0x349DC
addiu sp, sp, -0x18
sw ra, 0x14(sp)

	LI A0, 0x80207700
	JAL 0x80324570
	LI A1, 0x70
	
lw ra, 0x14(sp)
jr ra
addiu sp, sp, 0x18

.headersize (code_ram - code_rom)

.orga code_rom
execonce:
addiu sp, sp, 0xffec; don't get rid of those extra things. they are needed
sw a0, 0x4(sp)
sw a1, 0x8(sp)
sw ra, 0xc(sp)

NOP
; executes once here at start up

lw a0, 0x4(sp); don't get rid of those extra things. they are needed
lw a1, 0x8(sp)
or a0, r0, r0
jal 0x80277ee0
lui a1, 0x8000
lui a0, 0x8034
lui a1, 0x8034
addiu a1, a1, 0xb044
addiu a0, a0, 0xb028
jal 0x803225a0
addiu a2, r0, 0x1
lw ra, 0xc(sp)
jr ra
addiu sp, sp, 0x14

execeveryframe:
addiu sp, sp, -0x28
sw ra, 0x14(sp)
	LW T9, showtotals
	BNE T9, R0, endstuff
	
	LW T0, timershow_left
	BEQ T0, R0, noshow
	
	SUBIU T0, T0, 1
	SW T0, timershow_left

	LW AT, current_rec
	SLL AT, AT, 2
	LI A0, 20
	LI A2, vblanktimer_fmt
	LI A3, vblanktimers_rec - 4
	ADDU A3, A3, AT
	LW A3, 0x0(A3)
	JAL 0x802D62D8
	LI A1, 20
	
	LW AT, current_rec
	SLL AT, AT, 2
	LI A0, 20
	LI A2, globalimer_fmt
	LI A3, globaltimers_rec - 4
	ADDU A3, A3, AT
	LW A3, 0x0(A3)
	JAL 0x802D62D8
	LI A1, 40

noshow:
	LH T1, 0x8033AFA2
	ANDI T1, T1, 0x0020
	BEQ T1, R0, noL

	LW T5, current_rec
	SLL T7, T5, 2
	ADDIU T5, T5, 1
	SW T5, current_rec
	LI T2, 30
	SW T2, timershow_left
	LI T8, vblanktimers_rec
	ADDU T8, T8, T7
	LW T3, 0x8032D580 ; vblank
	SW T3, 0x0(T8)
	LI T8, globaltimers_rec
	ADDU T8, T8, T7
	LW T4, 0x8032d5d4 ; global
	SW T4, 0x0(T8)
	SLTI V0, T4, 10000
	BNE V0, R0, noDone
	NOP
	SW T4, showtotals
noDone:
	
noL:

	B fini

endstuff:
	LI AT, 1
	SW AT, 0x18(SP)
repe:
	; print out the cool table
	LW AT, 0x18(SP)
	SLL AT, AT, 2
	SLL T4, AT, 1
	LI A1, 4
	ADDU A1, A1, T4
	LI A2, vblanktimer_fmt
	LI A3, vblanktimers_rec
	ADDU A3, A3, AT
	LW V1, -0x8(A3)
	LW A3, 0x0(A3)
	BEQ A3, R0, fini
	NOP
	
	; do not make timer diffs for TOTAL
	SLTI T7, T4, 180
	BNE T7, R0, nofixup1
	NOP
	ADDIU V1, R0, 0
nofixup1:
	
	SUBU A3, A3, V1
	JAL 0x802D62D8
	LI A0, 100
	
	LW AT, 0x18(SP)
	SLL AT, AT, 2
	SLL T4, AT, 1
	LI A1, 4
	ADDU A1, A1, T4
	LI A2, globalimer_fmt
	LI A3, globaltimers_rec
	ADDU A3, A3, AT
	LW V1, -0x8(A3)
	LW A3, 0x0(A3)

	; do not make timer diffs for TOTAL
	SLTI T7, T4, 180
	BNE T7, R0, nofixup2
	NOP
	ADDIU V1, R0, 0
nofixup2:
	
	SUBU A3, A3, V1
	JAL 0x802D62D8
	LI A0, 200
	
	LW AT, 0x18(SP)
	SRL T5, AT, 1
	SLL T5, T5, 2
	SLL A3, AT, 3
	LI A1, 4
	ADDU A1, A1, A3
	LI A2, labels
	ADDU A2, A2, T5
	LW A2, 0x0(A2)
	JAL 0x802D62D8
	LI A0, 10
	
	LW T4, 0x18(SP)
	ADDIU T4, T4, 2
	SW T4, 0x18(SP)
	B repe

fini:
addiu t6, r0, 0x1; don't get rid of those extra things. they are needed
lui at, 0x8039
lw ra, 0x14(sp)
jr ra
addiu sp, sp, 0x28

readinputs:
	ADDIU SP, SP, -0x28
	SW RA, 0x14(SP)
	
	LW A1, showtotals
	BNE A1, R0, notas
	
	LW A1, readinputs_data
	ADDIU A2, A1, 4
	SW A2, readinputs_data
	JAL 0x278504
	NOP

notas:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x28

nop
nop
nop
nop

readinputs_data:
	.dw 0x00800000
current_rec:
	.dw 0
	
; padding for records - laziness
	.dw 0, 0
vblanktimers_rec:
	.dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	
	.dw 0, 0
globaltimers_rec:
	.dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
timershow_left:
	.dw 0
showtotals:
	.dw 0

labels:
	.dw label0, label1, label2, label3, label4, label5, label6, label7, label8, label9, label10, label11

label0:
	.asciiz "LOGO"
label1:
	.asciiz "FILE"
label2:
	.asciiz "INTRO"
label3:
	.asciiz "IN BOB"
label4:
	.asciiz "OUT BOB"
label5:
	.asciiz "IN WF"
label6:
	.asciiz "DIE WF"
label7:
	.asciiz "OUT WF1"
label8:
	.asciiz "OUT WF2"
label9:
	.asciiz "IN LAG"
label10:
	.asciiz "IN CCM"
label11:
	.asciiz "TOTAL"

vblanktimer_fmt:
	.asciiz "B %d"
globalimer_fmt:
	.asciiz "G %d"

code_end:
.definelabel code_end_copy, (code_end - (code_ram - code_rom))
