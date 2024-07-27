.orga 0x21fe44
    ADDIU SP, SP, -0x18
    SW RA, 0x0014 (SP)

    lw at, 0x8040A124
	jalr at
	nop

    LW RA, 0x0014 (SP)
    JR RA
    ADDIU SP, SP, 0x0018

.orga 0x21fe04
    SW T7, 0x0(T5)
.orga 0x21fe0c
    SW R0, 0x4(T8)
