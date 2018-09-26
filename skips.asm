// Peach Skip
.org 0x6BD4
ADDIU R0, R0, $0009

// Lakitu Skip
.org 0x6D90
ADDIU S0, R0, $0000

// Skips Mario Head Screen at beginning of the game (but not after a Game Over)
.org 0x9114B8
TGEI T0, 0x0000
BNEZ R0, 0x00911CF0

// Level Intro Text Skips
.org 0x4B7C
ADDIU R0, R0, $4B3D
.org 0x4924
BEQ R0, R0, $00004940