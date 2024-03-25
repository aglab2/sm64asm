.orga 0x34c8c
    lui v1, 0x8040
    sw t7, 0x51d0(v1)

.orga 0x9823c
    LW V1, 0x801ce030
    JALR V1
    NOP
    BEQ V0, R0, 0x98824
    NOP
