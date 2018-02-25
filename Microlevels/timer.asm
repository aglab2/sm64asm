;set timer for timer code
;overwritten 1st function in bowsey behaviour

;bparam1: seconds before ded

;overwritten moneybag, rip moneybag
.orga 0x21D7D4 ;behav 0x130039D4
.dw  0x00040000
.dd  0x0C000000802B7878
.dw  0x08000000
.dd  0x0C000000802EE8F4
.dw  0x09000000

.orga 0x72878
.area 0x30

LUI V1, 0x8036
LW V1, 0x1160(V1)

LB T0, 0x188(V1)
ADDIU T1, T1, 30

MULT T0, T1
MFLO T0

ADD AT, R0, T0
LUI T2, 0x8037
SH AT, 0x6E(T2)

JR RA
NOP
.endarea