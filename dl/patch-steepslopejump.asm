.orga 0xce58
    LI V1, 0x15
    LW T6, 0x30(SP)
    LW T7, 0x68(T6)

.orga 0xce6c
    LHU V0, 0x0(T7)
    LI AT, 0x13
    BEQ S0, AT, 0xce84

.orga 0xced4
    BEQ V0, V1, 0xcefc
    OR T8, R0, R0
    LWC1 F18, 0x2c (SP)
