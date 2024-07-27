.orga 0x21fe44
    ADDIU SP, SP, 0xFFD8
    SW RA, 0x0014 (SP)
    SW A0, 0x0018 (SP)
    SW A1, 0x001C (SP)
    SW A2, 0x0020 (SP)
    SW A3, 0x0024 (SP)
    LUI T0, 0x3F80
    BNE T0, A1, ehd
    NOP
    LUI A0, 0x0701
    ADDIU A0, A0, 0xF150
    JAL 0x00277F50
    NOP
    LBU T0, 0x0004 (V0)
    ORI T1, R0, 0x00FA
    BEQ T0, T1, draw
    NOP
    ADDIU T0, T0, 0x000A
    SB T0, 0x0004 (V0)
    SB T0, 0x0005 (V0)
    SB T0, 0x0006 (V0)
    
draw:
    lw at, 0x80406924
    lw a0, 0x6c(sp)
    addiu a1, t0, 0
	jalr at
    addiu a0, a0, 0x18

ehd:
    LW A0, 0x0018 (SP)
    LW A1, 0x001C (SP)
    LW A2, 0x0020 (SP)
    JAL 0x00325924
    LW A3, 0x0024 (SP)
    LW RA, 0x0014 (SP)
    JR RA
    ADDIU SP, SP, 0x0028

.orga 0x21fe04
    SW T7, 0x10(T5)
.orga 0x21fe0c
    SW R0, 0x14(T8)