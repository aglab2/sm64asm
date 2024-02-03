; !!! Requires 'override size restrictions' use in SM64 Editor/RM !!!
.if readu16(outputname(), 0xD459A) != 0x7C80
.error "Override size restrictions is not enabled"
.endif

; Changes notes limit from 16 to 24.
; Can increase even further if game does not start making krusty sounds
.orga 0xee2a4
	.db 0x20

; Audio heap was relocated to 0x807c0000 but heap size was not raised to 0x40000 from 0x31000-ish
.orga 0xefffc
	.dw 0x40000
