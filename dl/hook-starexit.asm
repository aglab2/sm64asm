.orga 0x8c44
    LW V1, 0x801ce0a0
    JALR V1
    NOP
    SW V0, 0x1c(SP)

.orga 0x133f8
    LW V1, 0x801ce0a4
    JALR V1
    OR A1, S0, R0
