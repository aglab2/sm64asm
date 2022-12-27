;8037dcd4
;.engine         0x0000000080378800    0x13490 load address 0x00000000000f5580
;FAA54

.orga 0xfaa54
.area 0x74
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	
	lui t9, 0x8039
	lw t6, 0xbd80(t9)

	lbu a2, 0x1(t6)
	lw a3,  0x4(t6)
	bne a2, 5, doit
	lbu t1, 0x4(t6)
	
	bne t1, 0xe, doit
	nop
	
	b end
	
doit:
	lw a0, 0xbca0(t9)
	jal 0x37bc90
	or a1, r0, r0
	
	jal 0x37cc74
	addu a0, v0, r0

end:	
	lui t9, 0x8039
	lw t0, 0xbd80(t9)
	addiu t0, t0, 8
	sw t0, 0xbd80(t9)

	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18
.endarea