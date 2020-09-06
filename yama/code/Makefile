SRC_DIR = src
OBJ_DIR = obj

# Alter these 4 variables according to your need
CPP_FILES = main boo_key book bookshelf key locked_box triplet obj_ctl wall_translucer mips mips_ctl cits_rotat particle_spawner two_d beach_2d_ctl rooms_coll red_indicator c1_moving hud_relocator c1_upwards c2_cannon c5_flying b1_fight_ctl c8_deathfloor c9_puzzle f2_scroll c9_puzzle_coin ow_rock memset cw_death c7_timer funny_text b3f_ctl b3f_platform b3f_switch b3f_fireball credits c9_door dorrie_ctl invi_wall_fixer cw_scroll cheeze_checkpoint
ROM = HH-patched.z64
INCLUDE_PATH = C:\sm64-api\sm64
LIBRARY_PATH = C:\sm64-api\ld

# 0x1208000
ROM_OFFSET = 18907136

SRC_FILES = $(patsubst %, $(SRC_DIR)/%.cpp, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))

CC = clang++
AR = llvm-ar
LD = ld.lld
CFLAGS = -Wall -Wdouble-promotion -Os -mtune=vr4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -I $(INCLUDE_PATH)/libc -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -DTARGET_N64 -mfpxx -flto

all: $(OBJ_DIR) inject

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(CFLAGS)
	
inject: $(OBJ_FILES)
	$(LD) -o tmp -L. -L $(LIBRARY_PATH) --oformat binary -T ldscript -M $^
	dd bs=1 seek=$(ROM_OFFSET) if=tmp of=$(ROM) conv=notrunc
	rm tmp

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
