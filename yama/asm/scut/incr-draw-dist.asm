.orga 0x1200d90
	addiu sp, sp, -0x18
	sw ra, 0x14(SP)

	JAL 0x80400E30
	nop

	li t0, 30000.0
	lw t1, 0x80361160
	sw t0, 0x19c(t1)
	
	lw ra, 0x14(SP)
	jr ra
	addiu sp, sp, 0x18
	
.orga 0x1204380
	addiu sp, sp, -0x18
	sw ra, 0x14(SP)

	JAL 0x803839CC
	nop

	li t0, 30000.0
	lw t1, 0x80361160
	sw t0, 0x19c(t1)
	
	lw ra, 0x14(SP)
	jr ra
	addiu sp, sp, 0x18