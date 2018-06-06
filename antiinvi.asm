//walls on no trianlge grounded 80255B9C
//walls on invis wall grounded 80255c44
//251708 writes new values for speed and rotation
//8026B5F4

//80256b24 returns 2 for invis walls and 0 if its fine?
	//802560ac stores 2 on sü+0x18 which gets returned above, modfy this?
	//8025634C decides that v0 is dead
//80380E8C seems to move mario, somehow resets his pos if hes above a ceiling
//802563D8 actually moves mario


//80256278 needs to be changed to branch if its a false alarm

//(make ceilings push mario outwards)
.org 0x112a0
test:
	jal 0x29BF64		//adds RA by AC if no ceiling available
	nop
	lw t0, 0x0050 (SP)
	mtc1 r0, f18
	lwc1 f16, 0x004c (T0)
	c.le.s f18, f16
	nop
	bc1f 0x11308
	nop
	swc1 f18, 0x004c (T0)

.org 0x56f64
second:
	lui t0, 0x8034
	lw t1, 0xb1d4 (T0)
	beq t1, r0, yes
	nop
	lh t2, 0x0008 (T1)
	sll t2, t2, 0x2		//only needed with extended boundaries?
	mtc1 t2, f4
	cvt.s.w f4, f4
	lwc1 f14, 0xb1b0 (T0)

	c.lt.s f4, f14
	nop
	bc1t yes
	nop
	lui at, 0x4348
	mtc1 at, f0
	add.s f14, f14, f0
	lh t2, 0x0006 (T1)
	sll t2, t2, 0x2		//only needed with extended boundaries?
	mtc1 t2, f4
	cvt.s.w f4, f4
	c.lt.s f14, f4
	nop
	bc1f end
	nop
	//j 0x4

yes:
	addiu ra, ra, 0x00ac
	jr ra
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
	//add some push here

yesend:
	jr ra
	nop

.org 0x10c44
grounded:
	jal 0x29c030
	addiu v0, r0, 0x0

.org 0x57030
groundedwalls:
	addiu ra, ra, 0x0000
	jr ra
	nop