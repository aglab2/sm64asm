.org 0x112a0
test:
	jal 0x29BF64		//adds RA by AC if no ceiling available
	nop
	bne v1, r0, 0x11354	;lw t0, 0x0050 (SP)
	nop	;mtc1 r0, f18
	lwc1 f16, 0x004c (T0)
	c.le.s f18, f16
	nop
	bc1f 0x11308
	nop
	swc1 f18, 0x004c (T0)

.orga 0x56f64
second:
	lui t0, 0x8034
	lw t1, 0xb1d4 (T0)
	beq t1, r0, yesend
	li v1, 1
	lh t2, 0x0008 (T1)
	sll t2, t2, 0x2
	mtc1 t2, f4
	cvt.s.w f4, f4
	lwc1 f14, 0xb1b0 (T0)

	c.lt.s f4, f14
	nop
	bc1t yesend
	li v1, 1
	lui at, 0x4348
	mtc1 at, f0
	add.s f14, f14, f0
	lh t2, 0x0006 (T1)
	sll t2, t2, 0x2
	mtc1 t2, f4
	cvt.s.w f4, f4
	c.lt.s f14, f4
	nop

end:
	lui t0, 0x8034
	lw t1, 0xb1d4 (T0)
	lui at, 0x4248
	mtc1 at, f6
	lwc1 f2, 0x001c (T1)
	mul.s f2, f2, f6
	lwc1 f4, 0x0024 (T1)
	mul.s f4, f4, f6
	lwc1 f0, 0xb1ac (T0)
	add.s f0, f0, f2
	swc1 f0, 0xb1ac (T0)

	lwc1 f0, 0xb1b4 (T0)
	add.s f0, f0, f4
	swc1 f0, 0xb1b4 (T0)
	lw t0, 0x0050 (SP)
	mtc1 r0, f18
	li v1, 0

yesend:
	jr ra
	nop

.org 0x57030
	nop