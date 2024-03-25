.orga 0x10cc4
    LW V1, 0x801ce034
    LW A1, 0x30(SP)
    JALR V1
    LW A0, 0x40(SP)
    NOP

.orga 0x5a04
    lw v1, 0x801ce03c
    lw a0, 0x30(sp)
    jalr v1
    addiu a1, sp, 0x34

.orga 0x359C8
    addiu sp, sp, -0x18
    sw ra, 0x14(sp)

    lw v1, 0x801ce038
    jalr v1
    NOP

    lw ra, 0x14(sp)
    jr ra
    addiu sp, sp, 0x18
