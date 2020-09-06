.orga 0x283434-0x245000
	jal 0x80406200
	nop
	
.orga 0x1206200
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	
	lhu t0, 0x8032DDF8
	li t1, 0x17
	bne t1, t0, nooverride
	nop

	li at, -11000.0
	mtc1 at, f6
	
nooverride:
	c.lt.s f6, f4
	nop

	lw ra, 0x14(sp)	
	jr ra
	addiu sp, sp, 0x18