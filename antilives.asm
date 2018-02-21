.orga 0x861C0 ; Set ROM address
.area 0x90 ; Set data import limit to 0x90 bytes
addiu sp, sp, 0xFFE8
sw ra, 0x14 (sp)

LUI T8, 0x8034
LUI T9, 0x802D

LB T0, 0xB21D(T8)
LB T1, 0xB250(T9)

BEQ T0, T1, lives_noaddone
NOP

ADDIU T0, T0, 2
SB T0, 0xB21D(T9)

lives_noaddone:
SB T0, 0xB250(T9)

lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea

.orga 0x86250 ; 0x802CB250
.dw 0x00000000
