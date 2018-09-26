;door that spawn to warp ID 0x20+(max ID of stars collected in level)

;use behav 1CB0, model 38(regular door) in tt64 (or any other door on demand)
;bparam1 byte to check stars in (12 for c1, 12+X for c1+X)
;bparam2 warp offset for star 1
;so warp to be used will be BPARAM2+(Star in BPARAM 1)

;act selector switches behaviour of warp
;0 - normal mode, furthest warp
;1 - normal mode, furthest warp
;2 - no warpzones mode, furthest warp
;3 - normal mode, nearest warp
;4 - no warpzones mode, furthest warp

;Normal Mode = if mario collected warpzone star (s7), he will be warped to it not taking other stars in account
;No warpzones Mode = star 7 won't be taken into account
;Furthest Warp = Mario will be taken to the warp closest to end of level depending on stars collected
;Nearest Warp = Mario will be taken to closest not collected star before warp

;If BPARAM2 >=0x60 then door is locked with bparam1=1
;If BPARAM2 >=0x70 then door is locked with bparam1=2

.orga 0x21BAB0 ;behav 0x13005310
.dw  0x00090000
.dd  0x0C000000802BB888
.dw  0x102A0800
.dd  0x0400000013000B14
.dw  0x102A0004
.dw  0x110100C9
.dd  0x27260000030156C0
.dw  0x28000000
.dd  0x2A0000000301CE78
.dw  0x2300000000500064
.dw  0x10050000
.dw  0x0E4303E8
.dw  0x2D000000
.dd  0x0C000000802ACC3C
.dw  0x08000000
.dd  0x0C000000802ACAC8
.dw  0x09000000

.orga 0x76888
.area 0x100
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
;EEPROM offset loader start
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI T8, 0x8020
	ADDIU T8, T8, 0x7700 ;current eep base
	
warp_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, warp_fileselectend
	NOP
	ADDIU T8, T8, 0x70
	B warp_fileselectloop
	NOP
warp_fileselectend:
	LB T7, 0x0188(V1)
	ADDU T8, T8, T7
;EEPROM offset loader fini

	LUI T6, 0x8033
	LB T6, 0x1620(T6)
	SUBIU T6, T6, 1
	ANDI T3, T6, 0x1 ;1=normal mode, 	0=no warpzones
	ANDI T4, T6, 0x2 ;1=furthest warp,	0=nearest warp
	
	
;Make door go to warp BPARAM2 - init it is
	LB T1, 0x189(V1)
	LB T7, 0x189(V1) ;ADDIU T7, R0, 0x20
	LB T9, 0x0(T8)

;Remove cannon and star 7 if no warpzones
	ANDI T2, T9, 0x40
	BNE T3, R0, warp_repeat
	ANDI T9, T9, 0x3F
	
;If Star 7 is set - warp to 0x28
	BEQ T2, R0, warp_repeat
	NOP
	
	B warp_fini
	ADDIU T7, R0, 0x27
	
warp_repeat:
;Use T9 as check for 0 for furthest, T9 & 0x01 for nearest
	BEQ T4, R0, warp_nonearest
	ADD T2, T9, R0
	ANDI T2, T9, 0x1
warp_nonearest:
	BEQ T2, R0, warp_fini
	NOP
	
	ADDIU T7, T7, 1
	SRL T9, T9, 1
	
	B warp_repeat
	NOP	

warp_fini:
	SLTI AT, T1, 0x60
	ADDIU T2, R0, 0
	BNE AT, R0, warp_actualend
	SB T2, 0x188(V1)
	
	SLTI AT, T1, 0x70
	ADDIU T2, T2, 1
	BNE AT, R0, warp_actualend
	SB T2, 0x188(V1)
	
	ADDIU T2, T2, 1
	SB T2, 0x188(V1)
	
warp_actualend:
	JR RA
	SB T7, 0x0189(V1)
.endarea