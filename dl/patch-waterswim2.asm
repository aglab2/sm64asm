; flutter speed target to 42
.orga 0x2cf88
    LUI AT, 0x4220 ; 42
.orga 0x2cfbc
    LI T4, 440

; unrestrict max speed to 42
.orga 0x2bcb0
    LUI AT, 0x4220 ; 42

; always show flutter anim
.orga 0x2cfe0
    nop
