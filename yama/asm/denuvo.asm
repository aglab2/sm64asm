; 80207700 to relocate for R/O?
; star count
; areaPtr, spawnPointPtr, levelSpawnPtr, hpPtr, menuModifiedPtr, spawnStatusPtr, igtigtPtr
; mario state is too scary

; full protection against quad/rom manager attacks
.orga 0xfb068
	JAL 0x80406000

.orga 0x1206000
	addiu sp, sp, -0x18
	sw ra, 0x14(sp)
	
	li t0, 0x20
	bne t0, a0, normal
	nop

	li a0, 0x19
normal:
	jal 0x0027868C
	nop

	lw ra, 0x14(sp)
	jr ra
	addiu sp, sp, 0x18
	

.macro ENCODE, off
	.if readu8(outputname(), off) == 0x19
	.orga off
		.db 0x20
	.endif
.endmacro
	
ENCODE 0x2ac097
ENCODE 0x2ac0ab
ENCODE 0x2ac0bf
ENCODE 0x2ac0d3
ENCODE 0x2ac0e7
ENCODE 0x2ac0fb
ENCODE 0x2ac10f
ENCODE 0x2ac123
ENCODE 0x2ac137
ENCODE 0x2ac14b
ENCODE 0x2ac15f
ENCODE 0x2ac173
ENCODE 0x2ac187
ENCODE 0x2ac19b
ENCODE 0x2ac1af
ENCODE 0x2ac1c3
ENCODE 0x2ac1d7
ENCODE 0x2ac1eb
ENCODE 0x2ac1ff
ENCODE 0x2ac213
ENCODE 0x2ac227
ENCODE 0x2ac23b
ENCODE 0x2ac24f
ENCODE 0x2ac263
ENCODE 0x2ac277
ENCODE 0x2ac28b
ENCODE 0x2ac29f
ENCODE 0x2ac2b3
ENCODE 0x2ac2c7
ENCODE 0x2ac2db
ENCODE 0x2ac2ef

; Weak protection against text manager
.orga 0x813bbe
	.dw 0x02ffffff