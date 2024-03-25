.orga 0xad584
    LW V1, 0x801ce018
    JALR V1
    NOP
    LW S0, 0x0014 (SP)
    LW S1, 0x0018 (SP)
    LW RA, 0x001C (SP)
    JR RA
    ADDIU SP, SP, 0x0020
