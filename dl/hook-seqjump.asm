.orga 0xD8DD4
    JAL 0x80406000

.orga 0x1206000
    ADDIU SP, SP, -0x28
    SW RA, 0x14(SP)

    LW V1, 0x801ce098
    JALR V1
    SW A0, 0x18(SP)

    JAL 0x8031C050
    LW A0, 0x18(SP)

    LW RA, 0x14(SP)
    JR RA
    ADDIU SP, SP, 0x28

    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

.orga 0xcfea4
    JAL 0x80406080

.orga 0x1206080
    ADDIU SP, SP, -0x18
    SW RA, 0x14(SP)

    JAL 0x31e240
    NOP

    LW V1, 0x801ce09c
    JALR V1
    NOP

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
    NOP
