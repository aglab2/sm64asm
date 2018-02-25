;make this warp be random
;overwritten 1st function in bowsey, from 0x30 offset

;overwritten bowser behav, rip bowsey
.orga 0x21B650 ;behav 0x13001850

.dw  0x00060000
.dw  0x11010009
.dw  0x102A2000
.dw  0x10050000
.dd  0x0C000000802B78A8
.dw  0x08000000
.dd  0x0C000000802AAA60
.dw  0x09000000

.orga 0x728A8
.area 0xE0
	ADDIU SP, SP, 0xFFE8
	SW RA, 0x14 (SP)

	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	LUI T1, 0x8041
	LB T1, 0x0E(T1)
	
	BEQ T1, R0, warp_normalmode
	NOP
	
	;speedrun mode somewhere not here...
	J 0x80304608
	NOP
	
warp_normalmode:

	JAL 0x80383BB0
	NOP

warp_restart:
;This T1 is offset to set byte
	LUI T1, 0x8041
	ADDIU V0, V0, 1
	
;Check if 10th level case
	LW T0, 0x08(T1)
	ADDIU T2, R0, 10
	BEQ T2, T0, warp_boss
	NOP
	
;Regular levels case
	ANDI V0, V0, 15 ;leave only values from 0 to 15
	B warp_checklevel
	ADDIU V0, V0, 0x40
;Bosses case
warp_boss:
	ANDI V0, V0, 3 ;leave only values from 0 to 4
	ADDIU V0, V0, 0x30


warp_checklevel:
	ADD T1, T1, V0
	LB T0, 0x0(T1)

	BNE R0, T0, warp_restart
	NOP

;Level picked, set as picked :]
	SB V0, 0x0(T1) ;it just sets any but not 0


warp_setwarp:
	SH V0, 0x188(V1)

	LW RA, 0x14 (SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea