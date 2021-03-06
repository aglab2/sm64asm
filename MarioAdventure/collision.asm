//subroutine of 80381794/80381900, finds the collision triangle below on Y axis.
//is about 30% faster than old one, will significantly remove lag in high poly levels
.org 0xFE2FC
asfstart:
LW T0, 0x0004 (A0)
LW A0, 0x0000 (A0)
LH T1, 0x000A (T0)
LH T2, 0x000E (T0)
LH T3, 0x0010 (T0)
LH T4, 0x0014 (T0)
SUBU T6, T2, A3
SUBU T7, T3, T1
MULTU T6, T7
MFLO T8
SUBU T6, T4, T2
SUBU T9, T1, A1
MULTU T9, T6
MFLO T7
SUBU T9, T8, T7
BGEZ T9, asfpass1
nop
BEQ R0, R0, asfend
NOP
asfpass1:
LH T5, 0x0016 (T0)
LH T6, 0x001A (T0)
SW T6, 0x001C (SP)
SUBU T8, T4, A3
SUBU T7, T5, T3
MULTU T8, T7
MFLO T9
LW T8, 0x001C (SP)
SUBU T6, T3, A1
SUBU T7, T8, T4
MULTU T6, T7
MFLO T8
SUBU T6, T9, T8
BGEZ T6, asfpass2
nop
BEQ R0, R0, asfend
NOP
asfpass2:
LW T7, 0x001C (SP)
SUBU T8, T1, T5
SUBU T9, T7, A3
MULTU T9, T8
MFLO T6
SUBU T9, T5, A1
SUBU T8, T2, T7
MULTU T9, T8
MFLO T7
SUBU T9, T6, T7
BGEZ T9, asfpass3
NOP
BEQ R0, R0, asfend
NOP
asfpass3:
LUI T8, 0x8036
LH T8, 0x1180 (T8)
BEQ T8, R0, asfcheck2
NOP
LB T6, 0x0004 (T0)
ANDI T7, T6, 0x0002
BEQ T7, R0, asfpass4
NOP
BEQ R0, R0, asfend
NOP
BEQ R0, R0, asfpass4
NOP
asfcheck2:
LH T9, 0x0000 (T0)
ADDIU AT, R0, 0x0072
BNE T9, AT, asfpass4
NOP
BEQ R0, R0, asfend
NOP
asfpass4:
LWC1 F4, 0x001C (T0)
SWC1 F4, 0x0018 (SP)
LWC1 F6, 0x0020 (T0)
SWC1 F6, 0x0014 (SP)
LWC1 F8, 0x0024 (T0)
SWC1 F8, 0x0010 (SP)
LWC1 F10, 0x0028 (T0)
SWC1 F10, 0x000C (SP)
LWC1 F16, 0x0014 (SP)
MTC1 R0, F18
NOP
C.EQ.S F16, F18
NOP
BC1F asfpass5
NOP
BEQ R0, R0, asfend
NOP
asfpass5:
MTC1 A1, F4
MTC1 A3, F18
LWC1 F8, 0x0018 (SP)
CVT.S.W F6, F4
LWC1 F16, 0x0010 (SP)
CVT.S.W F4, F18
MUL.S F10, F6, F8
LWC1 F18, 0x000C (SP)
MUL.S F6, F16, F4
ADD.S F8, F10, F6
LWC1 F10, 0x0014 (SP)
ADD.S F16, F8, F18
NEG.S F4, F16
DIV.S F6, F4, F10
ADD.S F6, F6, F6
ADD.S F6, F6, F6
SWC1 F6, 0x0008 (SP)
MTC1 A2, F4
LUI AT, 0xC29C
MTC1 AT, F18
LWC1 F8, 0x0008 (SP)
CVT.S.W F10, F4
ADD.S F16, F8, F18
MTC1 R0, F8
SUB.S F6, F10, F16
C.LT.S F6, F8
BC1F asfpass6
NOP
BEQ R0, R0, asfend
asfpass6:
LWC1 F18, 0x0008 (SP)
LW T8, 0x0048 (SP)
SWC1 F18, 0x0000 (T8)
SW T0, 0x0004 (SP)

BEQ R0, R0, asfskip
nop
asfend:
BNE A0, r0, asfstart
nop
nop
nop
nop
nop
nop
nop
nop
nop
asfskip:
lw v0, 0x0004 (SP)
jr ra
addiu sp, sp, 0x0038

.org 0x100394
ADDIU SP, SP, 0xFF60
SW RA, 0x003C (SP)
SW A0, 0x00A0 (SP)
SW A1, 0x00A4 (SP)
SW S2, 0x0038 (SP)
SW S1, 0x0034 (SP)
SW S0, 0x0030 (SP)
SDC1 F24, 0x0028 (SP)
SDC1 F22, 0x0020 (SP)
SDC1 F20, 0x0018 (SP)
LUI T6, 0x8036
LW T6, 0x1160 (T6)
ADDIU T7, T6, 0x021C
SW T7, 0x0088 (SP)
LW T8, 0x00A0 (SP)
LW T9, 0x0000 (T8)
LH S1, 0x0000 (T9)
LW T0, 0x00A0 (SP)
LW T1, 0x0000 (T0)
ADDIU T2, T1, 0x0002
SW T2, 0x0000 (T0)
LW T3, 0x00A0 (SP)
LW S0, 0x0000 (T3)
LUI T4, 0x8036
LW T4, 0x1160 (T4)
LW T5, 0x0050 (T4)
BNE r0,T5, ajump
NOP
LUI T7, 0x8036
LW T7, 0x1160 (T7)
LW T6, 0x0088 (SP)
SW T6, 0x0050 (T7)
LUI A0, 0x8036
LW A0, 0x1160 (A0)
ADDIU A1, R0, 0x0006
JAL 0x802A2930
ADDIU A2, R0, 0x0012
ajump:
LUI A0, 0x8036
LW A0, 0x1160 (A0)
ADDIU A1, SP, 0x0048
JAL 0x8029DDA8
LW A2, 0x0088 (SP)
OR S2, S1, R0
BEQ S2, R0, end
ADDIU S1, S1, 0xFFFF
loop:
LH T8, 0x0000 (S0)
MTC1 T8, F4
NOP
CVT.S.W F20, F4
LH T9, 0x0002 (S0)
MTC1 T9, F6
NOP
CVT.S.W F22, F6
LH T1, 0x0004 (S0)
ADDIU S0, S0, 0x0006
MTC1 T1, F8
NOP
CVT.S.W F24, F8
ADDIU T2, SP, 0x0048
LWC1 F10, 0x0000 (T2)
LWC1 F18, 0x0010 (T2)
LWC1 F8, 0x0020 (T2)
MUL.S F16, F20, F10
LW T4, 0x00A4 (SP)
MUL.S F4, F22, F18
ADD.S F6, F16, F4
MUL.S F10, F24, F8
LWC1 F16, 0x0030 (T2)
ADD.S F18, F6, F10
ADD.S F4, F16, F18
TRUNC.W.S F8, F4
MFC1 T3, F8
NOP
SH T3, 0x0000 (T4)
LW T5, 0x00A4 (SP)
ADDIU T6, T5, 0x0002
SW T6, 0x00A4 (SP)
ADDIU T7, SP, 0x0048
LWC1 F6, 0x0004 (T7)
LWC1 F16, 0x0014 (T7)
LWC1 F8, 0x0024 (T7)
MUL.S F10, F20, F6
LW T1, 0x00A4 (SP)
MUL.S F18, F22, F16
ADD.S F4, F10, F18
MUL.S F6, F24, F8
LWC1 F10, 0x0034 (T7)
ADD.S F16, F4, F6
ADD.S F18, F10, F16
TRUNC.W.S F8, F18
MFC1 T9, F8
NOP
SH T9, 0x0000 (T1)
LW T2, 0x00A4 (SP)
ADDIU T0, T2, 0x0002
SW T0, 0x00A4 (SP)
ADDIU T3, SP, 0x0048
LWC1 F4, 0x0008 (T3)
LWC1 F10, 0x0018 (T3)
LWC1 F8, 0x0028 (T3)
MUL.S F6, F20, F4
LW T6, 0x00A4 (SP)
MUL.S F16, F22, F10
ADD.S F18, F6, F16
MUL.S F4, F24, F8
LWC1 F6, 0x0038 (T3)
ADD.S F10, F18, F4
ADD.S F16, F6, F10
TRUNC.W.S F8, F16
MFC1 T5, F8
NOP
SH T5, 0x0000 (T6)
LW T7, 0x00A4 (SP)
ADDIU T8, T7, 0x0002
SW T8, 0x00A4 (SP)
OR S2, S1, R0
BNE r0, S2, loop
ADDIU S1, S1, 0xFFFF
end:
LW T9, 0x00A0 (SP)
SW S0, 0x0000 (T9)
LW RA, 0x003C (SP)
LDC1 F20, 0x0018 (SP)
LDC1 F22, 0x0020 (SP)
LDC1 F24, 0x0028 (SP)
LW S0, 0x0030 (SP)
LW S1, 0x0034 (SP)
LW S2, 0x0038 (SP)
JR RA
ADDIU SP, SP, 0x00A0

//80383a94
//rewrite loop in 80383614 and 80383828

.org 0x100394
ADDIU SP, SP, 0xFF60
SW RA, 0x003C (SP)
SW A0, 0x00A0 (SP)
SW A1, 0x00A4 (SP)
SW S2, 0x0038 (SP)
SW S1, 0x0034 (SP)
SW S0, 0x0030 (SP)
SDC1 F24, 0x0028 (SP)
SDC1 F22, 0x0020 (SP)
SDC1 F20, 0x0018 (SP)
LUI T6, 0x8036
LW T6, 0x1160 (T6)
ADDIU T7, T6, 0x021C
SW T7, 0x0088 (SP)
LW T8, 0x00A0 (SP)
LW T9, 0x0000 (T8)
LH S1, 0x0000 (T9)
LW T0, 0x00A0 (SP)
LW T1, 0x0000 (T0)
ADDIU T2, T1, 0x0002
SW T2, 0x0000 (T0)
LW T3, 0x00A0 (SP)
LW S0, 0x0000 (T3)
LUI T4, 0x8036
LW T4, 0x1160 (T4)
LW T5, 0x0050 (T4)
BNE r0,T5, bjump
NOP
LUI T7, 0x8036
LW T7, 0x1160 (T7)
LW T6, 0x0088 (SP)
SW T6, 0x0050 (T7)
LUI A0, 0x8036
LW A0, 0x1160 (A0)
ADDIU A1, R0, 0x0006
JAL 0x802A2930
ADDIU A2, R0, 0x0012
bjump:
LUI A0, 0x8036
LW A0, 0x1160 (A0)
ADDIU A1, SP, 0x0048
JAL 0x8029DDA8
LW A2, 0x0088 (SP)
OR S2, S1, R0
BEQ S2, R0, uend
ADDIU S1, S1, 0xFFFF
sloop:
LH T8, 0x0000 (S0)
MTC1 T8, F4
LH T9, 0x0002 (S0)
CVT.S.W F20, F4
MTC1 T9, F6
LH T1, 0x0004 (S0)
CVT.S.W F22, F6
ADDIU S0, S0, 0x0006
MTC1 T1, F8
NOP
CVT.S.W F24, F8
LWC1 F10, 0x0048 (sp)
LWC1 F18, 0x0058 (sp)
LWC1 F8, 0x0068 (sp)
MUL.S F16, F20, F10
LW A0, 0x00A4 (SP)
MUL.S F4, F22, F18
ADD.S F6, F16, F4
MUL.S F10, F24, F8
LWC1 F16, 0x0078 (sp)
ADD.S F18, F6, F10
ADD.S F4, F16, F18
TRUNC.W.S F8, F4
MFC1 T3, F8
ADDIU T6, a0, 0x0002
SH T3, 0x0000 (a0)
SW T6, 0x00A4 (SP)
LWC1 F6, 0x004c (sp)
LWC1 F16, 0x005c (sp)
LWC1 F8, 0x006c (sp)
MUL.S F10, F20, F6
MUL.S F18, F22, F16
ADD.S F4, F10, F18
MUL.S F6, F24, F8
LWC1 F10, 0x007c (sp)
ADD.S F16, F4, F6
ADD.S F18, F10, F16
TRUNC.W.S F8, F18
MFC1 T9, F8
ADDIU T0, T6, 0x0002
SH T9, 0x0000 (t6)
SW T0, 0x00A4 (SP)
LWC1 F4, 0x0050 (sp)
LWC1 F10, 0x0060 (sp)
LWC1 F8, 0x0070 (sp)
MUL.S F6, F20, F4
MUL.S F16, F22, F10
ADD.S F18, F6, F16
MUL.S F4, F24, F8
LWC1 F6, 0x0080 (sp)
ADD.S F10, F18, F4
ADD.S F16, F6, F10
TRUNC.W.S F8, F16
MFC1 T5, F8
ADDIU T8, t0, 0x0002
SH T5, 0x0000 (t0)
SW T8, 0x00A4 (SP)
OR S2, S1, R0
BNE r0, S2, sloop
ADDIU S1, S1, 0xFFFF
uend:
LW T9, 0x00A0 (SP)
SW S0, 0x0000 (T9)
LW RA, 0x003C (SP)
LDC1 F20, 0x0018 (SP)
LDC1 F22, 0x0020 (SP)
LDC1 F24, 0x0028 (SP)
LW S0, 0x0030 (SP)
LW S1, 0x0034 (SP)
LW S2, 0x0038 (SP)
JR RA
ADDIU SP, SP, 0x00A0

.org 0x1005A8
main:
ADDIU SP, SP, 0xFFD0
SW RA, 0x0014 (SP)
SW A0, 0x0030 (SP)
SW A1, 0x0034 (SP)
LW T6, 0x0030 (SP)
LW T7, 0x0000 (T6)
LH T8, 0x0000 (T7)
SW T8, 0x002C (SP)
LW T9, 0x0030 (SP)
LW T0, 0x0000 (T9)
ADDIU T1, T0, 0x0002
SW T1, 0x0000 (T9)
LW T2, 0x0030 (SP)
LW T3, 0x0000 (T2)
LH T4, 0x0000 (T3)
SW T4, 0x0024 (SP)
LW T5, 0x0030 (SP)
LW T6, 0x0000 (T5)
ADDIU T7, T6, 0x0002
SW T7, 0x0000 (T5)
JAL 0x80382F84
LW A0, 0x002C (SP)
SH V0, 0x0022 (SP)
JAL 0x80382FEC
LW A0, 0x002C (SP)
SH V0, 0x0020 (SP)
LH T8, 0x0020 (SP)
ORI T0, T8, 0x0001
SH T0, 0x0020 (SP)
LUI A0, 0x1300
JAL 0x80277F50
ADDIU A0, A0, 0x1C34
LUI T1, 0x8036
LW T1, 0x1160 (T1)
LW T9, 0x020C (T1)
BNE V0, T9, notbehavior
NOP
ADDIU T2, R0, 0x0005
BEQ R0, R0, prepareloop
SH T2, 0x001E (SP)
notbehavior:
SH R0, 0x001E (SP)
prepareloop:
LW T3, 0x0024 (SP)
SW R0, 0x0028 (SP)
BLEZ T3, aend
NOP
qloop:
LW A0, 0x0034 (SP)
JAL 0x80382B7C
LW A1, 0x0030 (SP)
SW V0, 0x0018 (SP)
BEQ v0, R0, skiplabelone
NOP
LUI T6, 0x8036
LW T6, 0x1160 (T6)
SW T6, 0x002C (v0)
LW T5, 0x002C (SP)
SH T5, 0x0000 (v0)
LH T0, 0x0022 (SP)
BEQ T0, R0, skiplabeltwo
NOP
LW T1, 0x0030 (SP)
LW T9, 0x0000 (T1)
LH T2, 0x0006 (T9)
BEQ R0, R0, combine
SH T2, 0x0002 (v0)
skiplabeltwo:
SH R0, 0x0002 (v0)
combine:
LH T5, 0x0020 (SP)
LB T7, 0x0004 (v0)
OR T8, T7, T5
SB T8, 0x0004 (v0)
LH T0, 0x001E (SP)
SB T0, 0x0005 (v0)
LW A0, 0x0018 (SP)
JAL 0x80382A2C
ADDIU A1, R0, 0x0001
skiplabelone:
LH t9, 0x0022 (SP)
BEQ T9, R0, skiplabelthree
NOP
LW T2, 0x0030 (SP)
LW T3, 0x0000 (T2)
ADDIU T4, T3, 0x0008
BEQ R0, R0, loopcounter
SW T4, 0x0000 (T2)
skiplabelthree:
LW T7, 0x0030 (SP)
LW T5, 0x0000 (T7)
ADDIU T8, T5, 0x0006
SW T8, 0x0000 (T7)
loopcounter:
LW T6, 0x0028 (SP)
LW T1, 0x0024 (SP)
ADDIU T0, T6, 0x0001
SLT AT, T0, T1
BNEZ AT, qloop
SW T0, 0x0028 (SP)
aend:
LW RA, 0x0014 (SP)
JR RA
ADDIU SP, SP, 0x0030




.org 0xFF8FC
subcall:
ADDIU SP, SP, 0xFF80
SW RA, 0x0034 (SP)
SW A0, 0x0080 (SP)
SW A1, 0x0084 (SP)
SW S7, 0x0030 (SP)
SW S6, 0x002C (SP)
SW S5, 0x0028 (SP)
SW S4, 0x0024 (SP)
SW S3, 0x0020 (SP)
SW S2, 0x001C (SP)
SW S1, 0x0018 (SP)
SW S0, 0x0014 (SP)
//shortenalot
LW T7, 0x0000 (a1)
LH T8, 0x0000 (T7)
SLL T9, T8, 0x2
SUBU T9, T9, T8
SH T9, 0x003E (SP)
LH T2, 0x0002 (T7)
SLL T3, T2, 0x2
SUBU T3, T3, T2
SH T3, 0x003C (SP)
LH T6, 0x0004 (T7)
SLL T0, T6, 0x2
SUBU T0, T0, T6
SH T0, 0x003A (SP)
LH t9, 0x003E (SP)
SLL t0, T9, 0x1
ADDU T1, a0, T0
LH S0, 0x0000 (T1)
LH S1, 0x0002 (T1)
LH S2, 0x0004 (T1)
LH T1, 0x003C (SP)
SLL T3, T1, 0x1
ADDU T2, a0, T3
LH S3, 0x0000 (T2)
LH S4, 0x0002 (T2)
LH S5, 0x0004 (T2)
LH T2, 0x003A (SP)
SLL T5, T2, 0x1
ADDU T4, a0, T5
LH S6, 0x0000 (T4)
LH S7, 0x0002 (T4)
LH T5, 0x0004 (T4)
//back to regular
SRA S0, S0, 0x2
SRA S1, S1, 0x2
SRA S2, S2, 0x2
SRA S3, S3, 0x2
SRA S4, S4, 0x2
SRA S5, S5, 0x2
SRA S6, S6, 0x2
SRA S7, S7, 0x2
SRA T5, T5, 0x2
SW T5, 0x0058 (SP)
SUBU T4, S4, S1
SUBU T9, S5, S2
SUBU T7, T5, S5
MULTU T4, T7
MFLO T8
SUBU T3, S5, S2
SUBU T0, S7, S4
MULTU T9, T0
MFLO T1
SUBU T2, T8, T1
MTC1 T2, F4
CVT.S.W F6, F4
SWC1 F6, 0x004C (SP)
SUBU T5, S6, S3
MULTU T3, T5
LW T7, 0x0058 (SP)
SUBU T4, S3, S0
SUBU T9, T7, S5
MFLO T6
SUBU T1, S3, S0
SUBU T2, S7, S4
MULTU T4, T9
MFLO T0
SUBU T8, T6, T0
MTC1 T8, F8
CVT.S.W F10, F8
SWC1 F10, 0x0048 (SP)
MULTU T1, T2
MFLO T3
SUBU T5, S4, S1
SUBU T7, S6, S3
MULTU T5, T7
MFLO T4
SUBU T9, T3, T4
MTC1 T9, F16
CVT.S.W F18, F16
SWC1 F18, 0x0044 (SP)
LWC1 F4, 0x004C (SP)
LWC1 F8, 0x0048 (SP)
LWC1 F18, 0x0044 (SP)
MUL.S F6, F4, F4
MUL.S F10, F8, F8
ADD.S F16, F6, F10
MUL.S F4, F18, F18
JAL 0x80323A50
ADD.S F12, F16, F4
SWC1 F0, 0x0040 (SP)
SW S1, 0x0050 (SP)
LW T6, 0x0050 (SP)
SLT AT, S4, T6
BEQ AT, R0, f80382DACskip
NOP
SW S4, 0x0050 (SP)
f80382DACskip:
LW T0, 0x0050 (SP)
SLT AT, S7, T0
BEQ AT, R0, f80382DC0skip
NOP
SW S7, 0x0050 (SP)
f80382DC0skip:
SW S1, 0x0054 (SP)
LW T8, 0x0054 (SP)
SLT AT, T8, S4
BEQ AT, R0, f80382DD8skip
NOP
SW S4, 0x0054 (SP)
f80382DD8skip:
LW T1, 0x0054 (SP)
SLT AT, T1, S7
BEQ AT, R0, f80382DECskip
NOP
SW S7, 0x0054 (SP)
f80382DECskip:
LWC1 F8, 0x0040 (SP)
LUI AT, 0x8039
LDC1 F10, 0xBBD0 (AT)
CVT.D.S F6, F8
C.LT.D F6, F10
NOP
BC1t endthisstupidshit
OR V0, R0, R0
LUI AT, 0x3FF0
MTC1 AT, F19
MTC1 R0, F18
CVT.D.S F4, F8
DIV.D F8, F18, F4
CVT.S.D F6, F8
SWC1 F6, 0x0040 (SP)
LWC1 F10, 0x004C (SP)
MUL.S F18, F10, F6
SWC1 F18, 0x004C (SP)
LWC1 F4, 0x0048 (SP)
MUL.S F12, F4, F6
SWC1 F12, 0x0048 (SP)
LWC1 F10, 0x0044 (SP)
MUL.S F18, F10, F6
JAL 0x803824F8
SWC1 F18, 0x0044 (SP)
SW V0, 0x007C (SP)
SH S0, 0x000A (v0)
SH S3, 0x0010 (v0)
SH S6, 0x0016 (v0)
SH S1, 0x000C (v0)
SH S4, 0x0012 (v0)
SH S7, 0x0018 (v0)
SH S2, 0x000E (v0)
SH S5, 0x0014 (v0)
LW T8, 0x0058 (SP)
SH T8, 0x001A (v0)
LWC1 F4, 0x004C (SP)
SWC1 F4, 0x001C (v0)
LWC1 F8, 0x0048 (SP)
SWC1 F8, 0x0020 (v0)
LWC1 F6, 0x0044 (SP)
SWC1 F6, 0x0024 (v0)
MTC1 S0, F10
MTC1 S1, F6
LWC1 F18, 0x004C (SP)
CVT.S.W F16, F10
LWC1 F8, 0x0048 (SP)
CVT.S.W F10, F6
MUL.S F4, F16, F18
LWC1 F6, 0x0044 (SP)
MUL.S F16, F8, F10
MTC1 S2, F8
CVT.S.W F10, F8
ADD.S F18, F4, F16
MUL.S F4, F6, F10
ADD.S F16, F18, F4
NEG.S F8, F16
SWC1 F8, 0x0028 (v0)
LW T4, 0x0050 (SP)
ADDIU T9, T4, 0xFFFB
SH T9, 0x0006 (v0)
LW T0, 0x0054 (SP)
ADDIU T8, T0, 0x0005
SH T8, 0x0008 (v0)
endthisstupidshit:
LW RA, 0x0034 (SP)
LW S0, 0x0014 (SP)
LW S1, 0x0018 (SP)
LW S2, 0x001C (SP)
LW S3, 0x0020 (SP)
LW S4, 0x0024 (SP)
LW S5, 0x0028 (SP)
LW S6, 0x002C (SP)
LW S7, 0x0030 (SP)
JR RA
ADDIU SP, SP, 0x0080


.org 0xFF7AC
secondsub:
ADDIU SP, SP, 0xFFC8
SW RA, 0x0014 (SP)
SW A0, 0x0038 (SP)
SW A1, 0x003C (SP)
SW R0, 0x0018 (SP)
LW T6, 0x0038 (SP)
LH A0, 0x000A (T6)
LH A1, 0x0010 (T6)
JAL 0x8038283C
LH A2, 0x0016 (T6)
SH V0, 0x002E (SP)
LW T7, 0x0038 (SP)
LH A0, 0x000E (T7)
LH A1, 0x0014 (T7)
JAL 0x8038283C
LH A2, 0x001A (T7)
SH V0, 0x002C (SP)
LW T8, 0x0038 (SP)
LH A0, 0x000A (T8)
LH A1, 0x0010 (T8)
JAL 0x8038289C
LH A2, 0x0016 (T8)
SH V0, 0x002A (SP)
LW T9, 0x0038 (SP)
LH A0, 0x000E (T9)
LH A1, 0x0014 (T9)
JAL 0x8038289C
LH A2, 0x001A (T9)
SH V0, 0x0028 (SP)
JAL 0x803828FC
LH A0, 0x002E (SP)
SH V0, 0x0026 (SP)
JAL 0x80382990
LH A0, 0x002A (SP)
SH V0, 0x0022 (SP)
JAL 0x803828FC
LH A0, 0x002C (SP)
SH V0, 0x0024 (SP)
JAL 0x80382990
LH A0, 0x0028 (SP)
SH V0, 0x0020 (SP)
LH T0, 0x0024 (SP)
LH T1, 0x0020 (SP)
SH T0, 0x001E (SP)
SLT AT, T1, T0
BNEZ AT, endthissubcall
NOP
biggerlooop:
LH T2, 0x0026 (SP)
LH T3, 0x0022 (SP)
SH T2, 0x001C (SP)
SLT AT, T3, T2
BNEZ AT, skiplabel23
NOP
smalllooooop:
LW A0, 0x003C (SP)
LH A1, 0x001C (SP)
LH A2, 0x001E (SP)
JAL 0x803825FC
LW A3, 0x0038 (SP)
LH T4, 0x001C (SP)
LH T8, 0x0022 (SP)
ADDIU T5, T4, 0x0001
SLL T6, T5, 0x10
SRA T7, T6, 0x10
SLT AT, T8, T7
BEQ AT, R0, smalllooooop
SH T5, 0x001C (SP)
skiplabel23:
LH T9, 0x001E (SP)
LH T3, 0x0020 (SP)
ADDIU T0, T9, 0x0001
SLL T1, T0, 0x10
SRA T2, T1, 0x10
SLT AT, T3, T2
BEQ AT, R0, biggerlooop
SH T0, 0x001E (SP)
endthissubcall:
LW RA, 0x0014 (SP)
JR RA
ADDIU SP, SP, 0x0038


.org 0xFF67C
deepcall:
SLL A0, A0, 0x10
SRA A0, A0, 0x10
ADDIU SP, SP, 0xFFF8
ADDIU A0, A0, 0x2000
SLL A0, A0, 0x10
SRA A0, A0, 0x10
BGEZ A0, greaterthanzero
nop
OR A0, R0, R0
greaterthanzero:
BGEZ A0, jumptwice
SRA T8, A0, 0xA
ADDIU AT, A0, 0x03FF
SRA T8, AT, 0xA
jumptwice:
SH T8, 0x0006 (SP)
BGEZ A0, dontsubmesenpai
ANDI T9, A0, 0x03FF
BEQ T9, R0, dontsubmesenpai
NOP
ADDIU T9, T9, 0xFC00
dontsubmesenpai:
SLTI AT, T9, 0x0032
BEQ AT, R0, yesimjumping
NOP
LH T0, 0x0006 (SP)
ADDIU T1, T0, 0xFFFF
SH T1, 0x0006 (SP)
yesimjumping:
LH T2, 0x0006 (SP)
BGEZ T2, imrealplsstopchecking
NOP
SH R0, 0x0006 (SP)
imrealplsstopchecking:
LH V0, 0x0006 (SP)
JR RA
ADDIU SP, SP, 0x0008


.org 0xFF710
verydeep:
SLL A0, A0, 0x10
SRA A0, A0, 0x10
ADDIU SP, SP, 0xFFF8
ADDIU A0, A0, 0x2000
SLL A0, A0, 0x10
SRA A0, A0, 0x10
BGEZ A0, sameasbeforelol
NOP
OR A0, R0, R0
sameasbeforelol:
BGEZ A0, thisisfamilar
SRA T8, A0, 0xA
ADDIU AT, A0, 0x03FF
SRA T8, AT, 0xA
thisisfamilar:
SH T8, 0x0006 (SP)
BGEZ A0, mushroomtrop
ANDI T9, A0, 0x03FF
BEQ T9, R0, mushroomtrop
NOP
ADDIU T9, T9, 0xFC00
mushroomtrop:
SLTI AT, T9, 0x03CF
BNEZ AT, nearlydonewiththisshit
NOP
LH T0, 0x0006 (SP)
ADDIU T1, T0, 0x0001
SH T1, 0x0006 (SP)
nearlydonewiththisshit:
LH T2, 0x0006 (SP)
SLTI AT, T2, 0x0010
BNEZ AT, iamfuckingreal
NOP
ADDIU T3, R0, 0x000F
SH T3, 0x0006 (SP)
iamfuckingreal:
LH V0, 0x0006 (SP)
endthissamefunction:
JR RA
ADDIU SP, SP, 0x0008


.org 0xFF37C
deepdeep:
ADDIU SP, SP, 0xFFD8
SW RA, 0x0014 (SP)
SW A0, 0x0028 (SP)
SW A1, 0x002C (SP)
SW A2, 0x0030 (SP)
SW A3, 0x0034 (SP)
JAL 0x80382490
NOP
SW V0, 0x0024 (SP)
LW T6, 0x0034 (SP)
LUI AT, 0x8039
LDC1 F8, 0xBBB0 (AT)
LWC1 F4, 0x0020 (T6)
CVT.D.S F6, F4
C.LT.D F8, F6
NOP
BC1F deepdeepfirstskip
NOP
SH R0, 0x0018 (SP)
ADDIU T7, R0, 0x0001
BEQ R0, R0, farjumping
SH T7, 0x001A (SP)
deepdeepfirstskip:
LW T8, 0x0034 (SP)
LUI AT, 0x8039
LDC1 F18, 0xBBB8 (AT)
LWC1 F10, 0x0020 (T8)
CVT.D.S F16, F10
C.LT.D F16, F18
NOP
BC1F anotherstupidjumplabel
NOP
ADDIU T9, R0, 0x0001
SH T9, 0x0018 (SP)
ADDIU T0, R0, 0xFFFF
BEQ R0, R0, farjumping
SH T0, 0x001A (SP)
anotherstupidjumplabel:
ADDIU T1, R0, 0x0002
SH T1, 0x0018 (SP)
SH R0, 0x001A (SP)
LW T2, 0x0034 (SP)
LUI AT, 0x8039
LDC1 F8, 0xBBC0 (AT)
LWC1 F4, 0x001C (T2)
CVT.D.S F6, F4
C.LT.D F6, F8
NOP
BC1T takemeplease
NOP
LUI AT, 0x8039
LDC1 F10, 0xBBC8 (AT)
C.LT.D F10, F6
NOP
BC1F farjumping
NOP
takemeplease:
LW T3, 0x0034 (SP)
LB T4, 0x0004 (T3)
ORI T5, T4, 0x0008
SB T5, 0x0004 (T3)
farjumping:
LW T6, 0x0034 (SP)
LH T8, 0x001A (SP)
LH T7, 0x000C (T6)
MULTU T7, T8
MFLO T9
SH T9, 0x001E (SP)
NOP
LW T0, 0x0034 (SP)
LW T1, 0x0024 (SP)
SW T0, 0x0004 (T1)
LH T2, 0x002A (SP)
BEQ T2, R0, skipthatshit
NOP
LH T4, 0x0032 (SP)
LH T3, 0x002E (SP)
LH T8, 0x0018 (SP)
SLL T5, T4, 0x2
SLL T6, T3, 0x2
SUBU T5, T5, T4
SUBU T6, T6, T3
SLL T6, T6, 0x3
SLL T5, T5, 0x7
ADDU T7, T5, T6
LUI T1, 0x8039
SLL T9, T8, 0x3
ADDU T0, T7, T9
ADDIU T1, T1, 0xD698
ADDU T2, T0, T1
BEQ R0, R0, letsdothisskip
SW T2, 0x0020 (SP)
skipthatshit:
LH T4, 0x0032 (SP)
LH T5, 0x002E (SP)
LH T7, 0x0018 (SP)
SLL T3, T4, 0x2
SLL T6, T5, 0x2
SUBU T3, T3, T4
SUBU T6, T6, T5
SLL T6, T6, 0x3
SLL T3, T3, 0x7
ADDU T8, T3, T6
LUI T1, 0x8039
SLL T9, T7, 0x3
ADDU T0, T8, T9
ADDIU T1, T1, 0xBE98
ADDU T2, T0, T1
SW T2, 0x0020 (SP)
letsdothisskip:
LW T4, 0x0020 (SP)
LW T5, 0x0000 (T4)
BEQ T5, R0, lastlabelinthisonefinally
NOP
loopmerightround:
LW T3, 0x0020 (SP)
LH T9, 0x001A (SP)
LW T6, 0x0000 (T3)
LW T7, 0x0004 (T6)
LH T8, 0x000C (T7)
MULTU T8, T9
MFLO T0
SH T0, 0x001C (SP)
NOP
LH T1, 0x001E (SP)
LH T2, 0x001C (SP)
SLT AT, T2, T1
BEQ AT, R0, dontgotoendplease
NOP
BEQ R0, R0, lastlabelinthisonefinally
NOP
dontgotoendplease:
LW T4, 0x0020 (SP)
LW T5, 0x0000 (T4)
SW T5, 0x0020 (SP)
LW T3, 0x0020 (SP)
LW T6, 0x0000 (T3)
BNEZ T6, loopmerightround
NOP
lastlabelinthisonefinally:
LW T7, 0x0020 (SP)
LW T9, 0x0024 (SP)
LW T8, 0x0000 (T7)
SW T8, 0x0000 (T9)
LW T0, 0x0024 (SP)
LW T1, 0x0020 (SP)
SW T0, 0x0000 (T1)
NOP
LW RA, 0x0014 (SP)
JR RA
ADDIU SP, SP, 0x0028

.org 0xFF210
deepest:
ADDIU SP, SP, 0xFFF8
LUI T6, 0x8036
LW T6, 0x116C (T6)
LUI T8, 0x8039
LW T8, 0xEE98 (T8)
SLL T7, T6, 0x3
ADDU T9, T7, T8
SW T9, 0x0004 (SP)
LUI T0, 0x8036
LW T0, 0x116C (T0)
LUI AT, 0x8036
ADDIU T1, T0, 0x0001
SW T1, 0x116C (AT)
LW T2, 0x0004 (SP)
SW R0, 0x0000 (T2)
LUI T3, 0x8036
LW T3, 0x116C (T3)
LW V0, 0x0004 (SP)
JR RA
ADDIU SP, SP, 0x0008

.org 0xFF278
lastsubcall:
ADDIU SP, SP, 0xFFF8
LUI T6, 0x8036
LW T6, 0x1170 (T6)
LUI T8, 0x8039
LW T8, 0xEE9C (T8)
SLL T7, T6, 0x2
SUBU T7, T7, T6
SLL T7, T7, 0x4
ADDU T9, T7, T8
SW T9, 0x0004 (SP)
LUI T0, 0x8036
LW T0, 0x1170 (T0)
LUI AT, 0x8036
ADDIU T1, T0, 0x0001
SW T1, 0x1170 (AT)
LUI T2, 0x8036
LUI T3, 0x8039
LH T3, 0xEEA0 (T3)
LW T2, 0x1170 (T2)
LW T4, 0x0004 (SP)
SH R0, 0x0000 (T4)
LW T5, 0x0004 (SP)
SH R0, 0x0002 (T5)
LW T6, 0x0004 (SP)
SB R0, 0x0004 (T6)
LW T7, 0x0004 (SP)
SB R0, 0x0005 (T7)
LW T8, 0x0004 (SP)
SW R0, 0x002C (T8)
LW V0, 0x0004 (SP)
JR RA
ADDIU SP, SP, 0x0008




.org 0xff61c
thelastoneofthissort:
SLL A0, A0, 0x10
SLL A1, A1, 0x10
SLL A2, A2, 0x10
SRA A2, A2, 0x10
SRA A1, A1, 0x10
SRA A0, A0, 0x10
SLT AT, A0, A1
BEQ AT, R0, lastskipprev
NOP
SLL A0, A1, 0x10
SRA T6, A0, 0x10
OR A0, T6, R0
lastskipprev:
SLT AT, A0, A2
BEQ AT, R0, endthishitfinallyforreal
NOP
SLL A0, A2, 0x10
SRA T7, A0, 0x10
OR A0, T7, R0
endthishitfinallyforreal:
JR RA
OR V0, A0, R0