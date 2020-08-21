.orga 0x96a40
	jal 0x80407080
	
.orga 0x1207080
	addiu sp, sp, -0x18
	sw ra, 0x14(SP)

	lb t0, 0x80331620
	li t1, 7
	beq t0, t1, @@overridehint
	nop
	
	jal 0x277f50
	nop
	b @@end
	nop
	
@@overridehint:
	li v0, 0x80407000

@@end:
	lw ra, 0x14(SP)
	jr ra
	addiu sp, sp, 0x18
	
	

.orga 0x9832c
	jal 0x80407100
	
.orga 0x1207100
	addiu sp, sp, -0x18
	sw ra, 0x14(SP)

	lb t0, 0x8032dd84
	li t1, 7
	beq t0, t1, @@overridehint
	nop
	
	jal 0x277f50
	nop
	b @@end
	nop
	
@@overridehint:
	li v0, 0x80407000

@@end:
	lw ra, 0x14(SP)
	jr ra
	addiu sp, sp, 0x18
	
	
	
	
.orga 0x2278e0
	jal 0x80407180
	
.orga 0x1207180
	addiu sp, sp, -0x18
	sw ra, 0x14(SP)

	lb t0, 0x801a81a0
	li t1, 6
	beq t0, t1, @@overridehint
	nop
	
	jal 0x277f50
	nop
	b @@end
	nop
	
@@overridehint:
	li v0, 0x80407000

@@end:
	lw ra, 0x14(SP)
	jr ra
	addiu sp, sp, 0x18