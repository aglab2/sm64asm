;survival object
;spawns random hardcoded enemy

;overwrites 2nd part of bowser behaviour
.orga 0x21B680 ;behav 0x13001880
.dw  0x00040000
.dw  0x08000000
.dd  0x0C000000802B75A4
.dw  0x09000000

;function has length 0x2CC, only first CC is used
.orga 0x725A4
.area 0xCC

;prologue
ADDIU SP, SP, 0xFFE8
SW RA, 0x14 (SP)

LUI T0, 0x8041
LB T0, 0x0D(T0)
BNE T0, R0, spawn_no

LUI V1, 0x8036
LW V1, 0x1160(V1)

LW T0, 0x154(V1)
ADDIU T1, R0, 50

BNE T0, T1, spawn_no
NOP

SW R0, 0x154(V1)

JAL 0x80383BB0
NOP

ANDI V0, V0, 3

ADDIU T8, RA, 0x18 ;RA shows to ANDI V0, V0, 3l we need ptr to first cmd

SLL V0, V0, 4
ADDU T8, T8, V0

JR T8
NOP

;spawn heave-ho
ADDIU A1, R0, 89
LUI A2, 0x1300
B spawn_spawn
ADDIU A2, A2, 0x1548

;spawn chuckya
ADDIU A1, R0, 223
LUI A2, 0x1300
B spawn_spawn
ADDIU A2, A2, 0x0528

;spawn amp2
ADDIU A1, R0, 194
LUI A2, 0x1300
B spawn_spawn
ADDIU A2, A2, 0x3354

;spawn koopa star
ADDIU A1, R0, 122
LUI A2, 0x1300
B spawn_spawn
ADDIU A2, A2, 0x4580


;spawn chuckya
spawn_spawn:
JAL 0x8029EDCC
ADD A0, R0, V1

spawn_no:
;epilogue
LW RA, 0x14 (SP)
JR RA
ADDIU SP, SP, 0x18

.endarea