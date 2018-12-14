; [ARMIPS 0.9+] Better parallel cam patch
; +++++++++++++++++++++++++++Controls for better parallel lakitu cam+++++++++++++++++++++++++++
; All old c-stick controls work the same leaving camera in 8-way angle mode without changing align
; Camera does not get stuck in c-up mode and cannons
; L button switches between parallel lakitu and non-parallel lakitu for water and flying
; Non-parallel mode for water and flying fixes camera when switching mario->lakitu to closest aligned 8-way direction
; D-pad left/right precise rotates lakitu camera allowing to change align
; D-pad down switches camera back to closest aligned 8-way direction
; D-pad up switches camera back to mario's angle

;is 0 when from mario cam, is not 0 if in lakitu
.defineLabel RAM_STATE, 0x41D20
.defineLabel RAM_STATE_HI, 0x8028
.defineLabel RAM_STATE_LO, 0x6D20

.defineLabel IS_PARALLEL, 0x41D24
.defineLabel IS_PARALLEL_HI, 0x8028
.defineLabel IS_PARALLEL_LO, 0x6D24

.defineLabel MARIO_FACE_HI, 0x8033
.defineLabel MARIO_FACE_LO, 0xDF60
.defineLabel MARIO_FACE_OF, 0x0012

.defineLabel LAKITU_ANGLE_HI, 0x8034
.defineLabel LAKITU_ANGLE_LO, 0xC778

.defineLabel INPUTS_HI, 0x8034
.defineLabel INPUTS_LO1, 0xAFA0 ; hold
.defineLabel INPUTS_LO2, 0xAFA0 ; press

;============Hook mario and lakitu cam functions==============
.orga 0x41BBC
.area 0x8
	B mariocamhook   ; original: BEQ T5, R0, 0x41C54 -- selector between mario and lakitu cam
	NOP
.endarea

.orga 0x41C7C
.area 0x8
	J 0x80282C3C ;B lakitucamhook  ; original: JR T9
	NOP
.endarea
;=========================End Hooks===========================



;Set mario cam hook onto place where bad lakitu cams live
;restrict payload to fit before 41D20 which is RAM
.orga 0x41CD4
.area 0x4C
mariocamhook:
	LUI V1, 0x8028

	BEQ T5, R0, 0x41C54
	NOP
	;====================Mario hook code=====================
	LW T0, 0x6D24(V1) ; Is Parallel
	BEQ T0, R0, mariocamhook_refixlakitu
	NOP
	B mariocamhook_endrefixlakitu
	NOP

mariocamhook_refixlakitu:
	SW R0, 0x6D20(V1) ; Get Mario Angle
mariocamhook_endrefixlakitu:
	;====================Mario hook end======================

	B 0x41BC4
	NOP
.endarea



;============Initilize RAM data with zeroes==================
.orga 0x41D20
.area 0x8
	NOP
	NOP
.endarea
;============================================================
	
;Set lakitu cam hook onto place where bad lakitu cam code live
.orga 0x3DC3C
.area 0x134
lakitucamhook:
	; Preparation: Load needed V0 and V1
	LUI V0, 0x8033
	LUI V1, 0x8034

	;====================Lakitu hook code====================
	
	;
	;--------------------------------------------------------
	;			Remove all low lakitu cam codes
	;--------------------------------------------------------
	;
	LUI T0, 0x8028
	ADDI T0, T0, 0x6CB4
	SUB T0, T9, T0
	BLEZ T0, lakitucamhook_nofixoverflow
	NOP

	LUI T9, 0x8028
	ADDI T9, T9, 0x6CC4
lakitucamhook_nofixoverflow:
	
	
	;
	;--------------------------------------------------------
	;		Check for L button press to switch modes
	;--------------------------------------------------------
	;
	LUI AT, INPUTS_HI
	LH T0, 0xAFA2(AT)
	
	ANDI T0, T0, 0x0020
	BEQ T0, R0, lakitucamhook_nolpress
	NOP
	
	LUI AT, IS_PARALLEL_HI
	LW T0, 0x6D24(AT)
	ADDI AT, R0, 0x0001
	SUB T0, AT, T0
	LUI AT, IS_PARALLEL_HI
	SW T0, 0x6D24(AT)
lakitucamhook_nolpress:


	;
	;--------------------------------------------------------
	;           Use parallel lakitu if L was pressed
	;--------------------------------------------------------
	;
	LUI AT, IS_PARALLEL_HI
	LW T0, 0x6D24(AT)
	BEQ T0, R0, lakitucamhook_nobeparallel
	NOP
	
	;flying check
	LUI T0, 0x8028
	ADDI T0, T0, 0x6C84
	SUB T0, T9, T0
	BEQ T0, R0, lakitucamhook_beparallel
	NOP
	
	;water check
	LUI T0, 0x8028
	ADDI T0, T0, 0x6CA4
	SUB T0, T9, T0
	BEQ T0, R0, lakitucamhook_beparallel
	NOP
	B lakitucamhook_nobeparallel
	NOP
lakitucamhook_beparallel:
	LUI T9, 0x8028
	ADDI T9, T9, 0x6CC4
lakitucamhook_nobeparallel:
	
	
	;
	;--------------------------------------------------------
	;			Rotate lakitu cam on dpad presses
	;--------------------------------------------------------
	;
	LH T0, 0xAFA0(V1) ;Inputs hold
	LH A0, 0xC778(V1) ;Lakitu Angle
	
	ANDI AT, T0, BUTTON_DLEFT
	BEQ AT, R0, lakitucamhook_noleft
	NOP
	B lakitucamhook_minirotateend
	ADDI A0, A0, 0xFFC0
lakitucamhook_noleft:

	ANDI AT, T0, BUTTON_DRIGHT
	BEQ AT, R0, lakitucamhook_noright
	NOP
	B lakitucamhook_minirotateend
	ADDI A0, A0, 0x0040
lakitucamhook_noright:

	ANDI AT, T0, BUTTON_DUP
	BEQ AT, R0, lakitucamhook_noup
	NOP
	LW T0, 0xDF60 (V0) ;Mario facing angle
	LH A0, 0x0012 (T0)
	;Rotate camera to be behind mario
	B lakitucamhook_minirotateend
	ADDI A0, A0, 0x8000
lakitucamhook_noup:

	LH T0, 0xAFA2(V1) ;Inputs press
	ANDI AT, T0, BUTTON_DDOWN
	BEQ AT, R0, lakitucamhook_nodown
	NOP	
	; Round camera to 0
	ADDI A0, A0, 0x1000
	;B lakitucamhook_minirotateend
	ANDI A0, A0, 0xE000
lakitucamhook_nodown:

	
lakitucamhook_minirotateend:
	SH A0, 0xC778(V1) ;Lakitu Angle

	
	;
	;--------------------------------------------------------
	;	Get last state of lakitu cam and line it if needed
	;--------------------------------------------------------
	;
	LUI AT, RAM_STATE_HI
	LW T0, 0x6D20(AT)
	
	BEQ T0, T9, lakitucamhook_fixangleend ;no fix required
	NOP
	
	LW T0, 0xDF60 (V0) ;Mario facing angle
	LH T0, 0x0012 (T0)

	;Rotate camera to be behind mario and make it 8-way
	ADDI T0, T0, 0x9000
	ANDI T0, T0, 0xE000

	SH T0, 0xC778(V1) ;Lakitu Angle
	
	;Store new mode of camera
	LUI AT, RAM_STATE_HI
	SW T9, 0x6D20 (AT)
lakitucamhook_fixangleend:
	;====================Lakitu hook end=====================

	JR T9
	NOP
.endarea