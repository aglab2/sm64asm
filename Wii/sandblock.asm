; Wii wtf is wrong with you
.if readu32(outputname(), 0xAA770) == 0xE8FF2015
.orga 0xAA770
	BNEZ T1, 0xAA788
.orga 0xAA788
	J 0x2EF714
	NOP
.endif