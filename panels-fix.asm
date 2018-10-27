.orga 0x632D0
    LUI A0, 0x1300
    JAL 0x80277F50
    ORI A0, A0, 0x05D8

objects_loop:
    LUI T1, 0x8036
    ORI T1, T1, 0x0E88
    LW V1, 0x18(SP)
    BEQ T1, V1, 0x63314

    LW T2, 0x20C(V1)
    BNE T2, V0, wrong_object
    NOP
	
	LW T4, 0x0F0(V1)

.orga 0x63304
wrong_object:
    ADDIU V1, V1, 0x260
    SW V1, 0x18(SP)
    B objects_loop
    NOP


.orga 0x63CE8
    NOP
    NOP
    BNE T2, V0, 0x63D04
