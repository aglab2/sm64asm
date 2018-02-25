;Shrinking platforms fix
;Change line 18 to edit time to wait, not less than 0x80

;Hook instead of ded object
.org 0x658AC
B hook_aftertimer

;Hook instead of object spawn
.org 0x65850
B hook_objectspawn

;--------------------------------------------------------------------

.orga 0x658EC
.area 0x38, 0x00
hook_aftertimer:
;Wait a bit before refreshing
SLTI AT, T0, 0x100
BNEZ AT, 0x658E0 ;finish 
NOP

;set damage to 1, just a hack not to spawn object twice
ADDIU T0, R0, 1
SW T0, 0x180(V1)

;set scale back to 1
LI AT, 1.0
JAL 0x29F430
MTC1 AT, F12

;return + set state to 0
B 0x658E0
SW R0, 0x14C(V1)
.endarea

;Hack not to spawn extra objects
.area 0x20, 0x00
hook_objectspawn:
BNEZ T0, 0x6586C
LW T9, 0x180(V1)
BNEZ T9, 0x6586C
NOP
B 0x65858
NOP
.endarea