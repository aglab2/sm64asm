.orga 0x120AC00
.dw 0x00040000
.dw 0x08000000
.dd 	0x0C0000008040AD00
.dw 0x09000000

.orga 0x120AB00
.asciiz "AHAHAHAHAHAAHAAHAHAHA"
.orga 0x120AB20
.asciiz "LITERALLY HANDLING GOD"
.orga 0x120AB40
.asciiz "I WISH IT WAS EASY"
.orga 0x120AB60
.asciiz "E*PLORER IN BLOOD"
.orga 0x120AB80
.asciiz "SECRETS ARE FREE LOL"
.orga 0x120ABA0
.asciiz "PIRATE SHIP FROM MA"
.orga 0x120ABC0
.asciiz "WHO NEEDS ASSIST"
.orga 0x120ABE0
.asciiz "I WANNA SEE"

.orga 0x120AC20
.asciiz "IDIOT"
.orga 0x120AC40
.asciiz "NOTEBLOCKS ARE FUN"
.orga 0x120AC60
.asciiz "WIND IS SO DUMB"
.orga 0x120AC80
.asciiz "YOU FOUND A SECRET"
.orga 0x120ACA0
.asciiz "NO WAY IT IS POSSIBLE"
.orga 0x120ACC0
.asciiz "SHARP EYES ARE GOOD"
.orga 0x120ACE0
.asciiz "BREAKING COURSE FAIL"

.orga 0x120AD00
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	LW V1, 0x80361160
	LW T0, 0x154(V1)
	LI T1, 100
	BEQ T0, T1, despawn
	NOP
	
	LI A0, 160
	LI A1, 40
	jal 0x802D66C0
	LW A2, 0x188(V1)
	B end
	NOP
	
despawn:
	SW R0, 0x74(V1)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

.orga 0x21DEA8
	.dd 0x0C0000008040AA00

.orga 0x120AA00
.area 0x100, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	JAL 0x802F45B8
	NOP
	
	LW V1, 0x80361160
	LW T0, 0x74(V1)
	LI T1, 0xFFFF0000
	AND T2, T0, T1
	BNE T2, R0, fini
	NOP
	
	ADD A0, R0, V1
	LI A1, 0
	LI A2, 0x0040AC00
	JAL 0x8029EDCC
	NOP
	
	LW V1, 0x80361160
	LW T0, 0x188(V1)
	SW T0, 0x188(V0)

fini:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea