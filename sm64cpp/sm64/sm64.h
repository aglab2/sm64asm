#pragma once

#include <sm64struct.h>

/* Constants - struct pointers */
#define M64_CURR_OBJ_PTR            (*(MObject**)0x80361160)
#define M64_FIRST_OBJ_STRUCT        (*(MObject**)0x8033D488)

#define M64_MARIO_STRUCT            (Mario*)0x8033B170
#define M64_MARIO_OBJ_PTR           (*(MObject**)0x80361158)
#define M64_LEVEL_STRUCT            (Level*)0x8033B90c

/* Constants - misc pointers */
#define M64_DISPLAY_STATS_FLAGS     0x8032b26a
#define M64_SEGMENT_TABLE           0x8033b400
#define M64_CURRENT_LEVEL_ID        0x8032ddf8 /* u16 */
#define M64_GEO_LAYOUT_PTR_TABLE    0x8032ddc4 /* Pointer to pointer */
#define DEBUG_FLAG1                 0x8032d598

/* graph flags */
#define BILLBOARD 4
#define INVISIBLE 0  /* recheck */
#define VISIBLE   1  /* recheck */

//library function:

#ifdef __cplusplus
extern "C"
{
#endif

int sprintf ( char * str, const char * format, ... );          
          
/* Functions */
int   CreateMessageBox(u16 flags, u16 rotate_to_mario, u16 type_of_dialog, u16 message_id);
/* CreateMessageBox                                          */
/* return value = 0x00 -> dialog is happening                */
/*                0x01 -> dialog is over (choice #1)         */
/*                0x02 -> dialog is over (choice #2)         */
/*                0x03 -> normal dialog is over              */
/* type of dialog = 0xA1 -> save related (wing blocks?)      */
/*                  0xA2 -> regular dialog                   */ 
/*                  0xA3 -> two choices                      */ 
/*   You may want to set an wrapper function for             */
/*   CreateMessageBox (check yoshi.c for an example)         */

int   CreateStar(float x, float y, float z);   /* returns pointer for spawned object */
void  CopyObjParams(MObject* dest, MObject* source);  /* copies X,Y,Z + rotation from another object */
void  CopyObjPosition(MObject* dest, MObject* source);
void  CopyObjRotation(MObject* dest, MObject* source);
void  CopyObjScaling(MObject* dest, MObject* source);
int   DeactivateObject(MObject* obj_pointer); /* kills current object */
float DistanceFromObject(MObject* object1, MObject* object2);  /* usually object 1 = (*Obj) and object 2 = Mario */
void  DmaCopy(u32 dst, u32 bottom, u32 top);
void  ExplodeObject(MObject* obj_ptr);
void  PlaySound(u32 argument);
void  PlaySoundProperly(u32 argument);
void  HideObject();  /* hides current object by ORing 0x01 at offset 0x02 */
void  UnHideObject(); /* ORs 0x10*/
int   RotateTorwardsMario(int current_rotation, int rotation_speed, int arg2);
void  ScaleObject(float global_scaling_factor);
void  ScaleXYZ(MObject* obj_pointer, float x, float y, float z);
void  SetModel(u16 model_ID);  /* change how the object looks */
int   SetObjAnimation(u16 animation_index);
int   ShakeScreen(u16 argument); /* argument = 1 to 4 (?) */
MObject* SpawnObj(MObject* obj_pointer, u16 model_id, u32 behavior);   /* returns pointer for spawned object */
int   CheckObjBehavior(u32 behavior_segmented_pointer); /* return 1 if behavior == arg, else 0  */
int   CheckObjBehavior2(MObject* obj_pointer, u32 behavior_segmented_pointer); /* return 1 if behavior == arg, else 0  */
void  SetObjBehavior(MObject* obj_pointer, u32 behavior_segmented_pointer); /* 0x802a14c4 */
int   IsMarioStepping(); /* returns 1 if Mario is on TOP of a solid object, else 0 */
void  ProcessCollision(); /* 0x803938cc, usually called from behaviors */
int   SetMarioAction(u32 mario_struct_pointer, u32 action, u32 unk_arg);  /* to Do: check return values */

int  ProcessGeoLayout(u32 *dest, u32 segmented_address);   /* 0x8037e0b4 */


/* Music Related */
int  SetMusic(u32 layer, u16 song_index, u32 a2); /* possible layers = 0 (main bgmusic), 1 (other musics) or 2 (sfx) */
int  SetInstrument(u32 *chan_ptr, u8 instrument_index);

/* these functions need to be tested further */
void  CreateTextBox(u16 msg_ID);
int   PrintText(u32 x_pos, char *text, u32 fade); /* used in Credits. a2 = a float value ? */
int   PrintRegularText(u32 x, u32 y, char *table_text_pointer);  /* needs to be tested */ 
int   StopMario(u16 arg);  /* 1 = stop mario  2 = do nothing?? */
/* print functions */
void  PrintInt (u16 x, u16 y, const char* text, u32 value);
void  PrintXY(u16 x, u16 y, const char* text);

/* memory functions */
int   SegmentedToVirtual(u32 segmented_pointer);   /* returns RAM pointer of a segmented address*/
int   GetSegmentBase(int segment);
int   SetSegmentBase(int segment, void *base);  /* sets segment pointer table */
u8    *DynamicIndexCopy(u32 index, u32 begin, u32 end, u32 what);

/* math stuff */
float sqrtf(float x);
float sinf(float x);
float cosf(float x);

int   SetMarioAnimation(MarioAnimation *AnimStruct, u16 index); /* returns 1 if animation has changed, 0 if its the same as before) */

short GetRNG();

#ifdef __cplusplus
}
#endif