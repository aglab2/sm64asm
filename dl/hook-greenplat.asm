.orga 0x1206300
    addiu sp, sp, -0x18
    sw ra, 0x14(sp)

    lw v1, 0x801ce04C
    jalr v1
    nop

    lw ra, 0x14(sp)
    jr ra
    addiu sp, sp, 0x18

.orga 0x21AB14 
    .dw 0x80406300
