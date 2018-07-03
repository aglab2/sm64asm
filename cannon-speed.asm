;floats: 0x42C80000 = 100.0
;floats: 0x447A0000 = 1000.0

; Code makes cannon speed 10 times faster

;horizontal speed
.orga 0x1AF28
	LUI AT, 0x447A ;0x42C8

;vertical speed
.orga 0x1AF58
	LUI AT, 0x447A ;0x42C8