.orga 0x34a10
	lhu t0, 0x80207700 + 0x1d0
	li t1, 2
	bge t1, t0, ok ; gSaveBuffer.menuData[0].soundMode <= 2
	nop
	
; we get bs here, drop all saves
	jal 0x8027951c ; wipe_main_menu_data
	nop
	jal 0x802798fc ; save_file_erase
	li a0, 0
	jal 0x802798fc
	li a0, 1
	jal 0x802798fc
	li a0, 2
	jal 0x802798fc
	li a0, 3

ok:
	lw ra, 0x1c(sp)
	jr ra
	addiu sp, sp, 0x30