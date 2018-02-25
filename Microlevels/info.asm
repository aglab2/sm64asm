;string start from 0x726F0 + 0x140
;replaced klepto behaviour

.orga 0x21F110; behaviour 5310
.dw  0x00040000
.dw  0x08000000
.dd  0x0C000000802B76F0
.dw  0x09000000

.orga 0x72830 ;802B7830
.asciiz "CHALLENGE %d"
.orga 0x72850 ;802B7850
.asciiz "CONGRATULATIONS"

.orga 0x726F0
.area 0x100
ADDIU SP, SP, 0xFFE8
SW RA, 0x14 (SP)

LUI T3, 0x8034
LUI T4, 0x8041

LUI V1, 0x8036
LW V1, 0x1160(V1)

LW T9, 0x154(V1)

BNE T9, R0, challenge_showinfo
NOP

ADDIU T8, R0, 0x0880
SH T8, 0xB21E (T3)

LB T8, 0xB24B (T3)
BEQ T8, R0, challenge_failed
NOP

;add 1 to challenge counter
LW T8, 0x0008(T4)
ADDIU T8, T8, 1
B challenge_showinfo
SW T8, 0x0008(T4)

;remove 1 life from player
challenge_failed:
LB T8, 0xB21D (T3)
SUBI T8, T8, 1
SB T8, 0xB21D (T3)

challenge_showinfo:
;show challenge number
LW A3, 0x0008(T4)
LI A2, 0x802B7830; challenge %d

SLTI AT, A3, 21
BNE AT, R0, challenge_nocongrats
NOP

LI A2, 0x802B7850

challenge_nocongrats:
ORI A0, R0, 80
JAL 0x802D62D8
ORI A1, R0, 160

;show timah if speedrun mode on
LUI AT, 0x8041
LB T0, 0xE(AT)
BEQ T0, R0, info_end

LHU T3, 0x04(AT)
LUI AT, 0x8037
JAL 0x802EE8F4
SH T3, 0x006E(AT)

info_end:
LW RA, 0x14 (SP)
JR RA
ADDIU SP, SP, 0x18
.endarea