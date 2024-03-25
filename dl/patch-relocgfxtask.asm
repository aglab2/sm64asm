; 0x30000
; gfx pools are relocated to 0x801ce000 + 0x10000 = 0x801DE000 and 0x801ce000 + 0x20000 = 0x801EE000
; sptask is 0x80 sized so GFX_POOL_SIZE 0xff80. this raises pool size from 6400 to roughly 8176

; render_init
.orga 0x2F10
    LI T6, 0x801DE000
.orga 0x2f38
    LI AT, 0xFF80
.orga 0x2f60
    LI AT, 0xFF80
.orga 0x2f90
    LI AT, 0xFF80

; select_gfx_pool
.orga 0x2fec
    LI T9, 0x801DE000
.orga 0x2ff8
.area 0x24, 0x00
    SLL T8, T7, 16
.endarea
.orga 0x3040
    LI AT, 0xFF80
.orga 0x3068
    LI AT, 0xFF80

; display_and_vsync
.orga 0x30e8
    LI AT, 0xFF80
