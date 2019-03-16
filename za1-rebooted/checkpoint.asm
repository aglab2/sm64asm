;8027a69C - sets 0 function
;*(8033BAC8) -> 8033B4A0 = Act Number
;*(8033BAC6) -> 8033B4A1 = Course Number // current stage? make warp dependant
;*(A0+1) -> 8033B4A2 = Level ID
;*(A0+2) -> 8033B4A3 = Area # to warp to
;*(A0+3) -> 8033B4A4 = Warp ID to warp to

; allow between levels checkpoints
.orga 0x6F28
	NOP

; do not check acts
.orga 0x3576C
	NOP
	
.orga 0x356C0
.area 0x48, 0x00
	LUI T9, 0x8034
	
	; act
	LH T0, 0xBAC8(T9)
	BNE T0, R0, goodact
	NOP
	LI T0, 1
goodact:
	SB T0, 0xB4A0(T9)
	
	; warp level id
	LBU T0, 0x1(A0)
	ANDI T1, T0, 0x7F
	SB T1, 0xB4A2(T9)

	; warp area id
	LBU T0, 0x2(A0)
	SB T0, 0xB4A3(T9)
	
	; warp id
	LBU T0, 0x3(A0)
	SB T0, 0xB4A4(T9)
	
	; level corresponding to warp
	LUI T8, 0x8041
	ADD T8, T8, T1
	LBU T1, 0xE800(T8)
	SB T1, 0xB4A1(T9)
.endarea

;warp tables at 0x120E800
.orga 0x120E800
.area 0x80, 0x00
.endarea

.orga 0x120E809
.db 0x01
.orga 0x120E818
.db 0x02
.orga 0x120E80C
.db 0x03
.orga 0x120E805
.db 0x04
.orga 0x120E804
.db 0x05
.orga 0x120E807
.db 0x06
.orga 0x120E816
.db 0x07
.orga 0x120E808
.db 0x08
.orga 0x120E817
.db 0x09
.orga 0x120E80A
.db 0x0A
.orga 0x120E80B
.db 0x0B
.orga 0x120E824
.db 0x0C
.orga 0x120E80D
.db 0x0D
.orga 0x120E80E
.db 0x0E
.orga 0x120E80F
.db 0x0F
.orga 0x120E811
.db 0x10
.orga 0x120E813
.db 0x11
.orga 0x120E815
.db 0x12
.orga 0x120E81B
.db 0x13
.orga 0x120E81C
.db 0x14
.orga 0x120E81D
.db 0x15
.orga 0x120E812
.db 0x16
.orga 0x120E81F
.db 0x17
.orga 0x120E818
.db 0x18