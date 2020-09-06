.org 0x6668
jal 0x405f00
nop
nop
JAL 0x8024A700
OR A3, R0, R0
//close pause menu and disable controller input
OR A0, R0, R0
JAL 0x802497B8
OR A1, R0, R0
LUI AT, 0x8034
SH R0, 0xBACC (AT)
LH T1, 0xC848 (at)
LUI t3, 0xFFFF
ORI t3, t3, 0x7FFF
AND T2, T1, t3
SH T2, 0xC848 (AT)
nop
nop
nop

.org 0x1205f00
; current area
lw t3, 0x8032ddcc
; warp to find
lbu a0, 0x8033B249 
li a1, 0xe
bne a0, a1, @@default_warp
nop 
lbu a0, 0x8033B24A
li a1, 3
bne a0, a1, @@default_warp
nop

b @@do
li at, 11
@@default_warp:
li at, 0xf1

@@do:
; 0x14 offsetof warpNodes in Area
; 0x8 offsetof next in ObjectWarpNode
; 0xc=0x14-0x8
addiu t3, t3, 0xc

loop777:
; load next and check if is the one necessary
lw t3, 0x08 (T3)
lbu t2, 0x0000 (T3)
bne t2, at, loop777
nop

; override arguments from the node
lbu a0, 0x0001 (t3)
lbu a1, 0x0002 (t3)
lbu a2, 0x0003 (t3)
jr ra
nop