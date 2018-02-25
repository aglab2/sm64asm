// [ARMIPS 0.9+] Antisoftlock service
 
.orga 0x861C0
.area 0x90
addiu sp, sp, -0x18
sw ra, 0x14 (sp)

JAL 0x31129C
NOP

lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea



;using last 0xDC bytes as RAM
;ram start 0xCC494 -> 0x80311494

.orga 0xCC494
.area 0xDC
NOP
NOP
NOP
.endarea

.orga 0xCC29C
.area 0x200
LUI T0, 0x8034
LUI T1, 0x8032

;check sliding
LW T9, 0xB17C(T0)
LUI T8, 0x0088
ADDIU T8, T8, 0x0456
BNE T9, T8, anti_end
NOP
;check if in menu
;LW T9, 0xB238(T0)
;BNE T9, R0, anti_end
;NOP

;check if stuck
LW T2, 0xB1AC(T0)
LW T3, 0xB1B0(T0)
LW T4, 0xB1B4(T0)

LUI T1, 0x8031
LW T5, 0x1494(T1)
LW T6, 0x1498(T1)
LW T7, 0x149C(T1)

BNE T2, T5, anti_nostuck
NOP
BNE T3, T6, anti_nostuck
NOP
BNE T4, T7, anti_nostuck
NOP

anti_fixstuck:
;LUI T8, 0x0000
;ADDIU T8, T8, 0x4220
;SH T8, 0xB1BC(T0)

;LUI T8, 0x0400
;ADDIU T8, T8, 0x0440
;SW T8, 0xB17C(T0)

LWC1 F0, 0xB1B4(T0)
LUI T1, 0x3100
MTC1 T1, F1
ADD.S F0, F0, F1
SWC1 F0, 0xB1B0(T0)

anti_nostuck: ;save prev coord
LUI T1, 0x8031
SW T2, 0x1494(T1)
SW T3, 0x1498(T1)
SW T4, 0x149C(T1)

anti_end:
JR RA
NOP
.endarea