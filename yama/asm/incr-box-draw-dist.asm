.orga 0x0021C074
	.dw 0x80406400

.orga 0x1206400
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	
	jal 0x802C19C0
	nop
	
	li t0, 30000.0
	lw t1, 0x80361160
	sw t0, 0x19c(t1)

	lw ra, 0x14(sp)	
	jr ra
	addiu sp, sp, 0x18