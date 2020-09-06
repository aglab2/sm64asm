 
//big loadblock at d6ea40 to d7ca40 loaded to 80402000
 
.org 0xd70a40
checkanimateable:
addiu sp, sp, 0xffe8
sw ra, 0x14 (SP)
lui t4, 0x8040
Loopanim:
addiu v0, r0, 0x0
lw a0, 0x4100 (t4)
beq a0, r0, oksdgsadg
nop
jal 0x277f50
nop
bne v0, a3, sdagsdagwe
nop
beq r0, r0, oksdgsadg
addiu v0, r0, 0x1
sdagsdagwe:
beq r0, r0, Loopanim
addiu t4, t4, 0x4
oksdgsadg:
lw ra, 0x14 (SP)
jr ra
addiu sp, sp, 0x0018
 
.org 0xf93d8
skipanimatingifbowserinfight1or2:
 ADDIU SP, SP, 0xFFD0
 SW RA, 0x001C (SP)
 SW A0, 0x0030 (SP)
 SW A1, 0x0034 (SP)
 lw a3, 0x020c (a0)
 jal 0x404000        //check if behavior is animated
nop
bne v0, r0, noanimation
 lui a0, 0x1300
 jal 0x277F50
 ori a0, a0, 0x1850
 bne a3, v0, itskanim
addiu at, r0, 0x0022
lui t1, 0x8033
 lhu t1, 0xddf8 (t1)
 bne t1, at, noanimation
 itskanim:
 SW S0, 0x0018 (SP)
 JAL 0x80277F50
 LW A0, 0x0034 (SP)
 SW V0, 0x002C (SP)
 //LW T6, 0x002C (SP)
 JAL 0x80277F50
 LW A0, 0x0000 (v0)
 SW V0, 0x0028 (SP)
 LW T7, 0x0030 (SP)
 //LW T9, 0x0028 (SP)
 LW T8, 0x003C (T7)
 BEQ v0, T8, noanimation
 NOP
 //LW T0, 0x0028 (SP)
// LW T1, 0x0030 (SP)
 SW v0, 0x003C (t7)
// LW T2, 0x0028 (SP)
 LH T3, 0x0000 (v0)
 ANDI T4, T3, 0x0002
 BEQ T4, R0, thehead
 NOP
 BEQ R0, R0, ahead
 ADDIU S0, R0, 0x0001
thehead:
 ADDIU S0, R0, 0xFFFF
ahead:
 //LW T5, 0x0028 (SP)
 //LW T8, 0x0030 (SP)
 LH T6, 0x0004 (v0)
 ADDU T8, S0, T6
 SH T8, 0x0040 (T7)
 //LW T9, 0x0030 (SP)
 SW R0, 0x0048 (T7)
 //LW T0, 0x0030 (SP)
 SH R0, 0x003A (T7)
noanimation:
 LW RA, 0x001C (SP)
 LW S0, 0x0018 (SP)
 JR RA
 ADDIU SP, SP, 0x0030
 
 .org 0x5af04
 fixanim0pointer:
 ADDIU SP, SP, 0xFFF0
 LUI T6, 0x8036
 LW T6, 0x1160 (T6)
 LW T7, 0x003C (T6)
 beq t7, r0, end0pointer
 nop
 LH T8, 0x0000 (T7)
 SW T8, 0x000C (SP)
 LUI T9, 0x8036
 LW T9, 0x1160 (T9)
 LH T0, 0x0040 (T9)
 SW T0, 0x0008 (SP)
 LUI T1, 0x8036
 LW T1, 0x1160 (T1)
 LW T2, 0x003C (T1)
 LH T3, 0x0008 (T2)
 ADDIU T4, T3, 0xFFFE
 SW T4, 0x0004 (SP)
 SW R0, 0x0000 (SP)
 LW T5, 0x000C (SP)
 ANDI T6, T5, 0x0001
 BEQ T6, R0, ahead0pointer
 NOP
 LW T7, 0x0004 (SP)
 LW T9, 0x0008 (SP)
 ADDIU T8, T7, 0x0001
 BNE T8, T9, ahead0pointer
 NOP
 ADDIU T0, R0, 0x0001
 SW T0, 0x0000 (SP)
ahead0pointer:
 LW T1, 0x0008 (SP)
 LW T2, 0x0004 (SP)
 BNE T1, T2, end0pointer
 NOP
 ADDIU T3, R0, 0x0001
 SW T3, 0x0000 (SP)
end0pointer:
 LW V0, 0x0000 (SP)
 JR RA
 ADDIU SP, SP, 0x0010
