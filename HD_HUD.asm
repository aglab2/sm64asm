.org 0x919f8
main:
ADDIU SP, SP, 0xFFD8
SW RA, 0x0014 (SP)
SW A0, 0x0028 (SP)
LUI A0, 0x0200
JAL 0x80277F50
ADDIU A0, A0, 0x7700


//set up the texture
LUI a3, 0x8034
LW a2, 0xB06C (a3)
ADDIU T7, a2, 0x0018
SW T7, 0xB06C (a3)
LUI T8, 0xE700
SW T8, 0x0000 (a2)
SW R0, 0x0004 (a2)

LUI T3, 0xFD10
SW T3, 0x0008 (a2)
LB T6, 0x002B (SP)
SLL T7, T6, 0x2
ADDU T8, v0, T7
LW T9, 0x0000 (T8)
SW T9, 0x000C (a2)

LUI T3, 0x0600
SW T3, 0x0010 (a2)


addiu at, r0, 0x0200
srl t1, t9, 0x10
nop;beq t1, at, normaltexture
hdtexture:
ori v0, r0, 0x1
LUI T6, 0x002d
ADDIU T6, T6, 0x6a90
beq r0, r0, unite
SW T6, 0x0014 (a2)
normaltexture:
LUI T6, 0x0201
ori v0, r0, 0x0
ADDIU T6, T6, 0x1AF8
SW T6, 0x0014 (a2)
unite:


LW RA, 0x0014 (SP)
JR RA
ADDIU SP, SP, 0x0028

.org 0x91c64
main2:
lui t7, 0x1000
ori t7, t7, 0x0800
bne v0, r0, HD
lui t2, 0x1000
ori t7, t2, 0x0400
HD:
sw t7, 0x0004 (T8)
lw ra, 0x14 (SP)
jr ra
addiu sp, sp, 0x38

.org 0x91aa0
.dd 0xF3000000073FF100
.dd 0xE700000000000000
.dd 0xF510100000094250
.dd 0xF20000000007C07C
.dd 0xB800000000000000