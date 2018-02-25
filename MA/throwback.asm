;overwrite klepto behav with gp bonk
;use behav 5310, model 0 in tt64

.orga 0x21F110;behav 0x13005310
.word 0x00040000
.word 0x08000000
.word 0x0C000000
	.word 0x80310498
.word 0x09000000

.orga 0xCB498
.area 0xB0
	LUI T1, 0x8034
	LW T2, 0xB17C(T1)
	
	;check for jumps
	LI T0, 0x010208B7
	BEQ T0, T2, train_hit
	NOP

	B train_nohit
	NOP

train_hit:
	LI T0, 0x03000880
	SW T0, 0xB17C(T1)
	LI T0, 1000.0
	SW T0, 0xB1BC(T1)
	;SB R0, 0xB21E(T1)
	
train_nohit:
	JR RA
	NOP
.endarea