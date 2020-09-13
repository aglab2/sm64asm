.definelabel FlipClock, 0x80405800
.definelabel FlipSwitch, 0x804059e0
.definelabel FlipSwitchSpawner, 0x80405acc
.definelabel MnRBlock, 0x80405b40
.definelabel NoteBlock, 0x80405db0
.definelabel PSwitch, 0x80405ed0
.definelabel SandBlock, 0x804060f0

.orga 0x21EEF4
	.dw FlipClock

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