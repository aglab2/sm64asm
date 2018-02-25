// loadEeprom function
.org 0x349DC
ADDIU SP, SP, 0xFFD0
SW RA, 0x1C(SP)

LUI AT, 0x8034
SB R0, 0xB4A5(AT) // Set value at 0x8033B4A5 to 0 (false)
SB R0, 0xB4A6(AT) // Set value at 0x8033B4A6 to 0 (false)

LUI A0, 0x8020
ADDIU A0, A0, 0x7700
JAL 0x80324570 // bzero function
ADDIU A1, R0, 0x200

LUI A0, 0x8020
ADDIU A0, A0, 0x7700
JAL 0x80279174 // Copy EEPROM to 0x80207700
ADDIU A1, R0, 0x200

LW RA, 0x1C(SP)
JR RA
ADDIU SP, SP, 0x30
//*****************************************************************//

// saveFileData function (A0 = fileNumber. File A = 0, File B = 1, File C = 2, File D = 3)
.org 0x34840
ADDIU SP, SP, 0xFFE8
SW RA, 0x14 (SP)
SW A0, 0x18 (SP)

LUI T6, 0x8034
LB T6, 0xB4A6(T6)
BEQZ T6, SkipFileSave // Branch to end if 0x8033B4A6(bool shouldSaveFileData) is 0(false)
NOP

LW T4, 0x18(SP)
ADDIU T5, R0, 0x70
MULT T5, T4 // T5 = fileNumber * 0x70
MFLO T5 // Get result from mult
LUI T6, 0x8020
ADDIU T6, T6, 0x7700
LUI A0, 0x8033
ORI A0, A0, 0xAF78 // A0 = pointer to message queue (0x8033AF78)
ADDIU A1, R0, 0xE // A1 = 0xE = (0x70 / 8)
MULT A1, T4 // A1 = 0xE * fileNumber, used to find address in EEPROM.
MFLO A1 // Get result from mult
ADDU A2, T5, T6 // A2 = pointer in RAM to copy to EEPROM
JAL 0x803247D0 // osEepromLongWrite, write data to the EEPROM
ADDIU A3, R0, 0x70 // A3 = number of bytes to save

LUI AT, 0x8034
SB R0, 0xB4A6(AT) // Set value at 0x8033B4A6 to 0 (false)

SkipFileSave:
JAL 0x802794A0 // Call saveMenuData() function
NOP

LW RA, 0x14 (SP) // End of function
JR RA
ADDIU SP, SP, 0x18 
//*****************************************************************/

// saveMenuData function
.org 0x344A0
ADDIU SP, SP, 0xFFE8
SW RA, 0x14 (SP)

LUI T6, 0x8034
LB T6, 0xB4A5(T6)
BEQZ T6, SkipMenuSave // Branch to end if 0x8033B4A5(bool shouldSaveMenuData) is 0(false)
NOP

LUI A0, 0x8033
ORI A0, A0, 0xAF78 // A0 = pointer to message queue (0x8033AF78)
ADDIU A1, R0, 0x38 // A1 = 0x38 = (0x1C0 / 8)
LUI A2, 0x8020
ADDIU A2, A2, 0x78C0 // 0x80207700 + 0x1C0, pointer in RAM to copy to EEPROM
JAL 0x803247D0 // osEepromLongWrite, write data to the EEPROM
ADDIU A3, R0, 0x40 // A3 = number of bytes to save

LUI T6, 0x8034
SB T6, 0xB4A5(T6) // Set value at 0x8033B4A5 to 0 (false)

SkipMenuSave:
LW RA, 0x14 (SP) // End of function
JR RA
ADDIU SP, SP, 0x18 