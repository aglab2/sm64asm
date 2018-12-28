; 0x2ABD28 -- star loader @16000EA0
; 170C0016 00218DA0 00219E00
; 170C0003 00AB240C 00AE5714

; 16000000 = 00218DA0
; 16000EA0 = 00219C40 - star geolayout
; 16000868 = 00219608

; 03000000 = 00AB240C
; 03014250 = 00AC665C

; dl1 = 0302B870 = 00ADDC7C = star dl
; dl2 = 0302BA18 = 00ADDE24 = eyes dl

;eyes @    0302B9C0 = ADDDCC
; FD cmd = 0302AEF0 = ADD2FC
; 04 cmd = 0302B920 = 

;star @ 0302B870 = 00ADDC7C
; FD cmd = 0302A6F0 = ADCAFC

; 04000000 = 011A35B8


; 04036A48 = 011DA000 ; texture
; 04037248 = 011DA800 ; dl
; 04037348 = 011DA900 ; geolayout

; 0403E348 = 11E1900

; star 0 11DA000 // 11DA800 dl


; models from F8 to FF
; jmp 06 08 00 00 04 03 56 40
; old 22 08 00 01 17 00 2D D4
; loader @ 04035640 = 11D8BF8; jmp 2ABCE0

; 21A618 -- 100 coin star spawn function
; 21CE2C -- star in act selector
; 21DC4C -- star regular

;AD548 -- picker for star transparent vs normal

; 79 = 1E4 = transparent star
; 7A = 1E8 = normal star
; F9 = 3E4 = normal star

.orga 0xAD57C
	JAL 0x80404200
	NOP

.orga 0x65FC4
	J 0x80403800
	NOP

.orga 0x1203800
	BEQ T6, R0, fixmodel
	NOP
	J 0x802AAFCC
	NOP
	
fixmodel:
	JAL 0x80404200
	NOP
	J 0x802AAFD4
	NOP


.orga 0x8C34
	J 0x80403900

.orga 0x1203900
	SW A1, 0x2C(SP)
	LBU T0, 0x188(A2)
	LUI T1, 0x8040
	SB T0, 0x08(T1)
	J 0x8024DC3C
	NOP

.orga 0xA80AC
	LUI T9, 0x8036
	LW T9, 0x1160(T9)
	LUI T7, 0x8040
	LB T7, 0x08(T7)
	JAL 0x80404200
	SB T7, 0x188(T9)
	

.orga 0x1204200
	LUI T8, 0x8033
	LW T8, 0xDDC4(T8)
	LUI T9, 0x8036
	LW T9, 0x1160(T9)
	
	LBU T0, 0x188(T9)
	
	ADDIU T8, T8, 0x1E8 ; default color

	SLTI T1, T0, 6
	BEQ T1, R0, end
	NOP
	
	ADDIU T8, T8, 0x1F8 ; to 0xF8 for 0
	
	SLL T0, T0, 2
	ADD T8, T8, T0
	
end:
	LW T0, 0x0(T8)
	SW T0, 0x014(T9)
	
	JR RA
	NOP

.orga 0x1203A00
	LW A2, 0x34(A2)
	LI A1, 0x79
	
	BEQ A1, A2, fs_end
	NOP

	LI A2, 0xF8
	ADDU A2, A2, T7
	
fs_end:
	J 0x80176D2C
	NOP
	
; 
.orga 0x2271E4
	J 0x80403A00