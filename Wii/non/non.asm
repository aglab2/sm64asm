.defineLabel OSTASK_UCODE_BOOT,      0x8032B260
.defineLabel OSTASK_UCODE_BOOT_SIZE, 0xD0
.defineLabel OSTASK_UCODE,           0x8032B330
.defineLabel OSTASK_UCODE_SIZE,      0x1408
.defineLabel OSTASK_UCODE_DATA,      0x80339AC0
.defineLabel OSTASK_UCODE_DATA_SIZE, 0x800

.headersize 0x80245000

.org OSTASK_UCODE_BOOT
.area OSTASK_UCODE_BOOT_SIZE, 0
.incbin "boot.bin"
.endarea

.org OSTASK_UCODE
.area OSTASK_UCODE_SIZE, 0
.incbin "code.bin"
.endarea

.org OSTASK_UCODE_DATA
.area OSTASK_UCODE_DATA_SIZE, 0
.incbin "data.bin"
.endarea