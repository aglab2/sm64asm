;max 1E60000

;1D10000 - 0E000000 # start of display list
;1E00000 - 0E0F0000 # start of custom geo layouts
;1E10000 - 0E100000 # rotating beacon 1

.orga 0x21A424 ;behav 13000624
.dw 0x00090000
.dd 0x2A0000000700FC0C
.dw 0x11010001
.dw 0x10240080
.dw 0x0E432000
.dw 0x08000000
.dw 0x0F130080
.dd 0x0C000000803839CC 
.dw 0x09000000
; +3 words

.dw 0x00090000 ;behav 1300064C
.dd 0x2A0000000E113DA8
.dd 0x0400000013000630

;.dw 0x00090000 ;behav 13000660
;.dw 0x0E432000
;.dw 0x08000000
;.dw 0x0F130080
;.dw 0x09000000