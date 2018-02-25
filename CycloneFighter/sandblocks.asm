;Sandblocks fix
;Change line 30 to edit time to wait, not less than 0x80

.org 0x651C0
J 0x2EF760 ;after hook

;Hook instead of ded object
.org 0x65230
J 0x2EF6F0 ;hook_aftertimer

;--------------------------------------------------------------------

.orga 0xAA6F0
.area 0x70, 0x00
BLT A0, T0, hook_aftertimer
NOP
J 0x2AA244 ;0x65244
NOP

hook_aftertimer:
;Sets hook to B to aftertimerwait
ADDIU V0, V0, 1
SW V0, 0x180(V1)
;This kills sand spawner?
LW V0, 0x17C(V1)
SH R0, 0x074(V0)

;Wait a bit before refreshing
hook_aftertimerwaiter:
SLTI AT, T0, 0x140
BNEZ AT, end ;finish 
NOP

;Set hook back to normal state
SW R0, 0x180(V1)

;Set scale back to 1
LI T0, 1.0
SW T0, 0x030(V1)

;Fix Y coordinate of object
LI T0, 304.578 ;pro constant
MTC1 T0, F0
LW T0, 0xA4(V1)
MTC1 T0, F2
SUB.S F0, F2, F0
SWC1 F0, 0xA4(V1)

;return + set state to 0
SW R0, 0x14C(V1)
end:
J 0x2AA274 ;0x65274
NOP
.endarea

.area 0x30, 0x00
;Object loader to V1
LUI V1, 0x8036
LW V1, 0x1160(V1)

;Check if object is invisible
;If so just jump to checker, no need to process shit
;We need to load timer to T0, hook believes in that
LW T0, 0x154(V1)
LW T1, 0x180(V1)
BNE T1, R0, hook_aftertimerwaiter
NOP

;If 0, just do what sandblock wants to do
JAL 0x2A3CFC
NOP
J 0x2AA1C8
NOP
.endarea