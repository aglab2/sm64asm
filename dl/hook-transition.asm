.orga 0x361b8
    LW V1, 0x801ce05c
    ADDIU A1, SP, 0x23
    ADDIU A2, SP, 0x27
    JALR V1
    ADDIU A3, SP, 0x2B

.orga 0x37968
    LW V1, 0x801ce060
    LW T3, 0x40(SP)
    LW A0, 0x28(SP)
    JALR V1
    LHU A1, 0x1C(T3)
    NOP

.orga 0x2276d8
    ADDIU T9, R0, 0xffff
.orga 0x22779c
    ADDIU T5, R0, 0xffff
.orga 0x22789c
    ADDIU T2, R0, 0xffff
