SRC_DIR = src
OBJ_DIR = obj

# Alter these 4 variables according to your need
CPP_FILES = crumbling fireball pieces main control twod
ROM = sr6.25.z64
INCLUDE_PATH = C:\n64chain\sm64
LIBRARY_PATH = C:\n64chain\ld

# 0x1209300
ROM_OFFSET = 18912000

SRC_FILES = $(patsubst %, $(SRC_DIR)/%.cpp, $(CPP_FILES))
OBJ_FILES = $(patsubst %, $(OBJ_DIR)/%.o, $(CPP_FILES))

CC = clang++
AR = llvm-ar
LD = ld.lld
CFLAGS = -Wall -Wdouble-promotion -Os -mtune=vr4300 -march=mips2 --target=mips-img-elf -fomit-frame-pointer -G0 -I $(INCLUDE_PATH) -mno-check-zero-division -fno-exceptions -fno-builtin -fno-rtti -fno-common -mno-abicalls -flto

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
	rm -f libmill.a
