.org 0x105F4
; JAL 0x2521A0
	J 0x2BBB98
	LW A0, 0x18(SP)

.orga 0x76B98
.area 0x70, 0x00
	LB V1, 0x07(A0)
	ANDI V1, V1, 0x02
	BEQ V1, R0, quicksand_yes
	NOP
;Jump to regular ground
	J 0x802554B0
	NOP

quicksand_yes:
	J 0x802555FC
	NOP
.endarea