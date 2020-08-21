.orga 0x1206000
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	
	lw v0, 0x80361160
	lw t0, 0x154(v0)
	
	li t6, 300
	beq t0, t6, @@yellow
	nop
	
	li t4, 3
	div t0, t4
	mfhi t1
	beq t1, r0, @@noyellow
	nop
	
@@yellow:
	jal 0x8040A4F0
	nop

@@noyellow:
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18

.orga 0x1206100
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	
	lw v0, 0x80361160
	
	lw t9, 0x108(v0)
	beq t9, r0, @@purple
	nop
	
	lw t0, 0x154(v0)
	
	li t6, 300
	beq t0, t6, @@purple
	nop
	
	li t4, 3
	div t0, t4
	mfhi t1
	beq t1, r0, @@nopurple
	nop
	
@@purple:
	jal 0x8040A8D8
	nop

@@nopurple:
	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18
