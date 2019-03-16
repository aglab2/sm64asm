.orga 0x120D000
.dw 0x00080000
.dw 0x11010009
.dd 	0x0C0000008040D080
.dw 0x08000000
.dd 	0x0C0000008040D100
.dw 0x09000000

.orga 0x120D080
.area 0x80, 0x00
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	LW V1, 0x80361160
	
	JAL 0x80383BB0
	NOP
	SH V0, 0xCA(V1)
	JAL 0x80383BB0
	NOP
	LI T0, 0x133
	SH V0, 0xD2(V1)
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18
.endarea

.orga 0x120D100
.area 0x100, 0x00
	LW V1, 0x80361160

; change state on demand
	LW T0, 0x8033B1D8
	LH T9, 0x0(T0)
	
; whitelist
	BEQ T9, R0, dorotation
	NOP
	LI T0, 0x13
	BEQ T9, T0, dorotation
	NOP
	LI T0, 0xA
	BEQ T9, T0, dorotation
	NOP

; setstate
; state != 0 fly to 0,0,0
	LI T1, 1
	LB T0, 0x188(V1)
	BEQ T0, T9, dorotation
	SW T1, 0x14C(V1)
	LB T0, 0x189(V1)
	BEQ T0, T9, dorotation
	NOP
	
; reset to 0, just fly around xd
	SW R0, 0x14C(V1)
	
dorotation:
	LW T9, 0x14C(V1)
	LHU T8, 0xCA(V1)
	LHU T7, 0xD2(V1)
	BEQZ T9, flyxd
	NOP
	
moveto0:
	LB T0, 0x18A(V1)
	BEQ T0, R0, normal
	NOP
	
fast:
	SUBI T7, T7, 0x2000
	B moveto0end
	SUBI T8, T8, 0x2000

normal:
	SUBI T7, T7, 0x900
	SUBI T8, T8, 0x900

moveto0end:
	BGE T7, R0, noclamp1
	NOP
	ADD T7, R0, R0
noclamp1:
	BGE T8, R0, noclamp2
	NOP
	ADD T8, R0, R0
noclamp2:

	B end
	NOP

flyxd:
	LB T0, 0x18B(V1)
	LI T1, 0x40
	MULT T0, T1
	MFLO T3

	ADD T7, T3
	ADD T8, T3
	
end:
	SH T8, 0xCA(V1)
	SH T7, 0xD2(V1)
	
	JR RA
	NOP
.endarea