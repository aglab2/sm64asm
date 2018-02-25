;24DD80 - eeprom writer
;24DDBC - count stars

.orga 0x8D80; 0x24DD80-0x245000
	J 0x80310698

.orga 0xAD540
	J 0x80310798

.orga 0xCB698
.area 0x100
;in T4 object address
	ADDI T9, R0, 0x1
	LUI T7, 0x8034
	SB T9, 0xB4A6 (T7) ;should save!
	
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

;File is in V1, store correctly now
	LB T1, 0x188(T4)
	ANDI T1, T1, 0x1F
	LB T2, 0x189(T4)
	SLTI AT, T2, 13
	BEQ AT, R0, odysseystars_nohardcodecourse
	NOP
	BEQ T2, R0, odysseystars_nohardcodecourse
	ADDIU T2, R0, 13
	ADDIU T2, R0, 20
odysseystars_nohardcodecourse:

;Get address for byte to write
	ADDU T3, V1, T2
;Get what to write
;Whomper is special case
	SLTI AT, T2, 21
	BNE AT, R0, odysseystars_notwhomp
	NOP
	B odysseystars_setstar
	ADDIU T4, R0, 0x7

odysseystars_notwhomp:
	ADDIU T4, R0, 1
	SLLV T4, T4, T1
	
odysseystars_setstar:
	LB T5, 0x0(T3)
	OR T5, T5, T4
	SB T5, 0x0(T3)

;idk if this is needed but who cares
	ADDIU A0, R0, 2
	JAL	0x80279C44 
	ADDIU A1, R0, 20
	
	J 0x8024DD88
	NOP
.endarea

.orga 0xCB798
.area 0x100
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

	LUI T6, 0x8036
	LW T6, 0x1160(T6)
	
	LB T6, 0x189(T6)
	SLTI AT, T6, 13
	BEQ AT, R0, odysseystars2_nohardcodecourse
	NOP
	BEQ T6, R0, odysseystars2_nohardcodecourse
	ADDIU T6, R0, 13
	ADDIU T6, R0, 20
odysseystars2_nohardcodecourse:
	
	ADDU T0, V1, T6
	LB T0, 0x0(T0)

	SLLV T3, T2, T1
	AND T4, T0, T3
	J 0x802F2548
	NOP
.endarea