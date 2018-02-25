.orga 0xD448
JAL 0x803843E0
nop


.orga 0x101160
lui t1, 0x8036
lw t1, 0x1158 (T1)
lw t0, 0x0214 (T1)
beq t0, r0, skip
nop
lwc1 f2, 0x00b0 (T0)
lui t2, 0x8034
lwc1 f4, 0xb1bc (T2)
mtc1 r0, f6
c.lt.s f2, f6
nop
bc1t skip
nop
add.s f4, f2, f4
swc1 f4, 0xb1bc (T2)
lwc1 f18, 0xb1b0 (T2)
add.s f18, f18, f2
swc1 f18, 0xb1b0 (T2)
skip:
jr ra
nop