.orga 0x1206500
	.dw 0x00090000
	.dw 0x08000000
	.dw 0x0c000000, 0x80406540
	.dw 0x09000000
	
.orga 0x1206540
	lui v1, 0x8040
	sw r0, 0x36d0(v1)
	jr ra
	sw r0, 0x36d4(v1)
	
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop