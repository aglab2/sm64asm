.orga 0x861C0
.area 0x90
addiu sp, sp, -0x18
sw ra, 0x14 (sp)

LUI AT, 0x8034
LH T0, 0xAFA2(AT)

ANDI T1, T0, 0x0200
BEQ T1, R0, debug_noleft
NOP


lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea