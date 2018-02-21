.orga 0x861C0
.area 0x90
;prologue
addiu sp, sp, -0x18
sw ra, 0x14 (sp)

;load upper part of address 0x8033AFA1
LUI A0, 0x8034

;load byte from address A0+0xAFA1=0x8033AFA1
LB T0, 0xAFA1(A0)

;choose only L button
;command D0XXXXXX YYYY
ANDI T0, T0, 0x0020

;check if button was pressed; NOP because BEQ needs it :]
BEQ T0, R0, nopress
NOP

;store byte at A0+0xB21D=0x8033B21D
;command 80XXXXXX YYYY
LUI A1, 0x8035
SB R0, 0xB21D(A1)

nopress:

;epilogue
lw ra, 0x14 (sp)
jr ra
addiu sp, sp, 0x18
.endarea