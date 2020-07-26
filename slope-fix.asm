; Allow A hold
;.orga 0x22fd8
;	ANDI T0, T9, 0x82

; Allow holding A but expect a release anywhere, on 5th frame jump
.orga 0x22fbc
	LW A0, 0x18(SP) ; m
	LHU T7, 0x1a(A0) ; m->actionTimer
	
	LHU T9, 0x2(A0) ; m->input

	BEQ T7, R0, overinit ; m->actionTimer != 0
	LI T8, 0x80 ;  INPUT_A_HOLD
	LBU T8, 0x1c(A0) ; m->extra &= m->input, T8 == 0 iff there was a frame where INPUT_A_HOLD was not appearing
overinit:
	AND T8, T8, T9 
	SB T8, 0x1c(A0)

	LI T0, 5 ; check actionTimer
	BNE T0, T7, tooearly
	
	ANDI T1, T9, 0x02 ; A pressed
	BNE T1, R0, dojump
	NOP
	LI T6, 0x0C008220
	BEQ T6, A1, nojump
	ANDI T2, T9, 0x80 ; A hold
	BEQ T2, R0, nojump ; end -- not holding
	NOP
	BNE T8, R0, nojump ; end -- always held does not count
	NOP

dojump:
	LW A1, 0x20(SP)
	JAL 0x2530a0
	LI A2, 0
	B end ; end of function
	
	; if (m->actionTimer == 5)
tooearly:
	ADDIU T7, T7, 1
	SH T7, 0x1a(A0)
nojump:

	JAL 0x80264740
	LUI A1, 0x4080
	
	LW A0, 0x18(SP) ; m
	LW A1, 0x1C(SP) ; stopAction
	BNEZ V0, setMarioAction
	LW A3, 0x28(SP) ; animation

commonSlideAction:
	JAL 0x80267ce4
	LW A2, 0x24(SP)
	B end
	LI V0, 0
	
setMarioAction:
	JAL 0x80252cf4
	LI A2, 0
	
end:
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18