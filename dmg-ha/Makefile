SRC_DIR = src
OBJ_DIR = obj
TOOL_DIR = Hacktice

# Alter these 4 variables according to your need
CPP_FILES = main image_select render_image levels gp_box

# ROM to inject into for convenient testing
ROM = dmgha.z64

INCLUDE_PATH = C:/sm64-api/sm64
LIBRARY_PATH = C:/sm64-api/ld

# 0x120A110
ROM_OFFSET = 18915600

SRC_FILES = $(patsubst %, $(SRC_DIR)/%.c, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))

PAYLOAD = $(OBJ_DIR)/payload

CC = mips-n64-gcc
AR = mips-n64-ar
LD = mips-n64-ld
CFLAGS = -DF3D_OLD=1 -DBINARY -Wall -Wdouble-promotion -Os -march=vr4300 -mfix4300 -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -I $(INCLUDE_PATH)/libc -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -DTARGET_N64 -mabi=32 -mhard-float

all: $(OBJ_DIR) $(ROM)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(PAYLOAD): $(OBJ_FILES)
	$(LD) -o $@ -L. -L $(LIBRARY_PATH) --oformat binary -T ldscript -Map $(OBJ_DIR)/ha.map -M $^

$(ROM): $(PAYLOAD)
	dd bs=1 seek=$(ROM_OFFSET) if=$^ of=$@ conv=notrunc

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean $(ROM)
