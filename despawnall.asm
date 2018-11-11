.orga 0x21B140 ;1340
	.dw 0x00040000
	.dw 0x08000000
	.dd 0x0C000000802AFF30
	.dw 0x09000000

.orga 0x6AF30
	ADDIU SP, SP, -0x30
	SW RA, 0x14(SP)
	
	LUI A0, 0x1300
	JAL 0x8029F95C
	ADDIU A0, 0x3E64
	
	BEQ V0, R0, end
	NOP
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	; setup behaviour
	LUI A0, 0x1300
	JAL 0x277F50
	ORI A0, A0, 0x01F4
	SW V0, 0x20(SP)
	
	LUI A0, 0x1300
	JAL 0x277F50
	ORI A0, A0, 0x4898
	SW V0, 0x24(SP)
	
	LUI A0, 0x1300
	JAL 0x277F50
	ORI A0, A0, 0x48E0
	SW V0, 0x28(SP)

	
	;setup loop
	LI V0, 0x8033D488
	LI T0, 0x80360E88

loop:
	BEQ T0, V0, endloop
	NOP
	
	LW T2, 0x20C(V0)
	
	; compare behavs
	LW T9, 0x20(SP)
	BEQ T2, T9, despawn
	NOP
	LW T9, 0x24(SP)
	BEQ T2, T9, despawn
	NOP
	LW T9, 0x28(SP)
	BEQ T2, T9, despawn
	NOP
	
	B loopcont
	NOP
	
despawn:
	; kill object
	SH R0, 0x74(V0)
	
loopcont:
	ADDIU V0, V0, 0x260
	B loop
	NOP

endloop:
	; kill ourself too
	; SH R0, 0x74(V1)

end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x30