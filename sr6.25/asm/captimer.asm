;-------------------------------------------------------------------------------------------------------;

;Relocates Bank 0x4

.org 0x2ABCA4
.dd 0x03F0000003F50000

.org 0x3F00000
.import "Assembly Data Files\Bank 0x4 Vanilla Contents.txt"

;-------------------------------------------------------------------------------------------------------;

;Relocates HUD String Data

.org 0x3F45400
.import "Assembly Data Files\HUD String Vanilla Contents.txt"

;-------------------------------------------------------------------------------------------------------;

;Adds HUD String Data

.org 0x1205000
.dd 0x1000110012001300,0x1400150016001700,0x180019001A001B00,0x1C001D001E001F00
.dh 0x2000

.org 0x3F45468
.dw 0x04046000
.org 0x3F4547C
.dw 0x04046200
.org 0x3F45484
.dw 0x04046400
.org 0x3F4548C
.dw 0x04046600,0x04046800,0x04046A00,0x04046C00

;-------------------------------------------------------------------------------------------------------;

.org 0x32F90 ;(0x80277F90 in RAM) hook to Custom HUD Expansion
J 0x80406500 ;hook

.org 0x918F0 ;(0x802D68F0) hook to Custom HUD Expansion Part 2
J 0x80406600 ;
NOP

.org 0xF484; (0x80254484 RAM) Hook to Cap Timer Code
J 0x80406880 ;hook

.org 0x1206500; (0x80406500 RAM) HUD Expansion Code

LUI T5, 0x0200
ADDIU T5, T5, 0x7700
BEQ A0, T5, HUDContinue ;if dealing with desired HUD textures, continue
LUI T5, 0x0200
ADDIU T5, T5, 0x7C7C
BEQ A0, T5, HUDContinue ;if dealing with desired HUD textures, continue
NOP
B HUDEnd ;else skip custom code and treat as vanilla
NOP

HUDContinue:
LUI T0, 0x8034
ADDIU T9, R0, 0x10
ADDU T0, T0, T9
LW T0, 0xB400(T0) ;loads the beginning address for RAM Bank 0x4 into T0
BEQ T0, R0, HUDEnd ;treat as vanilla if file has not yet been selected and demo has not begun
NOP
LUI T8, 0x0004
ADDIU T8, T8, 0x5400
ADDIU T3, R0, 0x7700
SUBU T1, T1, T3
ADDU T8, T8, T1 ;the RAM bank address offset of the starting texture segmented pointer (except the MSB 8)
ADDU T8, T0, T8 ;bank offset + bank starting address
OR T2, T8, AT ;final texture pointer starting address
ADDIU T5, R0, 0x0200
LH T6, 0(T2)
BNE T6, T5, HUDEnd ;if unexpected value, treat as vanilla
NOP
OR V0, T2, R0

HUDEnd:
J 0x80277F98 ;vanilla return hook
NOP

;-------------------------------------------------------------------------------------------------------;

.org 0x1206600; (0x80406600 RAM) Custom HUD Expansion Part 2
;All this basically tags onto vanilla's format for selecting HUD textures.
;This looks at an arbitrary value and sets V0 to a corresponding value.
;In our case, we look at our custom values (0x10 through 0x20) and set V0 to
;The offset of the starting address of our texture pointer table divided by 4.


LookAt0x10:
ADDIU AT, R0, 0x0010
BNE A0, AT, LookAt0x11
NOP
JR RA
ADDIU V0, R0, 0x001A ;0x68/4

LookAt0x11:
ADDIU AT, R0, 0x0011
BNE A0, AT, LookAt0x12
NOP
JR RA
ADDIU V0, R0, 0x001F ;0x7C/4

LookAt0x12:
ADDIU AT, R0, 0x0012
BNE A0, AT, LookAt0x13
NOP
JR RA
ADDIU V0, R0, 0x0021 ;0x84/4

LookAt0x13:
ADDIU AT, R0, 0x0013
BNE A0, AT, LookAt0x14
NOP
JR RA
ADDIU V0, R0, 0x0023 ;0x8C/4

LookAt0x14:
ADDIU AT, R0, 0x0014
BNE A0, AT, LookAt0x15
NOP
JR RA
ADDIU V0, R0, 0x0024 ;0x90/4

LookAt0x15:
ADDIU AT, R0, 0x0015
BNE A0, AT, LookAt0x16
NOP
JR RA
ADDIU V0, R0, 0x0025 ;0x94/4

LookAt0x16:
ADDIU AT, R0, 0x0016
BNE A0, AT, LookAt0x17
NOP
JR RA
ADDIU V0, R0, 0x0026 ;0x98/4

LookAt0x17:
ADDIU AT, R0, 0x0017
BNE A0, AT, LookAt0x18
NOP
JR RA
ADDIU V0, R0, 0x0027 ;0x9C/4

LookAt0x18:
ADDIU AT, R0, 0x0018
BNE A0, AT, LookAt0x19
NOP
JR RA
ADDIU V0, R0, 0x0028 ;0xA0/4

LookAt0x19:
ADDIU AT, R0, 0x0019
BNE A0, AT, LookAt0x1A
NOP
JR RA
ADDIU V0, R0, 0x0029 ;0xA4/4

LookAt0x1A:
ADDIU AT, R0, 0x001A
BNE A0, AT, LookAt0x1B
NOP
JR RA
ADDIU V0, R0, 0x002A ;0xA8/4

LookAt0x1B:
ADDIU AT, R0, 0x001B
BNE A0, AT, LookAt0x1C
NOP
JR RA
ADDIU V0, R0, 0x002B ;0xAC/4

LookAt0x1C:
ADDIU AT, R0, 0x001C
BNE A0, AT, LookAt0x1D
NOP
JR RA
ADDIU V0, R0, 0x002C ;0xB0/4

LookAt0x1D:
ADDIU AT, R0, 0x001D
BNE A0, AT, LookAt0x1E
NOP
JR RA
ADDIU V0, R0, 0x002D ;0xB4/4

LookAt0x1E:
ADDIU AT, R0, 0x001E
BNE A0, AT, LookAt0x1F
NOP
JR RA
ADDIU V0, R0, 0x002E ;0xB8/4

LookAt0x1F:
ADDIU AT, R0, 0x001F
BNE A0, AT, LookAt0x20
NOP
JR RA
ADDIU V0, R0, 0x002F ;0xBC/4

LookAt0x20:
ADDIU AT, R0, 0x0020
BNE A0, AT, LookAt0x21
NOP
JR RA
ADDIU V0, R0, 0x0030 ;0xC0/4

LookAt0x21:
J 0x802D6904 ;back to vanilla
NOP

.org 0x1206880; (0x80406880 RAM) Cap Timer HUD Code
SW T9, 0x0010(SP) ;ensures vanilla variable is not messed up

ADDIU A0, R0, 0x36 ;HUD Distance From Left
ADDIU A1, R0, 0x10 ;HUD Distance From Bottom
LUI A2, 0x8034
ADDIU A2, A2, 0x8388 ;Address Pointing to 25. Necessary for Some Reason
ADDIU A3, T6, 0 ;Cap Timer Value
ADDIU T9, R0, 30
DIVU A3, T9 ;Divides timer by 30, putting it into seconds
MFLO A3




LUI T8, 0x8034
LW T8, 0xB174(T8) ;pulls Mario cap state
ANDI T9, T8, 0b1110 ;control variable with vanish, metal, and wing cap set
BEQ T9, R0, SkipCapTexture
NOP
JAL 0x802D62D8 ;HUD Number Printing Function
NOP
LUI T8, 0x8034
LW T8, 0xB174(T8) ;pulls Mario cap state
ANDI T9, T8, 0b1110 ;control variable with vanish, metal, and wing cap set
LUI A2, 0x8040

ADDIU T7, R0, 0b0010 ;this block of code determines which cap/cap combinations Mario has
BEQ T9, T7, VTexture ;and branches to the corresponding instructions. if no cap is set,
ADDIU T7, R0, 0b0100 ;skip printing the cap texture.
BEQ T9, T7, MTexture
ADDIU T7, R0, 0b1000
BEQ T9, T7, WTexture
ADDIU T7, R0, 0b0110
BEQ T9, T7, VMTexture
ADDIU T7, R0, 0b1100
BEQ T9, T7, MWTexture
ADDIU T7, R0, 0b1010
BEQ T9, T7, VWTexture
ADDIU T7, R0, 0b1110
BEQ T9, T7, VMWTexture 
NOP
B SkipCapTexture
NOP

VTexture:
B PrintCapTexture ;this block of code decides the address that points to the arbitrary
ADDIU A2, A2, 0x5000 ;HUD texture selection value.
MTexture:
B PrintCapTexture
ADDIU A2, A2, 0x5002
WTexture:
B PrintCapTexture
ADDIU A2, A2, 0x5004
VMTexture:
B PrintCapTexture
ADDIU A2, A2, 0x5006
MWTexture:
B PrintCapTexture
ADDIU A2, A2, 0x5008
VWTexture:
B PrintCapTexture
ADDIU A2, A2, 0x500A
VMWTexture:
B PrintCapTexture
ADDIU A2, A2, 0x500C

PrintCapTexture:
ADDIU A0, R0, 0x16 ;HUD Distance From Left
ADDIU A1, R0, 0x10 ;HUD Distance From Bottom
JAL 0x802D6554 ;prints the cap texture
NOP
LUI A2, 0x8034
ADDIU A2, A2, 0x8384
ADDIU A0, R0, 0x26 ;HUD Distance From Left
ADDIU A1, R0, 0x10 ;HUD Distance From Bottom
JAL 0x802D6554 ;prints the x to the right of the cap texture
NOP

SkipCapTexture:
LW T9, 0x0010(SP) ;ensures vanilla variable is not messed up

BNE T9, R0, NotZero ;vanilla stuff
NOP

J 0x8025448C ;vanilla stuff
NOP

NotZero:
J 0x802544D0 ;vanilla stuff
NOP