;1ups kill player, remove bowser body anchor
;use with 69 lives setter!

.orga 0xAFA3C
.area 0x8
j 0x802B4080
NOP
.endarea

.orga 0x6F080
.area 0x50
LUI T0, 0x8034
LB T0, 0xB21D(T0)
ADDIU T1, R0, 0x45

BEQ T0, T1, up_nokill
NOP

LUI T8, 0x8034
SB R0, 0xB21E(T8)

up_nokill:
JAL 0x802E4E90
NOP
j 0x802F4A44
NOP
.endarea




;be 0x01 reds for specific level (bowser 2)
.orga 0xADDDC
.area 0x8
j 0x802B40D0
NOP
.endarea

.orga 0x6F0D0
.area 0x50
ADDIU AT, R0, 0x6

LUI T2, 0x8034
LB T2, 0xB249(T2)
SUBI T2, T2, 0x13
BNE T2, R0, red_nofix
NOP

ADDIU AT, R0, 0x1
red_nofix:
LW T0, 0x00F4(T9)
j 0x802F2DE4
NOP
.endarea