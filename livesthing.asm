;this spawn 1up on coins star that is required for 100
;8024BEC8 -- puts 0 to B218
;8024BED0 -- puts 0 to B262

; We know that T6 is 8033B218 - A8 = 8033B170

; Don't set coin count to 0
.orga 0x6EC8
NOP
NOP
NOP

; Always do coin stuff
.orga 0x6E54
ADDIU T9, T9, 1

; Don't neglect levels
.orga 0x8B88
NOP
NOP
NOP
NOP

.orga 0x8BC8
J 0x80310518
NOP

.orga 0xCB518
.area 0x30
;8033B1F8 - maro object
;8033B218 - coins

LW A0, 0x88(T6)
ADDIU A1, R0, 212
LUI A2, 0x1300
JAL 0x8029EDCC
ADDIU A2, A2, 0x4148

LUI V1, 0x8034
SH R0, 0xB218(V1)
SH R0, 0xB262(V1)

J 0x8024DBD0
NOP
.endarea