; clears flag OBJ_MOVE_ABOVE_LAVA from klepto
.orga 0xcc2c0
	LW T0, 0xEC (T6)
	ANDI T0, T0, 0xf7ff
	SW T0, 0xEC (T6)
	JAL 0x2FA1B0
	LWC1 F12, 0xF4 (T6)
	LW T8, 0x80361160
	JAL 0x2A2748
	SH V0, 0x1B0 (T8)
