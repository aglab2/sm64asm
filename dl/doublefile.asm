; decouples save file parts allowing double amount of stars
; WARNING: game overs will not do anything to the savefiles
; If you want to understand this code, most stuff is written in C and compiled to ASM :)
; fileIndex has now high argument so for example 0x0102 will refer to file 3 part 1

; zap restore_save_file_data to always call save_file_erase instead
.orga 0x34748
	ADDIU SP, SP, -0x18
	SW RA, 0x14(SP)

	JAL 0x802798fc
	NOP
	
	LW RA, 0x14(SP)
	JR RA
	ADDIU SP, SP, 0x18

; save_file_do_save - calculate signature for both file parts
.orga 0x348a0
	ADDIU A0, T3, 0x38
	LI A1, 0x38
	JAL 0x8027939C
	LI A2, 0x4442 ; new magic

; save_file_erase - clear both parts
.orga 0x34930
	LI A1, 0x70
	
; save_file_copy - copy both parts
.orga 0x349ac
	LI A2, 0x70

; save_file_load_all - verify 2nd part with new magic
.orga 0x34b14
	LI A2, 0x4442 ; new magic
; notice that because of zapping restore_save_file_data, all conditions but
; both magics being correct leads to save_file_erase

; initiate_delayed_warp: zap function call to 'save_file_reload' on game overs
; It does not work anymore. We will use that space for other function ('save_file_get_total_star_count' reimplementation)
.orga 0x5fc4
	NOP

; save_file_get_star_flags takes changes it behavior if short high A0 is set to 1
; u32 save_file_get_star_flags(s32 fileIndex, s32 courseIndex) {
;    u32 part = (fileIndex >> 8);
;    fileIndex = fileIndex & 0xff;
;    u32 starFlags;
;    struct SaveFile* file = (&gSaveBuffer.files[fileIndex][0] + part)
;
;    if (courseIndex == -1) {
;        starFlags = SAVE_FLAG_TO_STAR_FLAG(file->flags);
;    } else {
;        starFlags = file->courseStars[courseIndex] & 0x7F;
;    }
;
;    return starFlags;
; }
.orga 0x351c8
.area 0x74, 0x00
	ANDI AT, A0, 0x00FF
	SLL V0, AT, 0x4
	SLL AT, AT, 0x7
	SUBU AT, AT, V0
	LUI V0, 0x8020
	ADDIU V0, V0, 0x7700
	ADDU V0, V0, AT
	ADDIU AT, R0, 0xFFFF
	BEQ A1, AT, @@ow
	SRA V1, A0, 0x8
	SLL AT, V1, 0x3
	SLL V1, V1, 0x6
	SUBU AT, V1, AT
	ADDU AT, V0, AT
	ADDU AT, AT, A1
	LBU AT, 0x000C (AT)
	B @@ehd
	NOP
@@ow:
	SLL AT, V1, 0x3
	SLL V1, V1, 0x6
	SUBU AT, V1, AT
	ADDU AT, V0, AT
	LBU AT, 0x0008 (AT)
@@ehd:
	JR RA
	ANDI V0, AT, 0x007F
.endarea

;void save_file_set_star_flags(s32 fileIndex, s32 courseIndex, u32 starFlags) {
;    u32 part = (fileIndex >> 8);
;    fileIndex = fileIndex & 0xff;
;    struct SaveFile* file = (&gSaveBuffer.files[fileIndex][0] + part);
;    if (courseIndex == -1) {
;        file->flags |= STAR_FLAG_TO_SAVE_FLAG(starFlags);
;    } else {
;        file->courseStars[courseIndex] |= starFlags;
;    }
;
;    file->flags |= SAVE_FLAG_FILE_EXISTS;
;    gSaveFileModified = TRUE;
;}
.orga 0x3523C
.area 0xD4, 0x00
	ANDI AT, A0, 0x00FF
	SLL V0, AT, 0x4
	SLL AT, AT, 0x7
	SUBU AT, AT, V0
	LUI V0, 0x8020
	ADDIU V0, V0, 0x7700
	ADDU V0, V0, AT
	SRA AT, A0, 0x8
	ADDIU A3, R0, 0xFFFF
	SLL V1, AT, 0x3
	BEQ A1, A3, @@ow
	SLL A0, AT, 0x6
	SUBU AT, A0, V1
	ADDU AT, V0, AT
	ADDU A1, AT, A1
	LBU A3, 0x000C (A1)
	OR A2, A3, A2
	SB A2, 0x000C (A1)
	LW A1, 0x0008 (AT)
	B @@fin
	NOP
@@ow:
	SUBU AT, A0, V1
	ADDU AT, V0, AT
	LW AT, 0x0008 (AT)
	SLL A1, A2, 0x18
	OR A1, AT, A1
@@fin:
	SUBU AT, A0, V1
	ADDU AT, V0, AT
	ORI V0, A1, 0x0001
	SW V0, 0x0008 (AT)
	LUI AT, 0x8034
	ADDIU V0, R0, 0x0001
	JR RA
	SB V0, 0xB4A6 (AT)
.endarea

; interact_star_or_key: pass A2=(bparam4 ? 0x0100 : 0) argument of 'save_file_collect_star_or_key'
; T3 = m, T5 = beh params, T6, beh params >> 24
.orga 0x8d70
	ANDI A2, T5, 0xff
	BEQ A2, R0, @@nopatch
	ANDI A1, T6, 0x1f
	ADDIU A2, R0, 0x0100
@@nopatch:
	JAL 0x279C44 ; save_file_collect_star_or_key
	LH A0, 0xA8(T3)

; save_file_collect_star_or_key: used passed A2 argument to change 'fileIndex' variable to have high bits set properly
.orga 0x34C64
	OR T7, T7, A2
.orga 0x34C88
	SW T7, 0x34(SP) ; replaces pointless call to 'save_file_get_flags'

; save_file_reload is now original 'save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse)' (0x80279bc8)
; implementation is not a direct ASM copy but slightly optimized copy to fit in the space
; In later C code it is referred to as '_save_file_get_total_star_count'
.orga 0x34bc8
.area 0x7C, 0x00
	ADDIU SP, SP, 0xFFD8
	SW RA, 0x0024 (SP)
	SW S3, 0x0020 (SP)
	SW S2, 0x001C (SP)
	SW S1, 0x0018 (SP)
	SW S0, 0x0014 (SP)
	OR S0, A0, R0
	SLT AT, A2, A1
	BNEZ AT, @@loop_end
	ADDIU S2, R0, 0x0000
	OR S1, A1, R0
	ADDIU S3, A2, 0x0001
	ADDIU S2, R0, 0x0000
@@repeat:
	OR A0, S0, R0
	JAL 0x00279F80
	OR A1, S1, R0
	ADDIU S1, S1, 0x0001
	BNE S3, S1, @@repeat
	ADDU S2, V0, S2
@@loop_end:
	OR A0, S0, R0
	JAL 0x00279F80
	ADDIU A1, R0, 0xFFFF
	ADDU V0, V0, S2
	LW S0, 0x0014 (SP)
	LW S1, 0x0018 (SP)
	LW S2, 0x001C (SP)
	LW S3, 0x0020 (SP)
	LW RA, 0x0024 (SP)
	JR RA
	ADDIU SP, SP, 0x0028
.endarea

; save_file_get_total_star_count: call twice original save_file_get_total_star_count at save_file_reload loc with 2 fileIndices
; extern s32 _save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse);
;s32 save_file_get_total_star_count(s32 fileIndex, s32 minCourse, s32 maxCourse) {
;    s32 count = 0;
;    count += _save_file_get_total_star_count(fileIndex, minCourse, maxCourse);
;    count += _save_file_get_total_star_count(fileIndex | 0x100, minCourse, maxCourse);
;    return count;
;}
.orga 0x35010
.area 0x98, 0x00
	ADDIU SP, SP, 0xFFD8
	SW RA, 0x0024 (SP)
	SW S3, 0x0020 (SP)
	SW S2, 0x001C (SP)
	SW S1, 0x0018 (SP)
	SW S0, 0x0014 (SP)
	OR S0, A2, R0
	OR S1, A1, R0
	JAL 0x00279BC8
	OR S2, A0, R0
	OR S3, V0, R0
	ORI A0, S2, 0x0100
	OR A1, S1, R0
	JAL 0x00279BC8
	OR A2, S0, R0
	ADDU V0, V0, S3
	LW S0, 0x0014 (SP)
	LW S1, 0x0018 (SP)
	LW S2, 0x001C (SP)
	LW S3, 0x0020 (SP)
	LW RA, 0x0024 (SP)
	JR RA
	ADDIU SP, SP, 0x0028
.endarea

; bhv_collect_star_init check file based on bparam4
; !!! There's tons of conditions like save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(gCurrCourseNum))
;     If you want to cover all cases, go for it but I currently patched only standstill stars
;void bhv_collect_star_init(void) {
;    s8 starId = (gCurrentObject->oBehParams >> 24) & 0xFF;
;    s32 flagId = (gCurrentObject->oBehParams & 0xff) ? 0x100 : 0;
;    u8 currentLevelStarFlags = save_file_get_star_flags(flagId | (gCurrSaveFileNum - 1), gCurrCourseNum - 1);
;
;    if (currentLevelStarFlags & (1 << starId)) {
;        gCurrentObject->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
;    } else {
;        gCurrentObject->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
;    }
;
;    set_object_hitbox(gCurrentObject, &sCollectStarHitbox);
;}
.orga 0xad4f4
.area 0xBC, 0x00
	ADDIU SP, SP, 0xFFE0
	SW RA, 0x001C (SP)
	SW S1, 0x0018 (SP)
	SW S0, 0x0014 (SP)
	LUI AT, 0x8033
	LH AT, 0xDDF4 (AT)
	ADDIU AT, AT, 0xFFFF
	LUI S0, 0x8036
	LW V0, 0x1160 (S0)
	LW S1, 0x0188 (V0)
	ANDI V0, S1, 0x00FF
	SLTU V0, R0, V0
	SLL V0, V0, 0x8
	OR A0, V0, AT
	LUI AT, 0x8034
	LH AT, 0xBAC6 (AT)
	JAL 0x0027A1C8
	ADDIU A1, AT, 0xFFFF
	SRA AT, S1, 0x18
	ADDIU V1, R0, 0x0001
	SLLV AT, V1, AT
	LUI V1, 0x8033
	ADDIU A0, R0, 0x01E8
	LUI A1, 0x8033
	AND AT, AT, V0
	ANDI AT, AT, 0x00FF
	SLTIU AT, AT, 0x0001
	BNEZ AT, @@other_model
	ADDIU A1, A1, 0x2784
	ADDIU A0, R0, 0x01E4
@@other_model:
	LW AT, 0xDDC4 (V1)
	ADDU AT, AT, A0
	LW AT, 0x0000 (AT)
	LW A0, 0x1160 (S0)
	JAL 0x002A34A4
	SW AT, 0x0014 (A0)
	LW S0, 0x0014 (SP)
	LW S1, 0x0018 (SP)
	LW RA, 0x001C (SP)
	JR RA
	ADDIU SP, SP, 0x0020
.endarea

; bhv_spawned_star_init remove bparam4
.orga 0x65f68
	SB R0, 0x188(T6)

; exclamation_box_spawn_contents remove bparam4
.orga 0x7c7f4
	LW T1, 0x20(SP)
	LW A0, 0x80361160
	SB R0, 0x188(A0)