.orga 0x91ec4
	JAL 0x80404980
	NOP

; requires distance path

.orga 0x12039d4
	BNEZ T1, 0x1203a20

.orga 0x12039ec
	LW A0, 0x80361160
	LB T0, 0x189(A0)
	LI T1, 3
	BNE T0, T1, end
	NOP
	
	LI A2, 0x404a00
	JAL 0x8029edcc
	LI A1, 0
	
	LW A0, 0x80361160
	SW A0, 0x1ac(V0)

end:
	JAL 0x2c19c0
	NOP

	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	NOP
	
.orga 0x1204980
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	
	JAL 0x80404a10 ;TreasureHunt::Draw
	NOP

	LW T3, 0x8033B06C
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
	
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP