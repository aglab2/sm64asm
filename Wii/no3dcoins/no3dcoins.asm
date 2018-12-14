;00AB240C / 03000000
;00AB7ACC / 030056C0 ;vertices
;00AB7B8C / 03005780 ;textures
;00AB9D4C / 03007940 ;dl

;00ACF284 / 0301CE78 ;???

;restore AB7ACC - AB9D4C

.orga 0x66810
	LUI T8, 0x8036
	LW T8, 0x1160(T8)
	SW V0, 0xC8(T8)
	
.orga 0x66A28
	NOP
	NOP
	LW RA, 0x14(SP)
	ADDIU SP, SP, 0x20
	JR RA
	NOP

.orga 0x66B40
	sub.s F12, F6, F8

.orga 0x218EDC
	.incbin "coingeo.bin"
.orga 0xAB7ACC
	.incbin "coindata.bin"
.orga 0x21A630
	.incbin "coinbehav1.bin"
.orga 0x21A70C
	.incbin "coinbehav2.bin"
.orga 0x21A7D8
	.dw 0x0F1A0001
.orga 0x21A7AC
	.dw 0x21000000
.orga 0x21A938
	.dw 0x0E4303E8
.orga 0x21C394
	.dw 0x21000000
.orga 0x21C3B0
	.dw 0x0C000000
.orga 0x21C3B8
	.dw 0x0F1A0001
.orga 0x21CE68
	.incbin "coinbehav3.bin"
.orga 0x21DCB4
	.dw 0x21000000
.orga 0x21DCDC
	.dw 0x0F1A0001