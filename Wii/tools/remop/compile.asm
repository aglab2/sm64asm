;.definelabel FlipClock, 0x80405800
.definelabel FlipSwitch, 0x80405800
.definelabel FlipSwitchSpawner, 0x804058ec
.definelabel MnRBlock, 0x80405960
.definelabel NoteBlock, 0x80405bd0
.definelabel PSwitch, 0x80405cf0
.definelabel SandBlock, 0x80405f10

;.orga 0x21EEF4
;	.dw FlipClock

.orga 0x21A3F4
	.dw FlipSwitch
	
.orga 0x21A0AC
	.dw FlipSwitchSpawner
	
.orga 0x21AB40
	.dw MnRBlock

.orga 0x219F94
	.dw NoteBlock

.orga 0x021EF4c
	.dw PSwitch

.orga 0x21A464
	.dw SandBlock