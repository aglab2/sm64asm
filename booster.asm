.orga 0x861C0 ; Set ROM address
.area 0x90 ; Set data import limit to 0x90 bytes
addiu sp, sp, -0x18
sw ra, 0x14 (sp)

.f_testInput BUTTON_L, BUTTON_HELD, booster_no

LI T0, 300.0
LUI V1, 0x8034
SW T0, 0xB1C4(V1)

booster_no:	

lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea

