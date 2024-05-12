.orga 0x7F8C8
    ; obj_set_secondary_camera_focus
    JAL 0x2c53cc
    NOP
    LUI A0, 0x1300
    JAL 0x8029f95c ; find object with ghost hunt boo behav
    ADDIU A0, A0, 0x2804
    NOP

    LW T8, 0x80361160
    ; if there are still ghost hunt boos, bail
    BNE V0, R0, 0x7f9c0
    SW R0, 0x108(T8)
    ; set amount of boos collected to large count so it will be always spawned
    LI T0, 10
    SW T0, 0x1ac(T8)
    NOP
    NOP
    JAL 0x2c3534