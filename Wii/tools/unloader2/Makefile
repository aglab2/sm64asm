SRC_DIR = src
OBJ_DIR = obj

# Alter these 4 variables according to your need
CPP_FILES = unloader2
ROM = fc.z64
INCLUDE_PATH = C:\sm64-api\sm64
LIBRARY_PATH = C:\sm64-api\ld

# 0x1207200 - 18903552
# 0x120D200 - 18928128
# 0x120F200 - 18936320
ROM_OFFSET = 18936320

SRC_FILES = $(patsubst %, $(SRC_DIR)/%.cpp, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))

CC = clang++
AR = llvm-ar
LD = ld.lld
CFLAGS = -Wall -Wdouble-promotion -Os -mtune=vr4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -I $(INCLUDE_PATH)/libc -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -DTARGET_N64

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
