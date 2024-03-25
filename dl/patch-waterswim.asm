; break watershell
.orga 0x2d9cc
    B 0x2da34
    NOP

.orga 0x2f8f8
    B 0x2f92C
    NOP

; water shell allows jumping from water and checks for A presses
.orga 0x2d5bc
.area 0x58, 0x00
    JAL 0x8027197c ; check_water_jump
    LW A0, 0x28(SP) ; m
    BNEZ V0, 0x2d668
    
    LW A0, 0x28(SP) ; m
    LH T0, 0x2(A0)
    ANDI T1, T0, 0x28
    BEQ T1, R0, @@notimerreset
    LHU T2, 0x1A(A0)
    LI T2, 0
@@notimerreset:
    ADDIU T2, T2, 1
    SH T2, 0x1A(A0)

    SLTI AT, T2, 30
    BNEZ AT, @@nodropswim
    LI A0, 0
    LI A1, 0x300024D2
    JAL 0x80252cf4
    LI A2, 0
@@nodropswim:
.endarea