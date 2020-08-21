.orga 0x21DD44 ;13003F44
.dw 0x00090000
.dw 0x0E437FFF
.dd 0x2A0000000E123078
.dd 0x0C000000802F346C
.dw 0x08000000
.dd 0x0C000000802F356C
.dd 0x0C000000803839CC
.dw 0x09000000

.orga 0xAE46C  ;2F346C
.area 0x100
	LUI T9, 0x8034
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	LB T0, 0x188(V1)
	BEQ T0, R0, nox
	LI T1, 24.0
	SW T1, 0x0AC(V1)
nox:
	
	LB T0, 0x189(V1)
	BEQ T0, R0, noy
	NOP
	LB T0, 0x188(V1)
	BEQ T0, R0, yplus
	NOP
yminus:
	B yset
	LI T1, -19.0
yplus:
	LI T1, 19.0
yset:
	SW T1, 0x0B4(V1)
noy:

	JR RA
	NOP
.endarea

.orga 0xAE56C  ;2F356C
.area 0x240
	LUI T9, 0x8034
	
	LUI V1, 0x8036
	LW V1, 0x1160(V1)
	
	;Perform move
	LWC1 F0, 0x0A0(V1)
	LWC1 F2, 0x0AC(V1)
	add.s F0, F0, F2
	SWC1 F0, 0x0A0(V1)
	
	LWC1 F0, 0x0A8(V1)
	LWC1 F2, 0x0B4(V1)
	add.s F0, F0, F2
	SWC1 F0, 0x0A8(V1)
	
	;Get frame count on each 32 change direction
	LW T0, 0x154(V1)
	ANDI T0, T0, 127
	BNE T0, R0, end
	NOP
	
	;switch directions
	LW T0, 0x0AC(V1)
	MTC1 T0, F0
	neg.s F0, F0
	MFC1 T0, F0
	SW T0, 0x0AC(V1)
	
	LW T0, 0x0B4(V1)
	MTC1 T0, F0
	neg.s F0, F0
	MFC1 T0, F0
	SW T0, 0x0B4(V1)
	
end:
	JR RA
	NOP
.endarea