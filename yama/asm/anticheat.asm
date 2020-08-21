.orga 0x861C0
	addiu sp, sp, -0x28
	sw ra, 0x14 (sp)
	sw s0, 0x18 (sp)
	
	lhu t1, 0x8033B21A
	slti at, t1, 121
	bne at, r0, end
	nop

	; get destruction spot - bank E
	jal 0x80277F50
	li a0, 0x0e000000

	; get random number and store to s0
	jal 0x80383bb0
	add s0, v0, r0
	
	; add rands16() * 0x10
	sll v0, v0, 4
	jal 0x80383bb0
	add s0, s0, v0

	; do it
	jal 0x80383bb0
	nop
	jal 0x80383bb0
	sh v0, 0x2(s0)
	jal 0x80383bb0
	sh v0, 0x6(s0)
	jal 0x80383bb0
	sh v0, 0xa(s0)
	sh v0, 0xe(s0)

end:
	lw s0, 0x18 (sp)
	lw ra, 0x14 (sp)
	jr ra
	addiu sp, sp, 0x28
