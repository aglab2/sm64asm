.orga 0xa6f40
	JAL 0x802a057c
	NOP
	NOP

; rewrite for 3 bullies
.orga 0xa6c88
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)
	LW V1, 0x801ce0a8
	JALR V1
	NOP
	LI AT, 1
	BNE V0, AT, nope
	NOP
	JAL 0x2a37ac
	NOP
	LUI A0, 0x8040
	JAL 0x402700
	ORI A0, A0, 0x4fe4
nope:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

; rewrite for a single bully
.orga 0xA68B8
	LW V1, 0x801ce0ac
	JALR V1
	NOP
	LI AT, 1
	BNE V0, AT, 0xa69b8
	LW T8, 0x80361160
	LW T7, 0x144(T8)
	BNEZ T7, 0xA6920

; star spawners
.orga 0xad61c
	LW V1, 0x801ce0bc
	JALR V1
	NOP
	BEQ V0, R0, 0xad758
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

; red star spawners
.orga 0xadddc
	lw t0, 0xf4(t9)
	slti at, t0, 6
	bne at, r0, 0xaddfc