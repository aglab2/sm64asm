.orga 0x6f58
.area 0x20, 0x00
    LUI V1, 0x8034
    LH T0, 0xB21A(V1)
    SLTI AT, T0, 150
    BNEZ AT, 0x6f84
    LI T1, 5
    SH T1, 0xbac8(V1)
    B 0x6f78
    NOP
.endarea