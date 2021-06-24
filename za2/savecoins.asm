;instead of "need to check", let it always save :]
.org 0x34854
	JAL 0x802AE908
	NOP
	
;idk what it is, should be unused
.orga 0x69908
.area 0xB0
	LUI T7, 0x8034
	LB T7, 0xB249(T7) ;current level
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI V1, 0x8020
	ADDI V1, V1, 0x7700 ;current eep base

odysseystars_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, odysseystars_fileselectend
	NOP
	ADDI V1, V1, 0x70
	B odysseystars_fileselectloop
	NOP
odysseystars_fileselectend:

	LUI T6, 0x8034
	LH T7, 0xB218(T6)
	SH T7, 0x04(V1)
	LB T7, 0xB21D(T6)
	SB T7, 0x06(V1)

	JR RA
	NOP
.endarea

;------------------------------------------------------
.orga 0x21AD2C
.dw 0x00040000
.dd 0x0C000000802AE9B8
.dw 0x08000000
.dw 0x09000000

.orga 0x699B8
.area 0xA0
	LUI T7, 0x8034
	LB T7, 0xB249(T7) ;current level
	LUI T9, 0x8033
	LH T9, 0xDDF4(T9) ;current file
	LUI V1, 0x8020
	ADDI V1, V1, 0x7700 ;current eep base

odysseystars2_fileselectloop:
	SUBI T9, T9, 0x1
	BEQ T9, R0, odysseystars2_fileselectend
	NOP
	ADDI V1, V1, 0x70
	B odysseystars2_fileselectloop
	NOP
odysseystars2_fileselectend:

	LUI T0, 0x8040
	LB T1, 0x08(T0)
	BNE T1, R0, nodataload
	NOP

	ADDIU T1, T1, 1
	SB T1, 0x08(T0)
	
	LH T5, 0x04(V1)
	LUI T6, 0x8034
	SH T5, 0xB218(T6)
	SH T5, 0xB262(T6)
	
	LB T7, 0x06(V1)
	LI T8, 10
	BGE T8, T7, nostore
	NOP
	SB T7, 0xB21D(T6)

nostore:
nodataload:
	JR RA
	NOP
.endarea