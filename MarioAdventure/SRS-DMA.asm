// [ARMIPS 0.9 w/ SM64 Macro Library] DmaCopy Example by Davideesk

// Call our custom function with DMACopy from the top-most levelscript.
.org 0x108A18
.ls_callFunc 0x00, 0x8024B940

// Text to be displayed on screen
.orga 0x7F0000
.asciiz "-Hello DmaCopy-"

//************** Copy data from ROM into RAM **************//
.orga 0x6940 ; Overwrite the unused function 0x8024B940
.area 0x64 ; Set data import limit to 0x64 bytes
addiu sp, sp, 0xFFE8
sw ra, 0x14 (sp)
sw a0, 0x10 (sp) ; lvl cmd 0x11 safeguard

// These two are nessecary because of what we overwrote at 0x108A18.
.f_osViBlack FALSE ; Set screen blackout to false
sw r0, 0x8038BE24 ; Set level accumulator to 0

// Copies 0x10 bytes from ROM addr 0x7F0000 to RAM addr 0x80370000
.f_DmaCopy 0x80370000, 0x7F0000, 0x7F0010

lw v0, 0x10 (sp) ; lvl cmd 0x11 safeguard
lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea

//************** Display Text on screen **************//
.orga 0x861C0 ; Set ROM address
.area 0xA4 ; Set data import limit to 0xA4 bytes
addiu sp, sp, 0xFFE8
sw ra, 0x14 (sp)

// Prints "-Hello DmaCopy-" at the screen pos (0x70, 0x14)
.f_printXY 0x70, 0x14, 0x80370000

lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea