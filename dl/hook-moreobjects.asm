.orga 0x5e2cc
    SLTI AT, T8, 0x97 + 100
.orga 0x5e2f8
    SLTI AT, T1, 0xd3 + 100
.orga 0x6b780
    SLTI AT, T1, 0xd5 + 100

.orga 0x5827c
    LW V1, 0x801ce070
    JALR V1
    NOP
    B 0x582e0
    NOP

.orga 0x849B8
    ADDIU SP, SP, -0x18
    SW RA, 0x14(SP)

    LW V1, 0x801ce074
    JALR V1
    NOP

    LW RA, 0x14(SP)
    JR RA
    ADDIU SP, SP, 0x18
