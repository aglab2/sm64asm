.orga 0x32F50
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LUI AT, 0x00FF
	ORI AT, AT, 0xFFFF
	AND T1, A0, AT
	LUI V0, 0x8034
	ADDIU V0, V0, 0xB400
	SRL V1, A0, 0x16
	ANDI V1, V1, 0x03FC
	ADDU V0, V0, V1
	LW V0, 0x0000 (V0)
	ADDU T9, V0, T1
	LUI AT, 0x8000
	JAL 0x80406500
	OR V0, T9, AT

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP

.orga 0x120656C
	JR RA
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

.orga 0x918f0
	LUI V1, 0x8040
	ADD V1, V1, A0
	JR RA
	LB V0, 0x6600(V1)

.orga 0x1206600
.area 0x100, 0xff
.endarea

; vanilla symbol table
.orga 0x1206600 + '!'
.db 36
.orga 0x1206600 + '#'
.db 37
.orga 0x1206600 + '?'
.db 38
.orga 0x1206600 + '&'
.db 39
.orga 0x1206600 + '%'
.db 40
.orga 0x1206600 + '*'
.db 50
.orga 0x1206600 + '+'
.db 51
.orga 0x1206600 + ','
.db 52
.orga 0x1206600 + '-'
.db 53
.orga 0x1206600 + '.'
.db 54
.orga 0x1206600 + '/'
.db 55

; extra symbols
.orga 0x1206600 + 0x10
.db 0x1a
.orga 0x1206600 + 0x11
.db 0x1f
.orga 0x1206600 + 0x12
.db 0x21
.orga 0x1206600 + 0x13
.db 0x23
.orga 0x1206600 + 0x14
.db 0x24
.orga 0x1206600 + 0x14
.db 0x24
.orga 0x1206600 + 0x15
.db 0x25
.orga 0x1206600 + 0x16
.db 0x26
.orga 0x1206600 + 0x17
.db 0x27
.orga 0x1206600 + 0x18
.db 0x28
.orga 0x1206600 + 0x19
.db 0x29
.orga 0x1206600 + 0x1a
.db 0x2a
.orga 0x1206600 + 0x1b
.db 0x2b
.orga 0x1206600 + 0x1c
.db 0x2c
.orga 0x1206600 + 0x1d
.db 0x2d
.orga 0x1206600 + 0x1e
.db 0x2e
.orga 0x1206600 + 0x1f
.db 0x2f
.orga 0x1206600 + 0x20
.db 0x30
